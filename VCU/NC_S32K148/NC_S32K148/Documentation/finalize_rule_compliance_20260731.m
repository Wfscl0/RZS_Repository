function finalize_rule_compliance_20260731()
%FINALIZE_RULE_COMPLIANCE_20260731 Final safety-latch and model hygiene pass.
% 仅修改 VCU10 模型内部逻辑，不改变根接口和底层软件架构。

modelDir = 'C:\Users\icemi\Desktop\RZS_Repository\VCU';
model = 'VCU10';
oldDir = pwd;
cleanupDir = onCleanup(@() cd(oldDir));
cd(modelDir);
load_system(model);
cleanupModel = onCleanup(@() close_system(model, 0));
root = sfroot;

%% Emergency/Finished 必须保持锁存，退出仅允许由低压重启完成。
chart = root.find('-isa', 'Stateflow.Chart', ...
    'Path', [model '/AS_Stateflow/Chart']);
assert(~isempty(chart), 'Cannot find AS state chart.');
transitions = chart.find('-isa', 'Stateflow.Transition');
for index = numel(transitions):-1:1
    item = transitions(index);
    sourceName = object_name(item.Source);
    destinationName = object_name(item.Destination);
    if (strcmp(sourceName, 'AS_Emergency') && ...
            contains(item.LabelString, 'ebs_warning==0')) || ...
            (strcmp(sourceName, 'AS_Finished') && ...
            strcmp(destinationName, 'AS_Off'))
        delete(item);
    end
end

%% APPS 双通道偏差超过 10% 持续 100 ms 后确认故障。
pedalChart = root.find('-isa', 'Stateflow.Chart', ...
    'Path', [model ...
    '/Motor_Control/ManualTorque_Calculation/Pedal_Fault_Check']);
assert(~isempty(pedalChart), 'Cannot find APPS mismatch chart.');
transitions = pedalChart.find('-isa', 'Stateflow.Transition');
for index = 1:numel(transitions)
    if contains(transitions(index).LabelString, 'fault_count>=3')
        transitions(index).LabelString = strrep( ...
            transitions(index).LabelString, 'fault_count>=3', ...
            'fault_count>=10');
    end
end

%% 清理前次改线遗留的悬空分支，并明确终止已保留但不再参与触发的接口。
ebs = [model '/EBS'];
disconnect_output([ebs '/as_ebs_trig']);
disconnect_output([ebs '/EBS_Trigger_ASMS_Gate']);
add_line(ebs, 'as_ebs_trig/1', 'EBS_Trigger_ASMS_Gate/1', ...
    'autorouting', 'on');
add_line(ebs, 'EBS_Trigger_ASMS_Gate/1', 'ebs_trig/1', ...
    'autorouting', 'on');
add_line(ebs, 'EBS_Trigger_ASMS_Gate/1', ...
    'EBS_Response_Monitor/1', 'autorouting', 'on');

terminate_output(ebs, 'asb_check', 'Unused_ASB_Check_Terminator', ...
    [435 405 455 425]);
terminate_output(ebs, 'ipc_err', 'Unused_IPC_Error_Terminator', ...
    [435 450 455 470]);

ebsLed = [model '/LED_Control/EBS_LED'];
obsolete = [ebsLed '/Compare To Constant1'];
if getSimulinkBlockHandle(obsolete) ~= -1
    disconnect_output(obsolete);
    delete_block(obsolete);
end
disconnect_output([ebsLed '/display']);
orBlock = [ebsLed '/Logical Operator'];
set_param(orBlock, 'Inputs', '4');
clear_inputs(orBlock);
add_line(ebsLed, 'Compare To Constant/1', 'Logical Operator/1', ...
    'autorouting', 'on');
add_line(ebsLed, 'Enabled Subsystem/1', 'Logical Operator/2', ...
    'autorouting', 'on');
add_line(ebsLed, 'Logical Operator3/1', 'Logical Operator/3', ...
    'autorouting', 'on');
add_line(ebsLed, 'display/1', 'Logical Operator/4', ...
    'autorouting', 'on');

set_param(model, 'SimulationCommand', 'update');
save_system(model);
fprintf('FINALIZE_RULE_COMPLIANCE=PASS\n');
fprintf('MODEL_VERSION=%s\n', get_param(model, 'ModelVersion'));
clear cleanupModel cleanupDir;
end

function name = object_name(object)
if isempty(object)
    name = '';
elseif isa(object, 'Stateflow.State')
    name = object.Name;
else
    name = class(object);
end
end

function disconnect_output(block)
handles = get_param(block, 'LineHandles');
if ~isfield(handles, 'Outport')
    return;
end
for index = 1:numel(handles.Outport)
    if handles.Outport(index) ~= -1
        delete_line(handles.Outport(index));
    end
end
end

function clear_inputs(block)
handles = get_param(block, 'LineHandles');
if ~isfield(handles, 'Inport')
    return;
end
for index = 1:numel(handles.Inport)
    if handles.Inport(index) ~= -1
        delete_line(handles.Inport(index));
    end
end
end

function terminate_output(system, sourceName, terminatorName, position)
source = [system '/' sourceName];
terminator = [system '/' terminatorName];
disconnect_output(source);
if getSimulinkBlockHandle(terminator) == -1
    add_block('simulink/Sinks/Terminator', terminator, ...
        'Position', position);
end
clear_inputs(terminator);
add_line(system, [sourceName '/1'], [terminatorName '/1'], ...
    'autorouting', 'on');
end
