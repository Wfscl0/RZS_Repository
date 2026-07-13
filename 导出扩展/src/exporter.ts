import extensionConfig from '../extension.json';

import { api } from './api-adapter';
import { errorMessage, ExportStepError } from './errors';
import { ExportLogger, type ExportLogMetadata } from './logger';
import { resolveOutputSettings } from './settings';
import type {
  ComponentSnapshot,
  ExportUnit,
  ExtensionSettings,
  SavedFileRecord,
} from './types';

interface ProjectTree {
  schematics: Array<IDMT_SchematicItem>;
  pages: Array<IDMT_SchematicPageItem>;
}

class SaveCoordinator {
  private directEnabled: boolean;

  public constructor(
    public readonly targetDirectory: string,
    private readonly logger: ExportLogger,
  ) {
    this.directEnabled = api.supportsVerifiedDirectSave();
    if (!this.directEnabled) {
      this.logger.warn(
        '当前 EDA 缺少可验证的直接写入 API，将使用 SYS_FileSystem.saveFile() 回退保存。',
      );
    }
  }

  public async save(
    kind: SavedFileRecord['kind'],
    file: File | Blob,
    fileName: string,
  ): Promise<SavedFileRecord> {
    if (this.directEnabled) {
      let written = false;
      try {
        written = await api.saveFileDirect(this.targetDirectory, file, fileName);
      }
      catch (error) {
        this.directEnabled = false;
        this.logger.warn(
          `直接写入 ${fileName} 失败，将回退到系统保存对话框：${errorMessage(error)}`,
        );
      }

      if (this.directEnabled && !written) {
        this.directEnabled = false;
        this.logger.warn(`直接写入 ${fileName} 返回 false，将回退到系统保存对话框。`);
      }

      if (this.directEnabled && written) {
        const fullPath = api.joinPath(this.targetDirectory, fileName);
        let verified: File | undefined;
        let verificationError: unknown;
        try {
          verified = await readSavedFileWithRetry(fullPath, file.size);
        }
        catch (error) {
          verificationError = error;
        }

        if (!verified || verified.size <= 0 || verified.size !== file.size) {
          this.directEnabled = false;
          this.logger.warn(
            `${fileName} 直接写入后回读校验失败（期望 ${file.size} bytes，实际 `
            + `${verified?.size ?? 0} bytes${verificationError ? `，${errorMessage(verificationError)}` : ''}），`
            + '将回退到系统保存对话框。',
          );
        }
        else {
          return {
            kind,
            fileName,
            size: verified.size,
            mode: 'direct',
            verified: true,
            path: fullPath,
          };
        }
      }
    }

    // SYS_FileSystem.saveFile() 会打开原生保存窗口；先移除进度层，避免保存窗口被遮挡。
    api.destroyProgress();
    await api.saveFileWithDialog(file, fileName);
    this.logger.warn(
      `${fileName} 使用 SYS_FileSystem.saveFile() 保存；该官方 API 不返回路径或成功布尔值，无法自动回读。`,
    );
    return {
      kind,
      fileName,
      size: file.size,
      mode: 'fallback',
      verified: false,
    };
  }
}

async function readSavedFileWithRetry(
  fullPath: string,
  expectedSize: number,
): Promise<File | undefined> {
  const retryDelays = [0, 150, 300, 600, 1_000, 1_500, 2_000];
  let latest: File | undefined;
  let latestError: unknown;

  for (const delayMs of retryDelays) {
    if (delayMs > 0) {
      await delay(delayMs);
    }
    try {
      latest = await api.readSavedFile(fullPath);
      latestError = undefined;
      if (latest && latest.size === expectedSize && latest.size > 0) {
        return latest;
      }
    }
    catch (error) {
      latestError = error;
    }
  }

  if (latestError) {
    throw latestError;
  }
  return latest;
}

function delay(milliseconds: number): Promise<void> {
  return new Promise((resolve) => {
    setTimeout(resolve, milliseconds);
  });
}

export async function exportCurrentProject(): Promise<void> {
  const logger = new ExportLogger();
  const savedFiles: Array<SavedFileRecord> = [];
  let originalTabId: string | undefined;
  let logMetadata: ExportLogMetadata | undefined;
  let saveCoordinator: SaveCoordinator | undefined;
  let logFileName: string | undefined;

  try {
    api.assertCoreApiAvailable();
    const currentDocument = await api.getCurrentDocument();
    originalTabId = currentDocument?.tabId;

    const project = await api.getCurrentProject();
    if (!project) {
      throw new ExportStepError('检查当前工程', '当前没有打开工程，请先打开本地 .eprj2 工程。');
    }

    const projectName = sanitizeWindowsFileName(project.friendlyName || project.name);
    logFileName = `${projectName}_ExportLog.txt`;
    const tree = readAndValidateProjectTree(project);
    const units = buildExportUnits(projectName, tree, logger);
    const netlistType = api.resolveNetlistType();

    // 所有需要用户输入的目录对话框必须出现在进度层之前，否则 V3 客户端可能遮挡对话框。
    const settings = await resolveOutputSettings();
    if (!settings) {
      api.showToast('已取消 BOM 和网表导出。', ESYS_ToastMessageType.INFO);
      return;
    }
    api.showProgress(5, '正在准备工程导出...');

    logMetadata = {
      edaVersion: api.getEditorVersion(),
      pluginVersion: extensionConfig.version,
      projectName: project.friendlyName || project.name,
      projectUuid: project.uuid,
      exportedAt: new Date().toISOString(),
      netlistType: `ESYS_NetlistType.${netlistType.enumKey} (${String(netlistType.value)})`,
      schematicCount: tree.schematics.length,
      pageCount: tree.pages.length,
      outputDirectory: settings.outputDirectory,
    };

    logger.info(`工程文档树读取完成：${tree.schematics.length} 个原理图，${tree.pages.length} 个图页。`);
    logger.info(
      '官方 SCH_ManufactureData 文档将导出范围定义为“当前原理图图页”；插件将逐图页激活、校验并导出。',
    );
    logger.info('当前 SDK 未提供未保存状态查询；插件在检查每个图页时调用 SCH_Document.save()。');

    const targetDirectory = await prepareTargetDirectory(projectName, settings, logger);
    logMetadata.outputDirectory = targetDirectory;
    saveCoordinator = new SaveCoordinator(targetDirectory, logger);

    const warnings = await inspectAllPages(units, logger);
    if (warnings.length > 0) {
      for (const warning of warnings) {
        logger.warn(warning);
      }
      // 官方确认框是交互窗口；先销毁进度层，避免窗口被覆盖后看似卡死。
      api.destroyProgress();
      const confirmed = await api.confirm(
        buildWarningMessage(warnings),
        '导出前检查发现问题',
      );
      if (!confirmed) {
        api.showToast('已根据用户选择取消导出。', ESYS_ToastMessageType.INFO);
        return;
      }
      logger.info('用户确认忽略警告并继续导出。');
      api.showProgress(45, '正在准备导出文件...');
    }

    for (let index = 0; index < units.length; index += 1) {
      const unit = units[index];
      const progress = 45 + Math.floor((index / Math.max(units.length, 1)) * 40);
      api.showProgress(progress, `正在导出：${unit.schematic.name} / ${unit.page.name}`);
      await api.activateSchematicPage(unit.page.uuid);

      const bomName = `${unit.fileStem}_BOM.xlsx`;
      const netlistName = `${unit.fileStem}_Netlist.tel`;

      const bomFile = await api.getBomFile(unit.fileStem);
      assertNonEmptyFile(bomFile, '生成 BOM', bomName);
      const netlistFile = await api.getNetlistFile(unit.fileStem, netlistType.value);
      assertNonEmptyFile(netlistFile, '生成网表', netlistName);

      savedFiles.push(await saveCoordinator.save('BOM', bomFile, bomName));
      savedFiles.push(await saveCoordinator.save('Netlist', netlistFile, netlistName));
      logger.info(
        `已导出 ${unit.schematic.name} / ${unit.page.name}：${bomName} (${bomFile.size} bytes)，`
        + `${netlistName} (${netlistFile.size} bytes)。`,
      );
    }

    api.showProgress(90, '正在写入导出日志...');
    const logText = logger.render(logMetadata, savedFiles);
    const logFile = new File([logText], logFileName, { type: 'text/plain;charset=utf-8' });
    savedFiles.push(await saveCoordinator.save('Log', logFile, logFileName));

    api.showProgress(100, 'BOM 和网表导出完成');
    const fallbackUsed = savedFiles.some((file) => file.mode === 'fallback');
    const resultLines = savedFiles
      .filter((file) => file.kind !== 'Log')
      .map((file) => `${file.kind}: ${file.fileName}`);
    api.showInformation(
      [
        'BOM 和网表导出完成',
        '',
        `保存目录：${targetDirectory}`,
        ...resultLines,
        `日志：${logFileName}`,
        ...(fallbackUsed
          ? ['', '部分文件使用了系统保存对话框；其实际目录以对话框中的选择为准，详见日志。']
          : []),
      ].join('\n'),
      '导出完成',
    );
    api.showToast('BOM 和网表导出完成', ESYS_ToastMessageType.SUCCESS, 5);
  }
  catch (error) {
    const step = error instanceof ExportStepError ? error.step : '未预期步骤';
    const message = errorMessage(error);
    logger.error(`${step}: ${message}`);

    if (saveCoordinator && logMetadata && logFileName) {
      try {
        const failureLog = new File(
          [logger.render(logMetadata, savedFiles)],
          logFileName,
          { type: 'text/plain;charset=utf-8' },
        );
        await saveCoordinator.save('Log', failureLog, logFileName);
      }
      catch {
        // 保留原始异常作为用户需要处理的主要错误。
      }
    }

    api.showInformation(
      `失败步骤：${step}\n异常信息：${message}`,
      'BOM 和网表导出失败',
    );
    api.showToast(`导出失败：${step}`, ESYS_ToastMessageType.ERROR, 6);
  }
  finally {
    if (originalTabId) {
      try {
        await api.activateTab(originalTabId);
      }
      catch {
        // 恢复原标签失败不会覆盖导出结果。
      }
    }
    try {
      api.destroyProgress();
    }
    catch {
      // 兼容性检查失败时，进度条 API 本身也可能不存在。
    }
  }
}

function readAndValidateProjectTree(project: IDMT_ProjectItem): ProjectTree {
  const schematicByUuid = new Map<string, IDMT_SchematicItem>();
  for (const item of project.data) {
    if (item.itemType === EDMT_ItemType.BOARD) {
      schematicByUuid.set(item.schematic.uuid, item.schematic);
    }
    else if (
      item.itemType === EDMT_ItemType.SCHEMATIC
      || item.itemType === EDMT_ItemType.CBB_SCHEMATIC
    ) {
      schematicByUuid.set(item.uuid, item);
    }
  }
  const schematics = [...schematicByUuid.values()];
  const pages = schematics.flatMap((schematic) => schematic.page);
  if (schematics.length === 0) {
    throw new ExportStepError('检查工程原理图', '当前工程不包含任何原理图。');
  }

  const schematicUuids = new Set(schematics.map((schematic) => schematic.uuid));
  const orphanPages = pages.filter((page) => !schematicUuids.has(page.parentSchematicUuid));
  if (orphanPages.length > 0) {
    throw new ExportStepError(
      '校验工程文档树',
      `发现 ${orphanPages.length} 个无法关联到原理图的图页，已中止以避免遗漏。`,
    );
  }

  for (const schematic of schematics) {
    if (schematic.page.length === 0) {
      throw new ExportStepError(
        '校验工程文档树',
        `原理图“${schematic.name}”没有可导出的图页，已中止以避免静默遗漏。`,
      );
    }
    const mismatch = schematic.page.some(
      (page) => page.parentSchematicUuid !== schematic.uuid,
    );
    if (mismatch) {
      throw new ExportStepError(
        '校验工程文档树',
        `原理图“${schematic.name}”包含父级 UUID 不一致的图页，已中止导出。`,
      );
    }
  }
  return { schematics, pages };
}

function buildExportUnits(
  projectName: string,
  tree: ProjectTree,
  logger: ExportLogger,
): Array<ExportUnit> {
  const units: Array<ExportUnit> = [];
  const usedStems = new Set<string>();
  const multipleSchematics = tree.schematics.length > 1;

  for (const schematic of tree.schematics) {
    const pages = tree.pages.filter((page) => page.parentSchematicUuid === schematic.uuid);
    for (const page of pages) {
      let fileStem: string;
      if (tree.pages.length === 1) {
        fileStem = projectName;
      }
      else if (multipleSchematics && pages.length === 1) {
        fileStem = `${projectName}_${sanitizeWindowsFileName(schematic.name)}`;
      }
      else {
        fileStem = [projectName, schematic.name, page.name]
          .map(sanitizeWindowsFileName)
          .join('_');
      }

      if (usedStems.has(fileStem.toLocaleLowerCase())) {
        const disambiguated = `${fileStem}_${page.uuid.slice(0, 8)}`;
        logger.warn(`文件名“${fileStem}”发生冲突，已改为“${disambiguated}”。`);
        fileStem = disambiguated;
      }
      usedStems.add(fileStem.toLocaleLowerCase());
      units.push({ schematic, page, fileStem });
    }
  }
  return units;
}

async function inspectAllPages(
  units: Array<ExportUnit>,
  logger: ExportLogger,
): Promise<Array<string>> {
  const snapshots: Array<ComponentSnapshot> = [];
  const warnings: Array<string> = [];

  for (let index = 0; index < units.length; index += 1) {
    const unit = units[index];
    const progress = 10 + Math.floor((index / Math.max(units.length, 1)) * 30);
    api.showProgress(progress, `正在保存并检查：${unit.schematic.name} / ${unit.page.name}`);
    await api.activateSchematicPage(unit.page.uuid);
    const saved = await api.saveCurrentSchematicPage();
    if (!saved) {
      throw new ExportStepError(
        '保存未保存修改',
        `原理图“${unit.schematic.name}”图页“${unit.page.name}”保存失败，请手动保存后重试。`,
      );
    }

    const components = await api.getCurrentPageComponents();
    logger.info(
      `已检查 ${unit.schematic.name} / ${unit.page.name}，共 ${components.length} 个普通器件。`,
    );
    for (const component of components) {
      const designator = (component.getState_Designator() ?? '').trim();
      const primitiveId = component.getState_PrimitiveId();
      const subPartName = component.getState_SubPartName();
      const footprint = component.getState_Footprint();
      const addIntoPcb = component.getState_AddIntoPcb();

      snapshots.push({
        schematicUuid: unit.schematic.uuid,
        schematicName: unit.schematic.name,
        pageName: unit.page.name,
        primitiveId,
        designator,
        subPartName,
        hasFootprint: Boolean(footprint?.uuid),
      });
      if (!designator) {
        warnings.push(
          `${unit.schematic.name} / ${unit.page.name}: 器件 ${primitiveId} 的位号为空。`,
        );
      }
      else if (designator.includes('?')) {
        warnings.push(
          `${unit.schematic.name} / ${unit.page.name}: 器件位号“${designator}”尚未分配。`,
        );
      }
      if (addIntoPcb !== false && !footprint?.uuid) {
        warnings.push(
          `${unit.schematic.name} / ${unit.page.name}: 器件“${designator || primitiveId}”缺少封装。`,
        );
      }
    }
  }

  warnings.push(...findDuplicateDesignators(snapshots));
  return [...new Set(warnings)];
}

function findDuplicateDesignators(snapshots: Array<ComponentSnapshot>): Array<string> {
  const warnings: Array<string> = [];
  const groups = new Map<string, Array<ComponentSnapshot>>();
  for (const snapshot of snapshots) {
    if (!snapshot.designator || snapshot.designator.includes('?')) {
      continue;
    }
    const key = `${snapshot.schematicUuid}\u0000${snapshot.designator.toLocaleUpperCase()}\u0000`
      + `${snapshot.subPartName ?? '<single>'}`;
    const group = groups.get(key) ?? [];
    group.push(snapshot);
    groups.set(key, group);
  }

  for (const group of groups.values()) {
    if (group.length <= 1) {
      continue;
    }
    const first = group[0];
    const pages = [...new Set(group.map((item) => item.pageName))].join('、');
    warnings.push(
      `${first.schematicName}: 位号“${first.designator}”重复 ${group.length} 次（图页：${pages}）。`,
    );
  }
  return warnings;
}

async function prepareTargetDirectory(
  projectName: string,
  settings: ExtensionSettings,
  logger: ExportLogger,
): Promise<string> {
  if (!settings.createProjectSubdirectory) {
    return settings.outputDirectory;
  }
  const target = api.joinPath(settings.outputDirectory, `${projectName}_export`);
  try {
    const created = await api.createDirectory(target);
    if (!created) {
      logger.warn(`创建目录 ${target} 返回 false；仍将尝试直接写入，失败时自动回退。`);
    }
  }
  catch (error) {
    logger.warn(`创建目录 ${target} 时出现异常；写入失败时将自动回退：${errorMessage(error)}`);
  }
  return target;
}

function assertNonEmptyFile(
  file: File | undefined,
  step: string,
  expectedName: string,
): asserts file is File {
  if (!file || file.size <= 0) {
    throw new ExportStepError(step, `${expectedName} 的文件对象为空或大小为 0。`);
  }
}

function buildWarningMessage(warnings: Array<string>): string {
  const displayed = warnings.slice(0, 20);
  const remaining = warnings.length - displayed.length;
  return [
    `共发现 ${warnings.length} 个问题：`,
    '',
    ...displayed.map((warning) => `• ${warning}`),
    ...(remaining > 0 ? [`• 另有 ${remaining} 个问题，完整内容将写入日志。`] : []),
    '',
    '是否仍要继续导出？插件不会修改器件、导线、网络或属性。',
  ].join('\n');
}

export function sanitizeWindowsFileName(value: string): string {
  let sanitized = value
    .replace(/[<>:"/\\|?*\u0000-\u001F]/gu, '_')
    .replace(/[. ]+$/gu, '')
    .trim();
  if (!sanitized) {
    sanitized = '未命名工程';
  }
  if (/^(CON|PRN|AUX|NUL|COM[1-9]|LPT[1-9])(?:\.|$)/iu.test(sanitized)) {
    sanitized = `_${sanitized}`;
  }
  return sanitized.slice(0, 100);
}
