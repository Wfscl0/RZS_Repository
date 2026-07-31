function apply_topology_20260730()
%APPLY_TOPOLOGY_20260730 Align VCU model I/O with the latest vehicle netlist.
% Source authority:
%   电气拓扑(2).NET, generated 2026-07-30
%   NXPS32K_引脚分配(1).xlsx
% The model root interface and hand-written software architecture are kept.

modelDir = 'C:\Users\icemi\Desktop\RZS_Repository\VCU\Models\DBC_Debug';
model = 'VCU10';
modelFile = fullfile(modelDir, [model '.slx']);
dictionaryFile = fullfile(modelDir, 'VCU10DB.sldd');
backupDir = fullfile(modelDir, 'Backup_20260730_before_topology2');

if ~exist(backupDir, 'dir')
    mkdir(backupDir);
    copyfile(modelFile, fullfile(backupDir, [model '.slx']));
    copyfile(dictionaryFile, fullfile(backupDir, 'VCU10DB.sldd'));
end

oldDir = pwd;
cleanupDir = onCleanup(@() cd(oldDir));
cd(modelDir);
load_system(model);
cleanupModel = onCleanup(@() bdclose(model));

outputSystem = [model '/Output_Convert'];
outPack = [outputSystem '/Physical_OUT1_7_Pack'];
oldHoPack = [outputSystem '/Physical_HO1_4_Pack'];
hoPack = [outputSystem '/Physical_HO1_8_Pack'];

if getSimulinkBlockHandle(hoPack) == -1
    if getSimulinkBlockHandle(oldHoPack) ~= -1
        set_param(oldHoPack, 'Name', 'Physical_HO1_8_Pack');
    else
        error('VCU:Topology:MissingHOPack', 'Cannot find the HO packing block.');
    end
end
if getSimulinkBlockHandle(outPack) == -1
    error('VCU:Topology:MissingOUTPack', 'Cannot find the OUT packing block.');
end

set_param(outPack, 'NumInputs', '7');
set_param(hoPack, 'NumInputs', '8');

unusedOut = [outputSystem '/Unused_OUT_Bit'];
if getSimulinkBlockHandle(unusedOut) == -1
    add_block('simulink/Sources/Constant', unusedOut, ...
        'Value', 'false', 'OutDataTypeStr', 'boolean', ...
        'Position', [365 365 425 395]);
end
unusedHo = [outputSystem '/Unused_HO_Bit'];
if getSimulinkBlockHandle(unusedHo) == -1
    add_block('simulink/Sources/Constant', unusedHo, ...
        'Value', 'false', 'OutDataTypeStr', 'boolean', ...
        'Position', [365 420 425 450]);
end

obsoleteTerminator = [outputSystem '/Unused_RES_Error'];
if getSimulinkBlockHandle(obsoleteTerminator) ~= -1
    delete_block(obsoleteTerminator);
end

clear_all_input_lines(outPack);
clear_all_input_lines(hoPack);
delete_output_line(outPack);
delete_output_line(hoPack);
delete_output_line([outputSystem '/res_error']);

% OUT1..OUT7: Brake, ASSI blue, ASSI yellow, EBS error, RES error,
% reserved, reserved. Bit Concat input 1 is the most-significant bit.
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

% HO1..HO8: EBS trigger, BMS lamp, IMD lamp, DI8, RUN, R2D buzzer,
% Emergency buzzer, reserved.
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

% Old line labels were crossed: the OUT line resolved model_hox while the
% HO line resolved model_lox. Correct the labels; keep the seven-bit OUT
% signal type and widen the eight-bit HO signal type.
widen_output_signal_objects(dictionaryFile);

remove_old_mapping_annotations(outputSystem);
annotation = Simulink.Annotation(outputSystem, [ ...
    'Hardware mapping (netlist 2026-07-30): OUT1..7 = Brake, ASSI-B, ' ...
    'ASSI-Y, EBS error, RES error, reserved, reserved; HO1..8 = EBS ' ...
    'trigger, BMS, IMD, DI8, RUN, R2D, Emergency, reserved.']);
annotation.Position = [180 20 1100 62];

set_param(model, 'SimulationCommand', 'update');
save_system(model);

fprintf('TOPOLOGY_UPDATE=PASS\n');
fprintf('MODEL=%s\n', modelFile);
fprintf('MODEL_VERSION=%s\n', get_param(model, 'ModelVersion'));
fprintf('ROOT_INPUTS=%d ROOT_OUTPUTS=%d\n', ...
    numel(find_system(model, 'SearchDepth', 1, 'BlockType', 'Inport')), ...
    numel(find_system(model, 'SearchDepth', 1, 'BlockType', 'Outport')));
print_pack_sources(outPack, 'OUT');
print_pack_sources(hoPack, 'HO');
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

function remove_old_mapping_annotations(system)
annotations = find_system(system, 'FindAll', 'on', 'SearchDepth', 1, ...
    'Type', 'annotation');
for index = 1:numel(annotations)
    text = get_param(annotations(index), 'Name');
    if contains(text, 'Hardware mapping')
        delete(annotations(index));
    end
end
end

function widen_output_signal_objects(dictionaryFile)
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
% Do not close the dictionary while the linked model is loaded. MATLAB
% releases this client after the model cleanup at function exit.
end

function print_pack_sources(block, prefix)
handles = get_param(block, 'LineHandles');
count = numel(handles.Inport);
for bit = 1:count
    concatPort = count - bit + 1;
    line = handles.Inport(concatPort);
    sourcePort = get_param(line, 'SrcPortHandle');
    sourceBlock = get_param(sourcePort, 'Parent');
    fprintf('%s%d=%s\n', prefix, bit, get_param(sourceBlock, 'Name'));
end
end
