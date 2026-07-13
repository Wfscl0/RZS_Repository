import { api } from './api-adapter';
import { ExportStepError } from './errors';
import type { ExtensionSettings } from './types';

const SETTINGS_KEY = 'bom-netlist-export-settings-v1';

const DEFAULT_SETTINGS: ExtensionSettings = {
  outputDirectory: '',
  askEveryTime: false,
  createProjectSubdirectory: true,
};

function isSettings(value: unknown): value is Partial<ExtensionSettings> {
  return typeof value === 'object' && value !== null;
}

export async function loadSettings(): Promise<ExtensionSettings> {
  const stored = api.getStoredSetting(SETTINGS_KEY);
  if (!isSettings(stored)) {
    return { ...DEFAULT_SETTINGS };
  }
  return {
    outputDirectory: typeof stored.outputDirectory === 'string'
      ? stored.outputDirectory
      : DEFAULT_SETTINGS.outputDirectory,
    askEveryTime: typeof stored.askEveryTime === 'boolean'
      ? stored.askEveryTime
      : DEFAULT_SETTINGS.askEveryTime,
    createProjectSubdirectory: typeof stored.createProjectSubdirectory === 'boolean'
      ? stored.createProjectSubdirectory
      : DEFAULT_SETTINGS.createProjectSubdirectory,
  };
}

export async function saveSettings(settings: ExtensionSettings): Promise<void> {
  const saved = await api.setStoredSetting(SETTINGS_KEY, settings);
  if (!saved) {
    throw new ExportStepError('保存扩展设置', '嘉立创 EDA 未能保存导出设置。');
  }
}

export async function resolveOutputSettings(): Promise<ExtensionSettings | undefined> {
  const settings = await loadSettings();
  if (settings.outputDirectory && !settings.askEveryTime) {
    return settings;
  }

  let defaultPath = settings.outputDirectory;
  if (!defaultPath) {
    try {
      defaultPath = await api.getDocumentsPath();
    }
    catch {
      defaultPath = '';
    }
  }

  const outputDirectory = await api.promptDirectory(defaultPath);
  if (!outputDirectory) {
    return undefined;
  }
  const updated = { ...settings, outputDirectory };
  await saveSettings(updated);
  return updated;
}

export async function configureSettings(): Promise<boolean> {
  const settings = await loadSettings();
  let defaultPath = settings.outputDirectory;
  if (!defaultPath) {
    try {
      defaultPath = await api.getDocumentsPath();
    }
    catch {
      defaultPath = '';
    }
  }

  const outputDirectory = await api.promptDirectory(defaultPath);
  if (!outputDirectory) {
    return false;
  }

  const defaults = [
    ...(settings.askEveryTime ? ['askEveryTime'] : []),
    ...(settings.createProjectSubdirectory ? ['createProjectSubdirectory'] : []),
  ];
  const flags = await api.promptSettingFlags(defaults);
  if (!flags) {
    return false;
  }

  await saveSettings({
    outputDirectory,
    askEveryTime: flags.includes('askEveryTime'),
    createProjectSubdirectory: flags.includes('createProjectSubdirectory'),
  });
  return true;
}
