# 一键导出 BOM 和网表

面向嘉立创 EDA 专业版 V3 客户端的 TypeScript 扩展。扩展在顶部菜单注册“工具 → 一键导出 BOM 和网表”，并在激活时注册 `Ctrl+Alt+E`。

## 功能

- 检查当前工程、原理图和图页，并通过官方详细工程树读取完整层级，避免静默遗漏。
- 导出 XLSX BOM、嘉立创 EDA 专业版网表（`.tel`）和 UTF-8 文本日志。
- 网表类型优先使用 `ESYS_NetlistType.JLCEDA_PRO`，旧版运行时缺少该枚举成员时回退到 `EASYEDA_PRO`。
- 首次运行要求确认绝对输出目录，并通过 `SYS_Storage` 保存上次目录。
- 支持“每次导出时询问目录”和“建立 `<项目名>_export` 子目录”。
- 直接写入失败时，逐文件回退到官方 `SYS_FileSystem.saveFile()` 保存对话框。
- 导出前保存并检查每个图页，警告空位号、含 `?` 的未分配位号、缺失封装和重复位号；用户可以取消或继续。
- 直接写入后等待文件系统刷新并多次回读核对大小；仍无法校验时自动回退到系统保存对话框。日志记录版本、UUID、时间、文件名、大小、网表类型、图页数量、警告和错误。
- 使用进度条、消息框和 Toast；同一时刻只允许一个导出任务。
- 不解析或修改 `.eprj2` 数据库，不修改器件、导线、网络或属性。

## 官方 API 核对结果

本工程基于官方 `pro-api-sdk` 1.3.2 的构建结构和 `@jlceda/pro-api-types` 0.3.4 类型定义编写。2026-07-13 核对到的关键签名如下：

```ts
SCH_ManufactureData.getBomFile(
  fileName?: string,
  fileType?: 'xlsx' | 'csv',
  // 其余可选参数省略
): Promise<File | undefined>;

SCH_ManufactureData.getNetlistFile(
  fileName?: string,
  netlistType?: ESYS_NetlistType,
): Promise<File | undefined>;

SYS_FileSystem.saveFileToFileSystem(
  uri: string,
  fileData: File | Blob,
  fileName?: string,
  force?: boolean,
): Promise<boolean>;

SYS_FileSystem.saveFile(
  fileData: File | Blob,
  fileName?: string,
): Promise<void>;
```

参考资料：

- [官方 pro-api-sdk](https://github.com/easyeda/pro-api-sdk)
- [官方 pro-api-types 说明](https://prodocs.lceda.cn/cn/api/guide/ancillary-projects/pro-api-types.html)
- [SCH_ManufactureData](https://prodocs.lceda.cn/cn/api/reference/pro-api.sch_manufacturedata.html)
- [getBomFile()](https://prodocs.lceda.cn/cn/api/reference/pro-api.sch_manufacturedata.getbomfile.html)
- [getNetlistFile()](https://prodocs.lceda.cn/cn/api/reference/pro-api.sch_manufacturedata.getnetlistfile.html)
- [SYS_FileSystem](https://prodocs.lceda.cn/cn/api/reference/pro-api.sys_filesystem.html)
- [DMT_Schematic](https://prodocs.lceda.cn/cn/api/reference/pro-api.dmt_schematic.html)
- [扩展配置文件](https://prodocs.lceda.cn/cn/api/guide/extension-json.html)

### 导出范围与多原理图策略

官方 `SCH_ManufactureData` 文档明确写明其范围是“当前原理图图页”，并没有提供传入工程、原理图或图页 UUID 的参数。因此本扩展不会假设它默认导出整个工程：

1. 使用 `DMT_Project.getCurrentProjectInfo()` 返回的详细工程树取得全部板子、游离原理图和图页；不再并发等待可能长期不返回的 BETA 全量枚举接口。
2. 使用 `DMT_EditorControl.openDocument()`、`activateDocument()` 逐图页切换。
3. 每次切换后用 `getCurrentSchematicPageInfo()` 校验当前 UUID；校验失败立即中止。
4. 对每个图页分别调用一次 BOM 和网表 API，确保没有图页被遗漏。

文件命名规则：

- 工程只有一个原理图、一个图页：`<项目名>_BOM.xlsx`、`<项目名>_Netlist.tel`
- 多原理图且该原理图只有一个图页：`<项目名>_<原理图名>_BOM.xlsx`、`<项目名>_<原理图名>_Netlist.tel`
- 任一原理图含多个图页：`<项目名>_<原理图名>_<图页名>_BOM.xlsx`、`<项目名>_<原理图名>_<图页名>_Netlist.tel`
- 全工程共用一个 `<项目名>_ExportLog.txt`

多图页时增加图页名是因为官方 API 的公开范围是当前图页；在没有官方合并 API 的情况下，强行合并 XLSX 或网表可能产生不完整或错误数据。

### 当前 SDK 限制

- 类型定义没有“文档是否存在未保存修改”的查询接口。本扩展在检查每个图页时直接调用官方 `SCH_Document.save()`；保存失败则中止并要求用户手动保存。
- 当前 `SYS_FileSystem.openReadFolderDialog()` 只返回所选目录内的文件与相对路径，不返回可用于 `saveFileToFileSystem()` 的绝对目录路径；空目录也无法返回路径。因此本扩展使用官方 `SYS_Dialog.showInputDialog()` 让用户输入或粘贴绝对目录，并保存为扩展设置，没有编造不存在的目录选择 API。
- `SYS_FileSystem.saveFile()` 返回 `Promise<void>`，不返回最终路径或成功布尔值。回退模式只能确认 API 调用没有抛异常，无法自动回读；日志会将其标为 `verified=no`。

## 工程结构

```text
导出扩展/
├─ build/packaged.ts
├─ config/esbuild.common.ts
├─ config/esbuild.prod.ts
├─ src/api-adapter.ts
├─ src/errors.ts
├─ src/exporter.ts
├─ src/index.ts
├─ src/logger.ts
├─ src/settings.ts
├─ src/types.ts
├─ .edaignore
├─ extension.json
├─ package.json
└─ tsconfig.json
```

所有可能随 EDA 版本变化的调用都集中在 `src/api-adapter.ts`，且每个调用旁均标注官方类和方法。

## 构建与打包

要求 Node.js 20.17 或更高版本。

```powershell
cd "D:\git\RZS_Repository\导出扩展"
npm install
npm run typecheck
npm run build
```

`npm run build` 会依次执行 TypeScript 类型检查、ESBuild 编译和 `.eext` 打包。输出文件：

```text
build/dist/jlc-bom-netlist-exporter_v1.0.2.eext
```

只编译、不打包：

```powershell
npm run compile
```

只重新打包：

```powershell
npm run package
```

## V3 安装与调试

1. 打开嘉立创 EDA 专业版 V3 客户端。
2. 进入“高级 → 扩展管理器”。
3. 点击“导入”，选择 `build/dist/jlc-bom-netlist-exporter_v1.0.2.eext`。
4. 在“已安装”列表中启用扩展，并启用“显示在顶部菜单”。
5. 必须开启该扩展的“外部交互”权限，否则直接目录写入会抛错并回退到逐文件保存对话框。
6. 修改代码后重新运行 `npm run build`，在扩展管理器中重新导入生成的包进行调试。

官方 V3 安装说明：[扩展的获取和使用](https://prodocs.lceda.cn/cn/api/user-guide/using-extension.html)。

## 使用

1. 打开包含原理图的本地 `.eprj2` 工程。
2. 点击“工具 → 一键导出 BOM 和网表”，或按 `Ctrl+Alt+E`。
3. 第一次运行时输入输出目录；后续默认复用。
4. 如检查发现问题，在确认框中选择继续或取消。
5. 完成后查看成功窗口中的保存目录、文件列表和日志。
6. 通过“工具 → BOM 和网表导出设置...”修改目录询问和子目录选项。

## BETA API 提醒

`SCH_ManufactureData.getBomFile()`、`SCH_ManufactureData.getNetlistFile()`、直接文件系统写入、文档树枚举和快捷键注册在当前官方文档中包含 BETA/预览 API。嘉立创 EDA 更新后，函数签名、权限要求或运行行为可能变化。升级 EDA 后应先运行 `npm update`、`npm run typecheck`，再用一个包含单图页、多图页和多原理图的测试工程做实机验证。
