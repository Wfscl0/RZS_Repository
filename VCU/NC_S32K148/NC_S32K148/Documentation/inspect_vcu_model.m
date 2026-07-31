function inspect_vcu_model
% Read-only inspection helper for the current DBC bench-debug model.

modelDir = 'C:\Users\icemi\Desktop\RZS_Repository\VCU\Models\DBC_Debug';
model = 'VCU10';
oldDir = pwd;
cleanupDir = onCleanup(@() cd(oldDir));
cd(modelDir);

load_system(model);
cleanupModel = onCleanup(@() bdclose(model));

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
printPorts(model, 'Inport');
fprintf('\n[ROOT_OUTPORTS]\n');
printPorts(model, 'Outport');

fprintf('\n[TOP_LEVEL_BLOCKS]\n');
blocks = find_system(model, 'SearchDepth', 1, 'Type', 'Block');
for index = 2:numel(blocks)
    fprintf('%s | %s\n', get_param(blocks{index}, 'Name'), ...
        get_param(blocks{index}, 'BlockType'));
end

root = sfroot;
emCharts = root.find('-isa', 'Stateflow.EMChart');
fprintf('\n[MATLAB_FUNCTIONS]\n');
for index = 1:numel(emCharts)
    if startsWith(emCharts(index).Path, model)
        fprintf('\n--- %s/%s ---\n%s\n', emCharts(index).Path, ...
            emCharts(index).Name, emCharts(index).Script);
    end
end

charts = root.find('-isa', 'Stateflow.Chart');
fprintf('\n[STATEFLOW]\n');
for index = 1:numel(charts)
    chart = charts(index);
    if ~startsWith(chart.Path, model)
        continue;
    end
    fprintf('\nCHART=%s/%s\n', chart.Path, chart.Name);
    states = chart.find('-isa', 'Stateflow.State');
    for stateIndex = 1:numel(states)
        fprintf(' STATE: %s\n', oneLine(states(stateIndex).LabelString));
    end
    transitions = chart.find('-isa', 'Stateflow.Transition');
    for transitionIndex = 1:numel(transitions)
        label = strtrim(transitions(transitionIndex).LabelString);
        if ~isempty(label)
            fprintf(' TRANSITION: %s\n', oneLine(label));
        end
    end
end

try
    dictionary = Simulink.data.dictionary.open('VCU10DB.sldd');
    cleanupDictionary = onCleanup(@() close(dictionary));
    section = getSection(dictionary, 'Design Data');
    entries = find(section);
    fprintf('\n[DICTIONARY_DESIGN_DATA]\n');
    for index = 1:numel(entries)
        value = getValue(entries(index));
        if isa(value, 'Simulink.Parameter')
            value = value.Value;
        end
        if isnumeric(value) || islogical(value)
            rendered = mat2str(value);
        elseif ischar(value)
            rendered = value;
        else
            rendered = class(value);
        end
        fprintf('%s=%s\n', entries(index).Name, rendered);
    end
catch exception
    fprintf('\n[DICTIONARY_ERROR]\n%s\n', ...
        getReport(exception, 'extended'));
end
end

function printPorts(model, blockType)
ports = find_system(model, 'SearchDepth', 1, 'Type', 'Block', ...
    'BlockType', blockType);
for index = 1:numel(ports)
    fprintf('%s | port=%s | dimensions=%s | datatype=%s\n', ...
        get_param(ports{index}, 'Name'), get_param(ports{index}, 'Port'), ...
        get_param(ports{index}, 'PortDimensions'), ...
        get_param(ports{index}, 'OutDataTypeStr'));
end
end

function value = oneLine(value)
value = regexprep(value, '[\r\n]+', ' ');
value = regexprep(value, '\s+', ' ');
end
