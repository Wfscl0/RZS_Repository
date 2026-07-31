function audit_rule_compliance_current()
%AUDIT_RULE_COMPLIANCE_CURRENT Read-only rule-oriented audit of VCU10.
% This helper never saves the model or its linked data dictionary.

modelDir = 'C:\Users\icemi\Desktop\RZS_Repository\VCU';
model = 'VCU10';
reportFile = fullfile(fileparts(mfilename('fullpath')), ...
    'audit_rule_compliance_current.txt');
oldDir = pwd;
cleanupDir = onCleanup(@() cd(oldDir));
cd(modelDir);

diary(reportFile);
cleanupDiary = onCleanup(@() diary('off'));
load_system(model);
cleanupModel = onCleanup(@() close_system(model, 0));

fprintf('MODEL=%s\n', fullfile(modelDir, [model '.slx']));
fprintf('VERSION=%s\n', get_param(model, 'ModelVersion'));
fprintf('SOLVER=%s FIXED_STEP=%s DICTIONARY=%s\n', ...
    get_param(model, 'Solver'), get_param(model, 'FixedStep'), ...
    get_param(model, 'DataDictionary'));
try
    set_param(model, 'SimulationCommand', 'update');
    fprintf('MODEL_UPDATE=OK\n');
catch exception
    fprintf('MODEL_UPDATE=FAILED\n%s\n', getReport(exception, 'extended'));
end

fprintf('\n[ROOT_INPORTS]\n');
print_ports(model, 'Inport');
fprintf('\n[ROOT_OUTPORTS]\n');
print_ports(model, 'Outport');

fprintf('\n[TOP_LEVEL_BLOCKS]\n');
blocks = find_system(model, 'SearchDepth', 1, 'Type', 'Block');
for index = 2:numel(blocks)
    fprintf('%s | %s\n', blocks{index}, get_param(blocks{index}, 'BlockType'));
end

root = sfroot;
machine = root.find('-isa', 'Stateflow.Machine', 'Name', model);
charts = machine.find('-isa', 'Stateflow.Chart');
fprintf('\n[STATEFLOW]\n');
for chartIndex = 1:numel(charts)
    chart = charts(chartIndex);
    fprintf('\nCHART=%s\n', chart.Path);
    states = chart.find('-isa', 'Stateflow.State');
    for stateIndex = 1:numel(states)
        fprintf(' STATE %s | %s\n', states(stateIndex).Name, ...
            one_line(states(stateIndex).LabelString));
    end
    transitions = chart.find('-isa', 'Stateflow.Transition');
    for transitionIndex = 1:numel(transitions)
        item = transitions(transitionIndex);
        label = strtrim(item.LabelString);
        if ~isempty(label)
            fprintf(' TRANS %s -> %s | %s\n', object_name(item.Source), ...
                object_name(item.Destination), one_line(label));
        end
    end
end

emCharts = root.find('-isa', 'Stateflow.EMChart');
fprintf('\n[MATLAB_FUNCTIONS]\n');
for index = 1:numel(emCharts)
    if strncmp(emCharts(index).Path, model, length(model))
        fprintf('\n--- %s/%s ---\n%s\n', emCharts(index).Path, ...
            emCharts(index).Name, emCharts(index).Script);
    end
end

systems = { ...
    [model '/AS_Stateflow'], ...
    [model '/ASB_Selfcheck'], ...
    [model '/EBS'], ...
    [model '/EPS_Control'], ...
    [model '/Motor_Control'], ...
    [model '/Res'], ...
    [model '/Output_Convert']};
for index = 1:numel(systems)
    if getSimulinkBlockHandle(systems{index}) ~= -1
        fprintf('\n[BLOCKS %s]\n', systems{index});
        print_blocks(systems{index});
        fprintf('\n[LINES %s]\n', systems{index});
        print_lines(systems{index});
    end
end

fprintf('\nAUDIT_COMPLETE=1\n');
clear cleanupModel cleanupDiary cleanupDir;
end

function print_ports(model, blockType)
ports = find_system(model, 'SearchDepth', 1, 'BlockType', blockType);
for index = 1:numel(ports)
    fprintf('%s | port=%s | dimensions=%s | datatype=%s\n', ...
        ports{index}, get_param(ports{index}, 'Port'), ...
        get_param(ports{index}, 'PortDimensions'), ...
        get_param(ports{index}, 'OutDataTypeStr'));
end
end

function print_blocks(system)
blocks = find_system(system, 'SearchDepth', 1, 'Type', 'Block');
for index = 2:numel(blocks)
    block = blocks{index};
    fprintf('%s | %s', block, get_param(block, 'BlockType'));
    parameters = {'Value', 'Gain', 'Operator', 'Inputs', 'Threshold', ...
        'UpperLimit', 'LowerLimit', 'DataStoreName', 'Port'};
    objectParameters = get_param(block, 'ObjectParameters');
    for parameterIndex = 1:numel(parameters)
        parameter = parameters{parameterIndex};
        if isfield(objectParameters, parameter)
            value = get_param(block, parameter);
            if ischar(value) && ~isempty(value)
                fprintf(' | %s=%s', parameter, value);
            end
        end
    end
    fprintf('\n');
end
end

function print_lines(system)
lines = find_system(system, 'FindAll', 'on', 'SearchDepth', 1, 'Type', 'line');
for index = 1:numel(lines)
    sourcePort = get_param(lines(index), 'SrcPortHandle');
    destinationPorts = get_param(lines(index), 'DstPortHandle');
    if sourcePort == -1 || isempty(destinationPorts)
        continue;
    end
    sourceBlock = get_param(sourcePort, 'Parent');
    sourceNumber = get_param(sourcePort, 'PortNumber');
    for destinationIndex = 1:numel(destinationPorts)
        if destinationPorts(destinationIndex) == -1
            continue;
        end
        destinationBlock = get_param(destinationPorts(destinationIndex), 'Parent');
        destinationNumber = get_param(destinationPorts(destinationIndex), 'PortNumber');
        fprintf('%s:%d -> %s:%d\n', sourceBlock, sourceNumber, ...
            destinationBlock, destinationNumber);
    end
end
end

function name = object_name(object)
if isempty(object)
    name = '<default>';
elseif isa(object, 'Stateflow.State')
    name = object.Name;
elseif isa(object, 'Stateflow.Junction')
    name = '<junction>';
else
    name = class(object);
end
end

function value = one_line(value)
value = regexprep(value, '[\r\n]+', ' ');
value = regexprep(value, '\s+', ' ');
end
