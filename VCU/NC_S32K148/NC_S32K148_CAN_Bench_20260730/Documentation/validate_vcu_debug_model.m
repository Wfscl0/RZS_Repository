function validate_vcu_debug_model
% Simulate the generated bench-debug input path and its timeout fallback.

modelDir = 'C:\Users\icemi\Desktop\RZS_Repository\VCU\Models\DBC_Debug';
model = 'VCU10';
oldDir = pwd;
cleanupDir = onCleanup(@() cd(oldDir));
cd(modelDir);
load_system(model);
cleanupModel = onCleanup(@() bdclose(model));

time = (0:0.01:1.20)';
count = numel(time);
dataset = Simulink.SimulationData.Dataset;

dataset = addSignal(dataset, time, zeros(count, 1, 'uint16'), 'model_hin');
dataset = addSignal(dataset, time, zeros(count, 5, 'uint16'), 'model_ain');
dataset = addSignal(dataset, time, zeros(count, 1, 'single'), 'wlspd_fsensor');
dataset = addSignal(dataset, time, zeros(count, 1, 'single'), 'wlspd_hsensor');

zeroCan = zeros(count, 8, 'uint8');
names = {'AMI_Tx', 'ESP_T_01', 'ESP_T_03', 'ESP_T_06', 'ESP_T_07', ...
    'canb_epssendmsg1', 'canb_epssendmsg2', 'res_msg', ...
    'canb_ipctsmsg1', 'canb_ipctsmsg2'};
for index = 1:numel(names)
    dataset = addSignal(dataset, time, zeroCan, names{index});
end

control = repmat(uint8([165 90 15 0 0 0 0 0]), count, 1);
% ADS1115 pedal inputs: 187.5 uV/count. MCU air inputs: 2.416992 mV/count.
pedal = repmat(uint8([213 20 213 20 107 10 0 0]), count, 1);
airWheel = repmat(uint8([119 6 178 9 100 0 200 0]), count, 1);
digital = repmat(uint8([249 0 0 0 0 0 0 0]), count, 1);

rxCount = zeros(count, 4, 'uint8');
for index = 1:count
    if time(index) <= 0.60
        rxCount(index, :) = uint8(floor(time(index) / 0.10) + 1);
    else
        rxCount(index, :) = uint8(7);
    end
end

dataset = addSignal(dataset, time, control, 'vcu_dbg_control');
dataset = addSignal(dataset, time, pedal, 'vcu_dbg_pedal_adc');
dataset = addSignal(dataset, time, airWheel, 'vcu_dbg_air_wheel');
dataset = addSignal(dataset, time, digital, 'vcu_dbg_digital');
dataset = addSignal(dataset, time, rxCount, 'vcu_dbg_rx_count');

simulationInput = Simulink.SimulationInput(model);
simulationInput = simulationInput.setExternalInput(dataset);
simulationInput = simulationInput.setModelParameter( ...
    'StopTime', '1.20', 'SaveOutput', 'on', ...
    'OutputSaveName', 'yout', 'SaveFormat', 'Dataset', ...
    'SFInvalidInputDataAccessInChartInitDiag', 'none');
[~, simulationOutput] = evalc('sim(simulationInput)');

status = outputData(simulationOutput.yout, 10, count);
pedalEcho = outputData(simulationOutput.yout, 11, count);
airWheelEcho = outputData(simulationOutput.yout, 12, count);

activeIndex = find(time >= 0.50, 1, 'first');
expiredIndex = find(time >= 1.20, 1, 'first');

assert(status(activeIndex, 1) == 15, 'All override groups should be active.');
assert(status(activeIndex, 2) == 15, 'All override groups should be requested.');
assert(status(expiredIndex, 1) == 0, 'Overrides should expire after 500 ms.');
assert(status(expiredIndex, 2) == 0, 'Request should expire with control frame.');
assert(isequal(pedalEcho(activeIndex, 1:6), pedal(activeIndex, 1:6)), ...
    'Pedal echo does not match injected raw ADC values.');
assert(isequal(airWheelEcho(activeIndex, :), airWheel(activeIndex, :)), ...
    'Air/wheel echo does not match injected values.');
assert(all(pedalEcho(expiredIndex, 1:6) == 0), ...
    'Pedal input did not fall back to the supplied hardware value.');

fprintf('DEBUG_OVERRIDE_ACTIVE=0x%02X\n', status(activeIndex, 1));
fprintf('DEBUG_REQUESTED=0x%02X\n', status(activeIndex, 2));
fprintf('PEDAL_ECHO_RAW=%s\n', mat2str(pedalEcho(activeIndex, 1:6)));
fprintf('AIR_WHEEL_ECHO_RAW=%s\n', mat2str(airWheelEcho(activeIndex, :)));
fprintf('AFTER_TIMEOUT_ACTIVE=0x%02X AGE_RAW=%u\n', ...
    status(expiredIndex, 1), status(expiredIndex, 7));
fprintf('VALIDATION=PASS\n');
end

function dataset = addSignal(dataset, time, data, name)
signal = timeseries(data, time);
signal.DataInfo.Interpolation = tsdata.interpolation('zoh');
dataset = dataset.addElement(signal, name);
end

function data = outputData(dataset, portIndex, expectedRows)
element = dataset.getElement(portIndex);
data = squeeze(element.Values.Data);
if size(data, 1) ~= expectedRows && size(data, 2) == expectedRows
    data = data.';
end
end
