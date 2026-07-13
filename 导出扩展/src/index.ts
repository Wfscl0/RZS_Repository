import { api } from './api-adapter';
import { errorMessage } from './errors';
import { exportCurrentProject } from './exporter';
import { configureSettings } from './settings';

let exportRunning = false;
let shortcutRegistered = false;

export async function activate(): Promise<void> {
  if (shortcutRegistered) {
    return;
  }
  try {
    shortcutRegistered = await api.registerExportShortcut(oneClickExport);
    if (!shortcutRegistered) {
      api.showToast(
        'Ctrl+Alt+E 注册失败，可能与现有快捷键冲突；仍可通过“工具”菜单导出。',
        ESYS_ToastMessageType.WARNING,
        6,
      );
    }
  }
  catch (error) {
    api.showToast(
      `当前 EDA 不支持快捷键注册：${errorMessage(error)}`,
      ESYS_ToastMessageType.WARNING,
      6,
    );
  }
}

export async function oneClickExport(): Promise<void> {
  if (exportRunning) {
    api.showToast('导出任务正在运行，请勿重复点击。', ESYS_ToastMessageType.WARNING, 4);
    return;
  }
  exportRunning = true;
  try {
    await exportCurrentProject();
  }
  finally {
    exportRunning = false;
  }
}

export async function openExportSettings(): Promise<void> {
  if (exportRunning) {
    api.showToast('导出任务正在运行，暂时无法修改设置。', ESYS_ToastMessageType.WARNING, 4);
    return;
  }
  try {
    const changed = await configureSettings();
    if (changed) {
      api.showToast('导出设置已保存。', ESYS_ToastMessageType.SUCCESS, 4);
    }
  }
  catch (error) {
    api.showInformation(`保存设置失败：${errorMessage(error)}`, 'BOM 和网表导出设置');
  }
}
