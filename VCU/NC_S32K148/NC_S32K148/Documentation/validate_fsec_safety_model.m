function validate_fsec_safety_model()
%VALIDATE_FSEC_SAFETY_MODEL Verify brake-sensor fault debounce and recovery.
% The test uses the existing DBC bench override and does not save the model.

modelDir = 'C:\Users\icemi\Desktop\RZS_Repository\VCU\Models\DBC_Debug';
model = 'VCU10';
oldDir = pwd;
cleanupDir = onCleanup(@() cd(oldDir));
cd(modelDir);
load_system(model);
cleanupModel = onCleanup(@() close_system(model, 0));

monitor = [model '/ASB_Selfcheck/FSEC_Sensor_Monitor'];
portHandles = get_param(monitor, 'PortHandles');
configure_log(portHandles.Outport(1), 'fsec_brake_valid');
configure_log(portHandles.Outport(3), 'fsec_brake_fault');

time = (0:0.01:1.30)';
count = numel(time);
dataset = Simulink.SimulationData.Dataset;
dataset = add_signal(dataset, time, zeros(count, 1, 'uint16'), 'model_hin');
dataset = add_signal(dataset, time, zeros(count, 5, 'uint16'), 'model_ain');
dataset = add_signal(dataset, time, zeros(count, 1, 'single'), 'wlspd_fsensor');
dataset = add_signal(dataset, time, zeros(count, 1, 'single'), 'wlspd_hsensor');

zeroCan = zeros(count, 8, 'uint8');
names = {'AMI_Tx', 'ESP_T_01', 'ESP_T_03', 'ESP_T_06', 'ESP_T_07', ...
    'canb_epssendmsg1', 'canb_epssendmsg2', 'res_msg', ...
    'canb_ipctsmsg1', 'canb_ipctsmsg2'};
for index = 1:numel(names)
    dataset = add_signal(dataset, time, zeroCan, names{index});
end

control = repmat(uint8([165 90 15 0 0 0 0 0]), count, 1);
pedal = repmat(uint8([213 20 213 20 107 10 0 0]), count, 1);
% Disconnect/short-to-ground the brake ADC between 0.20 s and 0.50 s.
faultRows = time >= 0.20 & time < 0.50;
pedal(faultRows, 5:6) = 0;
% Reservoir sensor about 6 bar; cylinder-side pressure is released.
airWheel = repmat(uint8([179 9 0 0 0 0 0 0]), count, 1);
digital = repmat(uint8([249 0 0 0 0 0 0 0]), count, 1);

rxCount = zeros(count, 4, 'uint8');
for index = 1:count
    rxCount(index, :) = uint8(mod(floor(time(index) / 0.10) + 1, 255));
end

dataset = add_signal(dataset, time, control, 'vcu_dbg_control');
dataset = add_signal(dataset, time, pedal, 'vcu_dbg_pedal_adc');
dataset = add_signal(dataset, time, airWheel, 'vcu_dbg_air_wheel');
dataset = add_signal(dataset, time, digital, 'vcu_dbg_digital');
dataset = add_signal(dataset, time, rxCount, 'vcu_dbg_rx_count');

simulationInput = Simulink.SimulationInput(model);
simulationInput = simulationInput.setExternalInput(dataset);
simulationInput = simulationInput.setModelParameter( ...
    'StopTime', '1.30', 'SignalLogging', 'on', ...
    'SignalLoggingName', 'logsout', ...
    'SFInvalidInputDataAccessInChartInitDiag', 'none');
[~, simulationOutput] = evalc('sim(simulationInput)');

valid = signal_data(simulationOutput.logsout, 'fsec_brake_valid');
fault = signal_data(simulationOutput.logsout, 'fsec_brake_fault');
tripIndex = find(time >= 0.35, 1, 'first');
immediateIndex = find(time >= 0.21, 1, 'first');
recoveryIndex = find(time >= 1.10, 1, 'first');

assert(valid(immediateIndex) == false, ...
    'R2D brake-sensor permission was not removed immediately.');
assert(fault(tripIndex) == true, ...
    'Brake sensor fault was not confirmed after the 100 ms debounce.');
assert(valid(tripIndex) == false, ...
    'Brake sensor remained valid while the fault was active.');
assert(fault(recoveryIndex) == false, ...
    'Brake sensor fault did not recover after 500 ms of valid input.');
assert(valid(recoveryIndex) == true, ...
    'Brake sensor did not return to valid after recovery.');

fprintf('BRAKE_VALID_AT_0P21S=%d\n', valid(immediateIndex));
fprintf('BRAKE_FAULT_AT_0P35S=%d\n', fault(tripIndex));
fprintf('BRAKE_VALID_AT_0P35S=%d\n', valid(tripIndex));
fprintf('BRAKE_FAULT_AT_1P10S=%d\n', fault(recoveryIndex));
fprintf('BRAKE_VALID_AT_1P10S=%d\n', valid(recoveryIndex));
fprintf('FSEC_SAFETY_VALIDATION=PASS\n');
end

function configure_log(line, name)
set_param(line, 'DataLogging', 'on', ...
    'DataLoggingNameMode', 'Custom', 'DataLoggingName', name);
end

function dataset = add_signal(dataset, time, data, name)
signal = timeseries(data, time);
signal.DataInfo.Interpolation = tsdata.interpolation('zoh');
dataset = dataset.addElement(signal, name);
end

function data = signal_data(dataset, name)
element = dataset.getElement(name);
data = squeeze(element.Values.Data);
end
