function audit_vcu_model_details()
%AUDIT_VCU_MODEL_DETAILS Read-only dump of parameters needed by the VCU audit.
% This helper never saves the model or its data dictionary.

modelDir = 'C:\Users\icemi\Desktop\RZS_Repository\VCU\Models\DBC_Debug';
model = 'VCU10';
oldDir = pwd;
cleanup = onCleanup(@() cd(oldDir));
cd(modelDir);
load_system(model);
modelCleanup = onCleanup(@() close_system(model, 0));

sections = { ...
    [model '/Input_Convert'], ...
    [model '/Sensor_Signal'], ...
    [model '/Output_Convert'], ...
    [model '/Motor_Control']};

for sectionIdx = 1:numel(sections)
    section = sections{sectionIdx};
    fprintf('\n=== %s ===\n', section);
    blocks = find_system(section, 'LookUnderMasks', 'all', ...
        'FollowLinks', 'on', 'Type', 'Block');
    for blockIdx = 1:numel(blocks)
        block = blocks{blockIdx};
        blockType = get_param(block, 'BlockType');
        line = sprintf('%s | %s', block, blockType);
        params = {'Gain', 'Value', 'UpperLimit', 'LowerLimit', ...
            'BitIdxRange', 'Inputs', 'OutDataTypeStr'};
        for paramIdx = 1:numel(params)
            param = params{paramIdx};
            if isfield(get_param(block, 'ObjectParameters'), param)
                value = get_param(block, param);
                if ischar(value) && ~isempty(value)
                    line = sprintf('%s | %s=%s', line, param, value); %#ok<AGROW>
                end
            end
        end
        fprintf('%s\n', line);
    end
end

fprintf('\n=== Stateflow charts/data/transitions ===\n');
root = sfroot;
machine = root.find('-isa', 'Stateflow.Machine', 'Name', model);
charts = machine.find('-isa', 'Stateflow.Chart');
for chartIdx = 1:numel(charts)
    chart = charts(chartIdx);
    fprintf('\nCHART %s\n', chart.Path);
    data = chart.find('-isa', 'Stateflow.Data');
    for dataIdx = 1:numel(data)
        item = data(dataIdx);
        fprintf('DATA %s | Scope=%s | Init=%s\n', item.Name, ...
            item.Scope, item.Props.InitialValue);
    end
    transitions = chart.find('-isa', 'Stateflow.Transition');
    for transitionIdx = 1:numel(transitions)
        item = transitions(transitionIdx);
        label = strrep(item.LabelString, newline, ' ');
        if contains(lower(label), {'res', 'emergency', 'driv', 'stop', 'finish'})
            fprintf('TRANSITION %s\n', label);
        end
    end
end

fprintf('\n=== Selected subsystem connections ===\n');
dump_connections(model);
dump_connections([model '/Output_Convert']);
dump_connections([model '/Motor_Control']);

clear modelCleanup cleanup;
end

function dump_connections(system)
fprintf('\nCONNECTIONS %s\n', system);
lines = find_system(system, 'FindAll', 'on', 'SearchDepth', 1, ...
    'Type', 'line');
for lineIdx = 1:numel(lines)
    srcPort = get_param(lines(lineIdx), 'SrcPortHandle');
    dstPorts = get_param(lines(lineIdx), 'DstPortHandle');
    if srcPort == -1 || isempty(dstPorts)
        continue;
    end
    srcBlock = get_param(srcPort, 'Parent');
    srcNumber = get_param(srcPort, 'PortNumber');
    for dstIdx = 1:numel(dstPorts)
        if dstPorts(dstIdx) == -1
            continue;
        end
        dstBlock = get_param(dstPorts(dstIdx), 'Parent');
        dstNumber = get_param(dstPorts(dstIdx), 'PortNumber');
        fprintf('%s:%d -> %s:%d\n', srcBlock, srcNumber, ...
            dstBlock, dstNumber);
    end
end
end
