import { ExportStepError } from './errors';
import type { NetlistSelection } from './types';

const REQUIRED_APIS: ReadonlyArray<readonly [unknown, string, string]> = [
  [eda.dmt_Project, 'getCurrentProjectInfo', 'DMT_Project.getCurrentProjectInfo()'],
  [eda.dmt_Schematic, 'getCurrentSchematicPageInfo', 'DMT_Schematic.getCurrentSchematicPageInfo()'],
  [eda.dmt_SelectControl, 'getCurrentDocumentInfo', 'DMT_SelectControl.getCurrentDocumentInfo()'],
  [eda.dmt_EditorControl, 'openDocument', 'DMT_EditorControl.openDocument()'],
  [eda.dmt_EditorControl, 'activateDocument', 'DMT_EditorControl.activateDocument()'],
  [eda.sch_Document, 'save', 'SCH_Document.save()'],
  [eda.sch_PrimitiveComponent, 'getAll', 'SCH_PrimitiveComponent.getAll()'],
  [eda.sch_ManufactureData, 'getBomFile', 'SCH_ManufactureData.getBomFile()'],
  [eda.sch_ManufactureData, 'getNetlistFile', 'SCH_ManufactureData.getNetlistFile()'],
  [eda.sys_FileSystem, 'saveFile', 'SYS_FileSystem.saveFile()'],
  [eda.sys_Storage, 'getExtensionUserConfig', 'SYS_Storage.getExtensionUserConfig()'],
  [eda.sys_Storage, 'setExtensionUserConfig', 'SYS_Storage.setExtensionUserConfig()'],
  [eda.sys_Dialog, 'showInformationMessage', 'SYS_Dialog.showInformationMessage()'],
  [eda.sys_Dialog, 'showConfirmationMessage', 'SYS_Dialog.showConfirmationMessage()'],
  [eda.sys_Dialog, 'showInputDialog', 'SYS_Dialog.showInputDialog()'],
  [eda.sys_Dialog, 'showSelectDialog', 'SYS_Dialog.showSelectDialog()'],
  [eda.sys_Message, 'showToastMessage', 'SYS_Message.showToastMessage()'],
  [eda.sys_LoadingAndProgressBar, 'showProgressBar', 'SYS_LoadingAndProgressBar.showProgressBar()'],
  [eda.sys_LoadingAndProgressBar, 'destroyProgressBar', 'SYS_LoadingAndProgressBar.destroyProgressBar()'],
  [eda.sys_Environment, 'getEditorCurrentVersion', 'SYS_Environment.getEditorCurrentVersion()'],
];

export class EdaApiAdapter {
  public assertCoreApiAvailable(): void {
    const missing = REQUIRED_APIS
      .filter(([owner, key]) => (
        typeof owner !== 'object'
        || owner === null
        || typeof (owner as Record<string, unknown>)[key] !== 'function'
      ))
      .map(([, , label]) => label);
    if (missing.length > 0) {
      throw new ExportStepError(
        '兼容性检查',
        `当前 EDA/SDK 缺少所需 API：${missing.join('、')}。请升级嘉立创 EDA 专业版 V3。`,
      );
    }
  }

  public async getCurrentProject(): Promise<IDMT_ProjectItem | undefined> {
    // 官方类和方法：DMT_Project.getCurrentProjectInfo()
    return this.withTimeout(
      eda.dmt_Project.getCurrentProjectInfo(),
      'DMT_Project.getCurrentProjectInfo()',
      30_000,
    );
  }

  public async getAllSchematics(): Promise<Array<IDMT_SchematicItem>> {
    // 官方类和方法：DMT_Schematic.getAllSchematicsInfo()（BETA）
    return this.withTimeout(
      eda.dmt_Schematic.getAllSchematicsInfo(),
      'DMT_Schematic.getAllSchematicsInfo()',
      30_000,
    );
  }

  public async getAllSchematicPages(): Promise<Array<IDMT_SchematicPageItem>> {
    // 官方类和方法：DMT_Schematic.getAllSchematicPagesInfo()（BETA）
    return this.withTimeout(
      eda.dmt_Schematic.getAllSchematicPagesInfo(),
      'DMT_Schematic.getAllSchematicPagesInfo()',
      30_000,
    );
  }

  public async getCurrentDocument(): Promise<IDMT_EditorDocumentItem | undefined> {
    // 官方类和方法：DMT_SelectControl.getCurrentDocumentInfo()（BETA）
    return this.withTimeout(
      eda.dmt_SelectControl.getCurrentDocumentInfo(),
      'DMT_SelectControl.getCurrentDocumentInfo()',
      15_000,
    );
  }

  public async activateSchematicPage(pageUuid: string): Promise<string> {
    // 官方类和方法：DMT_EditorControl.openDocument()
    const tabId = await this.withTimeout(
      eda.dmt_EditorControl.openDocument(pageUuid),
      'DMT_EditorControl.openDocument()',
      30_000,
    );
    if (!tabId) {
      throw new ExportStepError('切换原理图图页', `无法打开图页 UUID ${pageUuid}`);
    }

    // 官方类和方法：DMT_EditorControl.activateDocument()
    const activated = await this.withTimeout(
      eda.dmt_EditorControl.activateDocument(tabId),
      'DMT_EditorControl.activateDocument()',
      30_000,
    );
    if (!activated) {
      throw new ExportStepError('切换原理图图页', `无法激活图页 UUID ${pageUuid}`);
    }

    // 官方类和方法：DMT_Schematic.getCurrentSchematicPageInfo()（BETA）
    const currentPage = await this.withTimeout(
      eda.dmt_Schematic.getCurrentSchematicPageInfo(),
      'DMT_Schematic.getCurrentSchematicPageInfo()',
      15_000,
    );
    if (!currentPage || currentPage.uuid !== pageUuid) {
      throw new ExportStepError(
        '切换原理图图页',
        `图页激活校验失败：期望 ${pageUuid}，实际 ${currentPage?.uuid ?? '未知'}。已中止，避免导出不完整文件。`,
      );
    }
    return tabId;
  }

  public async activateTab(tabId: string): Promise<boolean> {
    // 官方类和方法：DMT_EditorControl.activateDocument()
    return this.withTimeout(
      eda.dmt_EditorControl.activateDocument(tabId),
      'DMT_EditorControl.activateDocument()',
      30_000,
    );
  }

  public async saveCurrentSchematicPage(): Promise<boolean> {
    // 官方类和方法：SCH_Document.save()
    return this.withTimeout(eda.sch_Document.save(), 'SCH_Document.save()', 60_000);
  }

  public async getCurrentPageComponents(): Promise<Array<ISCH_PrimitiveComponent>> {
    // 官方类和方法：SCH_PrimitiveComponent.getAll()（BETA）
    return this.withTimeout(
      eda.sch_PrimitiveComponent.getAll(ESCH_PrimitiveComponentType.COMPONENT, false),
      'SCH_PrimitiveComponent.getAll()',
      60_000,
    );
  }

  public async getBomFile(fileName: string): Promise<File | undefined> {
    // 官方类和方法：SCH_ManufactureData.getBomFile()（BETA）
    return this.withTimeout(
      eda.sch_ManufactureData.getBomFile(fileName, 'xlsx'),
      'SCH_ManufactureData.getBomFile()',
      180_000,
    );
  }

  public async getNetlistFile(
    fileName: string,
    netlistType: ESYS_NetlistType,
  ): Promise<File | undefined> {
    // 官方类和方法：SCH_ManufactureData.getNetlistFile()（BETA）
    return this.withTimeout(
      eda.sch_ManufactureData.getNetlistFile(fileName, netlistType),
      'SCH_ManufactureData.getNetlistFile()',
      180_000,
    );
  }

  public resolveNetlistType(): NetlistSelection {
    try {
      const values = ESYS_NetlistType as unknown as Record<string, ESYS_NetlistType | undefined>;
      if (values.JLCEDA_PRO !== undefined) {
        return { enumKey: 'JLCEDA_PRO', value: values.JLCEDA_PRO };
      }
      if (values.EASYEDA_PRO !== undefined) {
        return { enumKey: 'EASYEDA_PRO', value: values.EASYEDA_PRO };
      }
    }
    catch (error) {
      throw new ExportStepError(
        '网表类型兼容性检查',
        '当前 EDA 未提供 ESYS_NetlistType，无法生成专业版网表。',
        { cause: error },
      );
    }
    throw new ExportStepError(
      '网表类型兼容性检查',
      '当前 EDA 同时缺少 ESYS_NetlistType.JLCEDA_PRO 和 EASYEDA_PRO。',
    );
  }

  public getEditorVersion(): string {
    // 官方类和方法：SYS_Environment.getEditorCurrentVersion()
    return eda.sys_Environment.getEditorCurrentVersion();
  }

  public async getDocumentsPath(): Promise<string> {
    // 官方类和方法：SYS_FileSystem.getDocumentsPath()（BETA）
    return this.withTimeout(
      eda.sys_FileSystem.getDocumentsPath(),
      'SYS_FileSystem.getDocumentsPath()',
      30_000,
    );
  }

  public async createDirectory(path: string): Promise<boolean> {
    // 官方类和方法：SYS_FileSystem.createDirectoryInFileSystem()（BETA）
    return this.withTimeout(
      eda.sys_FileSystem.createDirectoryInFileSystem(path),
      'SYS_FileSystem.createDirectoryInFileSystem()',
      30_000,
    );
  }

  public async saveFileDirect(
    directory: string,
    file: File | Blob,
    fileName: string,
  ): Promise<boolean> {
    // 官方类和方法：SYS_FileSystem.saveFileToFileSystem()（BETA）
    return eda.sys_FileSystem.saveFileToFileSystem(this.asDirectoryUri(directory), file, fileName, true);
  }

  public supportsVerifiedDirectSave(): boolean {
    const fileSystem = eda.sys_FileSystem as unknown as Record<string, unknown>;
    return typeof fileSystem.saveFileToFileSystem === 'function'
      && typeof fileSystem.readFileFromFileSystem === 'function';
  }

  public async readSavedFile(path: string): Promise<File | undefined> {
    // 官方类和方法：SYS_FileSystem.readFileFromFileSystem()（BETA）
    return eda.sys_FileSystem.readFileFromFileSystem(path);
  }

  public async saveFileWithDialog(file: File | Blob, fileName: string): Promise<void> {
    // 官方类和方法：SYS_FileSystem.saveFile()
    await eda.sys_FileSystem.saveFile(file, fileName);
  }

  public getStoredSetting(key: string): unknown {
    // 官方类和方法：SYS_Storage.getExtensionUserConfig()
    return eda.sys_Storage.getExtensionUserConfig(key);
  }

  public async setStoredSetting(key: string, value: unknown): Promise<boolean> {
    // 官方类和方法：SYS_Storage.setExtensionUserConfig()
    return this.withTimeout(
      eda.sys_Storage.setExtensionUserConfig(key, value),
      'SYS_Storage.setExtensionUserConfig()',
      30_000,
    );
  }

  public showProgress(progress: number, title: string): void {
    // 官方类和方法：SYS_LoadingAndProgressBar.showProgressBar()
    eda.sys_LoadingAndProgressBar.showProgressBar(progress, title);
  }

  public destroyProgress(): void {
    // 官方类和方法：SYS_LoadingAndProgressBar.destroyProgressBar()
    eda.sys_LoadingAndProgressBar.destroyProgressBar();
  }

  public showToast(message: string, type: ESYS_ToastMessageType, seconds = 4): void {
    // 官方类和方法：SYS_Message.showToastMessage()
    eda.sys_Message.showToastMessage(message, type, seconds);
  }

  public showInformation(content: string, title: string): void {
    // 官方类和方法：SYS_Dialog.showInformationMessage()
    eda.sys_Dialog.showInformationMessage(content, title, '确定');
  }

  public confirm(
    content: string,
    title: string,
    mainButtonTitle = '继续导出',
    cancelButtonTitle = '取消',
  ): Promise<boolean> {
    return new Promise((resolve) => {
      // 官方类和方法：SYS_Dialog.showConfirmationMessage()
      eda.sys_Dialog.showConfirmationMessage(
        content,
        title,
        mainButtonTitle,
        cancelButtonTitle,
        (confirmed) => resolve(confirmed),
      );
    });
  }

  public promptDirectory(defaultPath: string): Promise<string | undefined> {
    return new Promise((resolve) => {
      // 官方类和方法：SYS_Dialog.showInputDialog()（BETA）
      // 当前 SDK 没有返回绝对路径的“选择目录”API，因此使用官方输入框让用户确认绝对目录。
      eda.sys_Dialog.showInputDialog(
        '请输入或粘贴输出目录的绝对路径：',
        '该目录会保存到扩展设置；直接写入需要在扩展管理中启用“外部交互”权限。',
        '选择 BOM 和网表输出目录',
        'text',
        defaultPath,
        { placeholder: '例如：D:\\EDA_Exports' },
        (value) => {
          const normalized = typeof value === 'string' ? value.trim() : '';
          resolve(normalized.length > 0 ? normalized : undefined);
        },
      );
    });
  }

  public promptSettingFlags(defaultValues: Array<string>): Promise<Array<string> | undefined> {
    return new Promise((resolve) => {
      // 官方类和方法：SYS_Dialog.showSelectDialog()（BETA）
      eda.sys_Dialog.showSelectDialog(
        [
          { value: 'askEveryTime', displayContent: '每次导出时询问目录' },
          { value: 'createProjectSubdirectory', displayContent: '建立 <项目名>_export 子目录' },
        ],
        '选择要启用的导出选项：',
        '可通过“工具 → BOM 和网表导出设置...”再次修改。',
        'BOM 和网表导出设置',
        defaultValues,
        true,
        (value) => resolve(value),
      );
    });
  }

  public async registerExportShortcut(callback: () => Promise<void>): Promise<boolean> {
    // 官方类和方法：SYS_ShortcutKey.registerShortcutKey()（BETA）
    return eda.sys_ShortcutKey.registerShortcutKey(
      ['CONTROL', 'ALT', 'E'],
      '一键导出 BOM 和网表',
      callback,
    );
  }

  public joinPath(directory: string, fileName: string): string {
    const separator = directory.includes('\\') ? '\\' : '/';
    return `${directory.replace(/[\\/]+$/u, '')}${separator}${fileName}`;
  }

  private asDirectoryUri(directory: string): string {
    const separator = directory.includes('\\') ? '\\' : '/';
    return `${directory.replace(/[\\/]+$/u, '')}${separator}`;
  }

  private async withTimeout<T>(
    operation: Promise<T>,
    apiName: string,
    timeoutMs: number,
  ): Promise<T> {
    let timer: ReturnType<typeof setTimeout> | undefined;
    const timeout = new Promise<never>((_, reject) => {
      timer = setTimeout(() => {
        reject(new ExportStepError(
          '等待官方 API',
          `${apiName} 在 ${Math.round(timeoutMs / 1000)} 秒内没有返回。`,
        ));
      }, timeoutMs);
    });
    try {
      return await Promise.race([operation, timeout]);
    }
    finally {
      if (timer !== undefined) {
        clearTimeout(timer);
      }
    }
  }
}

export const api = new EdaApiAdapter();
