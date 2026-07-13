import type { SavedFileRecord } from './types';

type LogLevel = 'INFO' | 'WARN' | 'ERROR';

interface LogEntry {
  time: string;
  level: LogLevel;
  message: string;
}

export interface ExportLogMetadata {
  edaVersion: string;
  pluginVersion: string;
  projectName: string;
  projectUuid: string;
  exportedAt: string;
  netlistType: string;
  schematicCount: number;
  pageCount: number;
  outputDirectory: string;
}

export class ExportLogger {
  private readonly entries: Array<LogEntry> = [];

  public info(message: string): void {
    this.push('INFO', message);
  }

  public warn(message: string): void {
    this.push('WARN', message);
  }

  public error(message: string): void {
    this.push('ERROR', message);
  }

  public render(metadata: ExportLogMetadata, files: Array<SavedFileRecord>): string {
    const fileLines = files.length === 0
      ? ['（尚未生成文件）']
      : files.map((file) => {
          const location = file.path ?? '由系统保存对话框选择';
          return `${file.kind}: ${file.fileName} | ${file.size} bytes | ${file.mode} | `
            + `verified=${file.verified ? 'yes' : 'no'} | ${location}`;
        });
    const warningCount = this.entries.filter((entry) => entry.level === 'WARN').length;
    const errorCount = this.entries.filter((entry) => entry.level === 'ERROR').length;

    return [
      '嘉立创 EDA 专业版 BOM 和网表导出日志',
      '========================================',
      `EDA 版本: ${metadata.edaVersion}`,
      `插件版本: ${metadata.pluginVersion}`,
      `工程名称: ${metadata.projectName}`,
      `工程 UUID: ${metadata.projectUuid}`,
      `导出时间: ${metadata.exportedAt}`,
      `网表类型: ${metadata.netlistType}`,
      `原理图数量: ${metadata.schematicCount}`,
      `图页数量: ${metadata.pageCount}`,
      `目标目录: ${metadata.outputDirectory}`,
      `警告数量: ${warningCount}`,
      `错误数量: ${errorCount}`,
      '',
      '输出文件',
      '--------',
      ...fileLines,
      '',
      '过程记录',
      '--------',
      ...this.entries.map((entry) => `[${entry.time}] [${entry.level}] ${entry.message}`),
      '',
    ].join('\r\n');
  }

  private push(level: LogLevel, message: string): void {
    this.entries.push({ time: new Date().toISOString(), level, message });
  }
}
