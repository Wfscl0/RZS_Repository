function optimize_vcu_model()
%OPTIMIZE_VCU_MODEL Apply hardware-aligned fixes without changing root I/O.
% The source model remains the DBC-debug copy. Root interfaces and the
% function-call architecture are intentionally preserved.

modelDir = 'C:\Users\icemi\Desktop\RZS_Repository\VCU\Models\DBC_Debug';
model = 'VCU10';
modelFile = fullfile(modelDir, [model '.slx']);
dictionaryFile = fullfile(modelDir, 'VCU10DB.sldd');
backupDir = fullfile(modelDir, 'Backup_20260728_before_full_audit');

if ~exist(backupDir, 'dir')
    mkdir(backupDir);
    copyfile(modelFile, fullfile(backupDir, [model '.slx']));
    copyfile(dictionaryFile, fullfile(backupDir, 'VCU10DB.sldd'));
end

oldDir = pwd;
cleanup = onCleanup(@() cd(oldDir));
cd(modelDir);
load_system(model);

%% Analog inputs: APPS/brake use ADS1115 (187.5 uV/count, 0-5 V).
pedalBlocks = { ...
    'MCU_AinConvert', 'MCU_AinConvert1', 'MCU_AinConvert2'};
pedalNames = { ...
    'Pedal_AinConvert_APP1', ...
    'Pedal_AinConvert_APP2', ...
    'Pedal_AinConvert_Brake'};
for index = 1:numel(pedalBlocks)
    oldPath = [model '/Input_Convert/' pedalBlocks{index}];
    newPath = [model '/Input_Convert/' pedalNames{index}];
    if getSimulinkBlockHandle(newPath) == -1
        set_param(oldPath, 'Name', pedalNames{index});
    end
    set_param([newPath '/Gain'], 'Gain', 'single(187.5e-6)');
    set_param([newPath '/Saturation'], 'LowerLimit', '0', 'UpperLimit', '5');
end

%% Pressure inputs: MCU ADC path represents the board's 0-10 V inputs.
pressureBlocks = {'ADS1115_AinConvert', 'ADS1115_AinConvert1'};
pressureNames = {'Pressure_AinConvert1', 'Pressure_AinConvert2'};
for index = 1:numel(pressureBlocks)
    oldPath = [model '/Input_Convert/' pressureBlocks{index}];
    newPath = [model '/Input_Convert/' pressureNames{index}];
    if getSimulinkBlockHandle(newPath) == -1
        set_param(oldPath, 'Name', pressureNames{index});
    end
    set_param([newPath '/Gain'], 'Gain', 'single(0.0024169921875)');
    set_param([newPath '/Saturation'], 'LowerLimit', '0', 'UpperLimit', '10');
end

% Sensor is 0-1 MPa at 0-10 V. The upstream gain converts V to mV, so
% 0.001 bar/mV gives 0-10 bar (0-1 MPa).
set_param([model '/Sensor_Signal/Gain'], 'Gain', 'single(0.001)');
set_param([model '/Sensor_Signal/Gain1'], 'Gain', 'single(0.001)');

%% Make Stateflow local initial states explicit for simulation and firmware.
root = sfroot;
machine = root.find('-isa', 'Stateflow.Machine', 'Name', model);
explicitFalse = {'di8_flag'};
explicitZero = { ...
    'di8_offcheck_flag', 'di8_check_flag', ...
    'run_offcheck_flag', 'run_check_flag', 'run_flag', ...
    'shutdown_count', 'fault_count'};
data = machine.find('-isa', 'Stateflow.Data');
for index = 1:numel(data)
    if strcmp(data(index).Scope, 'Local')
        if any(strcmp(data(index).Name, explicitFalse))
            data(index).Props.InitialValue = 'F';
        elseif any(strcmp(data(index).Name, explicitZero))
            data(index).Props.InitialValue = '0';
        end
    end
end

% RES heartbeat timeout: tolerate short bus jitter and confirm a timeout
% after roughly 300 ms at the 10 ms model rate.
heartbeatChart = machine.find('-isa', 'Stateflow.Chart', ...
    'Path', [model '/Res/Res_Msg/Subsystem/heaartbeat_chart']);
if ~isempty(heartbeatChart)
    transitions = heartbeatChart.find('-isa', 'Stateflow.Transition');
    for index = 1:numel(transitions)
        label = transitions(index).LabelString;
        if contains(label, 'hbcnt>10')
            transitions(index).LabelString = strrep(label, 'hbcnt>10', 'hbcnt>30');
        end
    end
end

%% RES stop gate: current frame XOR match + existing communication checks.
resSystem = [model '/Res/Res_Msg'];
checksumMatch = [resSystem '/Stop_Checksum_Match'];
stopValid = [resSystem '/Validated_Stop'];
if getSimulinkBlockHandle(checksumMatch) == -1
    add_block('simulink/Logic and Bit Operations/Relational Operator', ...
        checksumMatch, 'Operator', '==', 'Position', [500 235 555 275]);
end
if getSimulinkBlockHandle(stopValid) == -1
    add_block('simulink/Logic and Bit Operations/Logical Operator', ...
        stopValid, 'Operator', 'AND', 'Inputs', '3', ...
        'Position', [640 190 695 245]);
end

delete_input_line([resSystem '/Bus Creator'], 1);
delete_input_line(checksumMatch, 1);
delete_input_line(checksumMatch, 2);
delete_input_line(stopValid, 1);
delete_input_line(stopValid, 2);
delete_input_line(stopValid, 3);
add_line(resSystem, 'Bitwise AND5/1', 'Stop_Checksum_Match/1', 'autorouting', 'on');
add_line(resSystem, 'Logical Operator/1', 'Stop_Checksum_Match/2', 'autorouting', 'on');
add_line(resSystem, 'Data Type Conversion7/1', 'Validated_Stop/1', 'autorouting', 'on');
add_line(resSystem, 'Subsystem/1', 'Validated_Stop/2', 'autorouting', 'on');
add_line(resSystem, 'Stop_Checksum_Match/1', 'Validated_Stop/3', 'autorouting', 'on');
validatedStopLine = add_line(resSystem, 'Validated_Stop/1', ...
    'Bus Creator/1', 'autorouting', 'on');
set_param(validatedStopLine, 'Name', 'res_stop');

%% Torque safety gate: emergency state forces zero torque in the same step.
motorSystem = [model '/Motor_Control'];
emergencyRead = [motorSystem '/AS_Emergency_Read'];
zeroTorque = [motorSystem '/Emergency_Zero_Torque'];
torqueGate = [motorSystem '/Emergency_Torque_Gate'];
if getSimulinkBlockHandle(emergencyRead) == -1
    add_block('simulink/Signal Routing/Data Store Read', emergencyRead, ...
        'DataStoreName', 'as_emergency_flag', ...
        'Position', [695 520 800 550]);
end
if getSimulinkBlockHandle(zeroTorque) == -1
    add_block('simulink/Sources/Constant', zeroTorque, ...
        'Value', '0', 'OutDataTypeStr', 'double', ...
        'Position', [700 455 750 485]);
end
if getSimulinkBlockHandle(torqueGate) == -1
    add_block('simulink/Signal Routing/Switch', torqueGate, ...
        'Criteria', 'u2 >= Threshold', 'Threshold', '0.5', ...
        'Position', [850 430 905 520]);
end

delete_input_line([motorSystem '/Goto2'], 1);
delete_input_line(torqueGate, 1);
delete_input_line(torqueGate, 2);
delete_input_line(torqueGate, 3);
add_line(motorSystem, 'Emergency_Zero_Torque/1', 'Emergency_Torque_Gate/1', 'autorouting', 'on');
add_line(motorSystem, 'AS_Emergency_Read/1', 'Emergency_Torque_Gate/2', 'autorouting', 'on');
add_line(motorSystem, 'Motor_Torque_Stateflow/1', 'Emergency_Torque_Gate/3', 'autorouting', 'on');
add_line(motorSystem, 'Emergency_Torque_Gate/1', 'Goto2/1', 'autorouting', 'on');

%% Output packing follows the 2026-07-30 vehicle netlist and VCU pin table.
outputSystem = [model '/Output_Convert'];
oldFive = [outputSystem '/Bit Concat'];
oldSeven = [outputSystem '/Bit Concat1'];
fivePack = [outputSystem '/Physical_HO1_8_Pack'];
sevenPack = [outputSystem '/Physical_OUT1_7_Pack'];
if getSimulinkBlockHandle(fivePack) == -1
    oldNamedFive = [outputSystem '/Physical_HO1_4_Pack'];
    if getSimulinkBlockHandle(oldNamedFive) ~= -1
        set_param(oldNamedFive, 'Name', 'Physical_HO1_8_Pack');
    else
        set_param(oldFive, 'Name', 'Physical_HO1_8_Pack');
    end
end
if getSimulinkBlockHandle(sevenPack) == -1
    set_param(oldSeven, 'Name', 'Physical_OUT1_7_Pack');
end
set_param(fivePack, 'NumInputs', '8');
set_param(sevenPack, 'NumInputs', '7');
falseBlock = [outputSystem '/Unused_HO_Bit'];
if getSimulinkBlockHandle(falseBlock) == -1
    add_block('simulink/Sources/Constant', falseBlock, ...
        'Value', 'false', 'OutDataTypeStr', 'boolean', ...
        'Position', [380 430 430 460]);
end
unusedOutBlock = [outputSystem '/Unused_OUT_Bit'];
if getSimulinkBlockHandle(unusedOutBlock) == -1
    add_block('simulink/Sources/Constant', unusedOutBlock, ...
        'Value', 'false', 'OutDataTypeStr', 'boolean', ...
        'Position', [380 380 430 410]);
end

% The new netlist assigns OUT5 to RES error. R2D is on HO6, so the old
% terminator is obsolete.
resErrorTerminator = [outputSystem '/Unused_RES_Error'];
if getSimulinkBlockHandle(resErrorTerminator) ~= -1
    delete_block(resErrorTerminator);
end

clear_all_input_lines(fivePack);
clear_all_input_lines(sevenPack);
delete_output_line(fivePack);
delete_output_line(sevenPack);
delete_output_line([outputSystem '/res_error']);

% Bit-concat port 1 is the most-significant bit. OUT1..OUT7 are brake,
% ASSI blue, ASSI yellow, EBS error, RES error, reserved, reserved.
add_line(outputSystem, 'Unused_OUT_Bit/1', 'Physical_OUT1_7_Pack/1', 'autorouting', 'on');
add_line(outputSystem, 'Unused_OUT_Bit/1', 'Physical_OUT1_7_Pack/2', 'autorouting', 'on');
add_line(outputSystem, 'res_error/1', 'Physical_OUT1_7_Pack/3', 'autorouting', 'on');
add_line(outputSystem, 'led_ebserror/1', 'Physical_OUT1_7_Pack/4', 'autorouting', 'on');
add_line(outputSystem, 'led_assi_y/1', 'Physical_OUT1_7_Pack/5', 'autorouting', 'on');
add_line(outputSystem, 'led_assi_b/1', 'Physical_OUT1_7_Pack/6', 'autorouting', 'on');
add_line(outputSystem, 'led_brake/1', 'Physical_OUT1_7_Pack/7', 'autorouting', 'on');
outLine = add_line(outputSystem, 'Physical_OUT1_7_Pack/1', 'model_lox/1', ...
    'autorouting', 'on');
set_param(outLine, 'Name', 'model_lox');

% HO1..HO8 are EBS trigger, BMS lamp, IMD lamp, DI8, RUN, R2D buzzer,
% Emergency buzzer and reserved.
add_line(outputSystem, 'Unused_HO_Bit/1', 'Physical_HO1_8_Pack/1', 'autorouting', 'on');
add_line(outputSystem, 'buzzer_ebs/1', 'Physical_HO1_8_Pack/2', 'autorouting', 'on');
add_line(outputSystem, 'buzzer_r2d/1', 'Physical_HO1_8_Pack/3', 'autorouting', 'on');
add_line(outputSystem, 'run/1', 'Physical_HO1_8_Pack/4', 'autorouting', 'on');
add_line(outputSystem, 'di8/1', 'Physical_HO1_8_Pack/5', 'autorouting', 'on');
add_line(outputSystem, 'led_imderr/1', 'Physical_HO1_8_Pack/6', 'autorouting', 'on');
add_line(outputSystem, 'led_bmserr/1', 'Physical_HO1_8_Pack/7', 'autorouting', 'on');
add_line(outputSystem, 'ebs_trig/1', 'Physical_HO1_8_Pack/8', 'autorouting', 'on');
hoLine = add_line(outputSystem, 'Physical_HO1_8_Pack/1', 'model_hox/1', ...
    'autorouting', 'on');
set_param(hoLine, 'Name', 'model_hox');

% Correct the formerly crossed OUT/HO signal-object labels. The OUT pack is
% seven bits; the HO pack uses all eight bits. Both use uint8 C storage.
dictionary = Simulink.data.dictionary.open(dictionaryFile);
section = getSection(dictionary, 'Design Data');
entry = getEntry(section, 'model_lox');
signal = getValue(entry);
signal.DataType = 'fixdt(0,7,0)';
setValue(entry, signal);
entry = getEntry(section, 'model_hox');
signal = getValue(entry);
signal.DataType = 'uint8';
setValue(entry, signal);
saveChanges(dictionary);

% Visible notes make the hardware assumptions obvious when opening Simulink.
ensure_annotation(outputSystem, ...
    'Hardware mapping (netlist 2026-07-30): OUT1..7 = Brake, ASSI-B, ASSI-Y, EBS error, RES error, reserved, reserved; HO1..8 = EBS trigger, BMS, IMD, DI8, RUN, R2D, Emergency, reserved.', ...
    [250 20 1050 60]);
ensure_annotation([model '/Input_Convert'], ...
    'ADC mapping: APP1/APP2/Brake = ADS1115 0-5 V; Air1/Air2 = MCU ADC 0-10 V.', ...
    [170 15 800 55]);

set_param(model, 'SimulationCommand', 'update');
save_system(model);
close_system(model, 0);
clear cleanup;
fprintf('MODEL_OPTIMIZATION=PASS\n');
fprintf('MODEL=%s\n', modelFile);
fprintf('BACKUP=%s\n', backupDir);
end

function delete_input_line(block, portNumber)
handles = get_param(block, 'LineHandles');
if portNumber <= numel(handles.Inport) && handles.Inport(portNumber) ~= -1
    delete_line(handles.Inport(portNumber));
end
end

function clear_all_input_lines(block)
handles = get_param(block, 'LineHandles');
for index = 1:numel(handles.Inport)
    if handles.Inport(index) ~= -1
        delete_line(handles.Inport(index));
    end
end
end

function delete_output_line(block)
handles = get_param(block, 'LineHandles');
for index = 1:numel(handles.Outport)
    if handles.Outport(index) ~= -1
        delete_line(handles.Outport(index));
    end
end
end

function ensure_annotation(system, text, position)
annotations = find_system(system, 'FindAll', 'on', 'SearchDepth', 1, ...
    'Type', 'annotation');
for index = 1:numel(annotations)
    if strcmp(get_param(annotations(index), 'PlainText'), text)
        return;
    end
end
annotation = Simulink.Annotation(system, text);
annotation.Position = position;
end
