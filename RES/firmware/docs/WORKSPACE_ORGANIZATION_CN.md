# RES 固件工作区目录整理规范（不执行删除）

> 本文件只定义识别、放置和人工复核规则。本次整理**不移动、不删除、不覆盖**任何已有源码、构建目录、备份、日志或映像。

## 1. 整理目标

这个工作区同时包含 CubeMX/Keil 交付、CubeIDE 历史配置、CMake 主机测试、GCC 临时构建和 STM8 桥接资料。整理的目的不是压缩目录，而是让每一份文件可回答三个问题：

1. 它是不是权威源文件？
2. 它由哪一套工具生成、能否安全重建？
3. 它是否是可追溯的烧录/测试证据？

当答案不明确时，保留文件并标记待核实；不得把“看似重复”当作删除理由。

## 2. 分类规则

| 类别 | 典型位置/文件 | 管理规则 |
|---|---|---|
| 权威配置 | `remote_g0b1/*.ioc`、`vehicle_g0b1/*.ioc`、`MDK-ARM/*.uvprojx`、STM8 IAR 工程 | 受版本控制；改外设时先改/复核 `.ioc`，再生成代码并审查 USER CODE 区域 |
| 应用与共享源码 | `remote_g0b1/Core/`、`vehicle_g0b1/Core/`、`shared/`、`radio_bridge_stm8/` | 受版本控制；共享算法只维护 `shared/` 中的一份实现 |
| 文档/接口合同 | `docs/`、`dbc/`、各端 `Docs/` | 受版本控制；硬件实测变更需同步回写配置和文档 |
| 主机测试与夹具 | `tests/`、`tools/`、根 `CMakeLists.txt` | 受版本控制；结果可作为回归证据但不能替代硬件验证 |
| 当前 HIL 构建证据 | `artifacts/<target>/gcc/`、`artifacts/HIL_BUILD_MANIFEST_20260903.md` | 本次 GNU Arm 10.3 的可复现映像、映射文件和哈希；可作为待烧录候选，仍须完成 HIL |
| 可重建的临时构建 | `build/`、`build-mingw*/`、`*/build-gcc-live/`、Keil `Objects/`、`Listings/` | 默认为生成物；保留当前内容，日后仅由构建工具重建或人工归档后清理 |
| 备份/历史映像 | `backups/`、旧 `.hex/.bin/.axf/.elf/.map`、测试导出日志 | 不假定可删除；须先确认来源、哈希、用途和是否已有归档副本 |
| 发布证据（建议） | 由人工创建的 `release/<YYYYMMDD>_<版本>/` 或受控制品库 | 仅复制已验证的映像与清单；不在源目录手工篡改构建输出 |

## 3. 当前目录的推荐阅读与维护方式

```text
firmware/
├─ remote_g0b1/          遥控端 STM32：CubeMX + Keil 交付入口
├─ vehicle_g0b1/         车载端 STM32：CubeMX + Keil 交付入口
├─ radio_bridge_stm8/    两块 E220 板载 STM8 的 IAR 桥接实现
├─ shared/               无线协议、鉴权、重放、跳频、CAN 打包的唯一源
├─ dbc/                  RES → VCU 的 0x510/0x511/0x512 合同
├─ tests/                不依赖实物的 C 单元测试与 STM8 stub
├─ tools/                可选台架工具（非安全控制器）
├─ artifacts/            本次可重现映像及 SHA-256 构建清单
├─ docs/                 交付、HIL、接口和本整理说明
└─ build* / */build-*    工具自动产生的本地构建树，非源码入口
```

端点工程中的 `Core/Src/res_protocol_build.c` 与
`vehicle_g0b1/Core/Src/res_can_contract_build.c` 是为 IDE/构建系统提供的
包含包装器，实际共享实现仍在 `shared/src/`。修改协议时不要把实现复制到
两个端点目录；只改共享源，再从两个端点重新构建和测试。

## 4. 烧录产物放置规范

### 4.1 日常本机构建

- 本次已生成的 GNU Arm 10.3 映像为 `artifacts/remote/gcc/RES_Remote_G0B1.{hex,bin}` 和 `artifacts/vehicle/gcc/RES_Vehicle_G0B1.{hex,bin}`；重新生成命令和哈希见 `artifacts/HIL_BUILD_MANIFEST_20260903.md`。
- 遥控端 Keil 输出使用 `remote_g0b1/MDK-ARM/Objects/RES_Remote_G0B1.{hex,bin,axf}`。
- 车载端 Keil 输出使用 `vehicle_g0b1/MDK-ARM/Objects/RES_Vehicle_G0B1.{hex,bin,axf}`。
- STM8 输出只保留在其 IAR 工程指定的输出目录，且应有桥接源/频点表版本记录。
- 不把 `.hex/.bin/.axf` 手工复制到 `Core/`、`shared/`、`docs/` 或 DBC 目录；那会混淆源码与构建结果。

### 4.2 可追溯发布（建议流程，不在本次自动创建目录）

一个经过 HIL 评审、可交付给烧录人员的版本可人工归档为：

```text
release/<YYYYMMDD>_<版本或提交短哈希>/
├─ remote/RES_Remote_G0B1.hex
├─ remote/RES_Remote_G0B1.bin
├─ vehicle/RES_Vehicle_G0B1.hex
├─ vehicle/RES_Vehicle_G0B1.bin
├─ stm8/<桥接映像>
├─ manifest.txt
└─ test-evidence/        仅保存脱敏日志、截图和测试结论
```

`manifest.txt` 至少写入：构建日期、提交/工作树状态、硬件版本、Keil/ARM
Compiler/IAR 版本、`.ioc` 哈希、每个映像 SHA-256、STM8 频点表版本、VCU
版本、HIL 记录编号和密钥**指纹**。绝不把密钥原文或可复用访问凭据放进发布目录。

只在所有映像和记录都已复制并校验后，才可由具备负责人权限的人员手动清理本地生成树。清理前应先确认目标路径、保存清单和可重建命令；本规范不授权任何自动删除脚本。

## 5. 避免常见混淆

1. **CubeMX 与 Keil。** `.ioc` 是外设配置的权威入口；Keil 项目负责构建/下载。重新生成后必须审查 `main.c` 的 USER CODE、共享源码包装器、Keil 分组和 include path，不能只看“生成成功”。
2. **CAN 与 E220 UART。** `dbc/` 仅描述车载 RES → VCU 的 CAN。STM32 ↔ E220 是 UART 私有帧，不能用 DBC 推导它的鉴权/重放行为。
3. **继电器命令与物理反馈。** `0x510` byte5 是逻辑命令位，不等于触点反馈。触点状态必须在 HIL 中用万用表、示波器或独立反馈电路证实。
4. **演示密钥与现场密钥。** `RES_DEMO_AUTH_KEY_BYTES` 只能用于公开单元测试/示例。真实 16 字节密钥应在本地受控配置中提供，不能提交、复制到报告或发送到 CAN。
5. **0x511 与启动授权。** `0x511` 是事件，不是无条件启动命令；VCU 必须同时监督新鲜合法 `0x510`、自身 AS Ready 与独立安全条件，并按 session/counter 去重。
6. **主机测试与 HIL。** CMake/MinGW 测试证明部分 C 逻辑；继电器极性、STB、电源复位、射频换频、CAN 超时和硬件锁存必须按 HIL 清单实测。

## 6. 后续人工整理动作（可选）

在不影响当前工作树的前提下，后续维护者可以按以下顺序操作：

1. 先读取 [工作区入口索引](FIRMWARE_WORKSPACE_INDEX_CN.md)，为本次要烧录的目标建立版本记录。
2. 用相应 `.ioc` 复核引脚和时钟，用 Keil 重新构建；将实际输出与 `Objects/` 的哈希写入测试记录。
3. 保留并标识当前 `build*`、`build-gcc-live` 和 `backups` 的来源；若需减小工作区，先迁移到受控归档，再由人工在确认路径后处理。
4. 将 CAN、示波器和 HIL 报告按发布版本归档，文件名包含日期、目标、软件版本和测试编号。
5. 仅在共享实现、端点工程、DBC、VCU 实现和 HIL 文档相互一致后，标记该版本为“待烧录/HIL 已验证”；任何无线法规或赛事合规结论另行评审。

本次仅新增索引和规范文档；没有执行清理、移动或删除，也没有改变任何 STM32/STM8 源码、Keil 配置、构建脚本或烧录产物。
