%% Validate the VCU CAN bench DBC without connecting CAN hardware.
thisFile = mfilename('fullpath');
benchDir = fileparts(thisFile);
dbcFile = fullfile(fileparts(benchDir), 'DBC', 'VCU_TSMaster_Debug.dbc');

db = canDatabase(dbcFile);
info = messageInfo(db);
required = {'VCU_DBG_Control', 'VCU_DBG_PedalADC', ...
    'VCU_DBG_AirWheel', 'VCU_DBG_Digital', 'VCU_DBG_Status', ...
    'VCU_DBG_PedalEcho', 'VCU_DBG_AirWheelEcho'};

if istable(info)
    available = cellstr(string(info.Name));
else
    available = {info.Name};
end
missing = required(~ismember(required, available));
assert(isempty(missing), 'Missing debug messages: %s', strjoin(missing, ', '));

fprintf('DBC_PARSE=PASS\n');
fprintf('DBC_MESSAGES=%d\n', numel(info));
fprintf('DBC_DEBUG_MESSAGES=%d/%d\n', numel(required), numel(required));
