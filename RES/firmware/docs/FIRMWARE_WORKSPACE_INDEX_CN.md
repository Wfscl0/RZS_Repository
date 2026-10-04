# RES 固件工作区入口索引

> 面向烧录、联调和 HIL 操作。先从本页定位“权威配置”和“生成产物”，不要从历史构建目录或截图中猜测当前软件版本。

## 1. 推荐阅读顺序

1. [软件交付与烧录说明](DELIVERY_CN.md)：系统组成、基础接线、状态逻辑和既有注意事项。
2. 本工作区内两个端点的 `Docs/HARDWARE_ALLOCATION_CN.md` 与 `Docs/SOFTWARE_DESCRIPTION_CN.md`：端点专属引脚、Keil/CubeMX 工程和烧录步骤。
3. [CAN DBC 验证与遥控端引脚说明](../dbc/RES_DBC_验证与遥控端引脚说明.md) 与 `../dbc/RES_CAN_Validation.dbc`：车载 RES → VCU CAN 合同。
4. 同级 VCU 项目的 `VCU/RES_CAN_MIGRATION_AGENT_BRIEF.md`：VCU 需要怎样替换旧 `res_msg[8]` 逻辑并实现 150 ms 监督、GO 去重与故障安全。
5. [HIL 测试总说明与检查表](HIL_TEST_CHECKLIST_CN.md)：通电、CAN 注入、故障注入和证据保存。
6. [工作区目录整理规范](WORKSPACE_ORGANIZATION_CN.md)：识别源文件、生成文件、备份和发布映像，且不执行删除。

若两个文件或截图对同一接口有不同表述，优先级为：当前 `.ioc` / 源码中的硬件配置、`shared/include` 的协议合同、DBC、端点软件说明、交付说明、历史构建产物。真实硬件测量可以发现配置错误，但不能在没有回写工程文件和记录的情况下反向成为“新合同”。

## 2. 目录与职责

| 位置 | 内容 | 操作原则 |
|---|---|---|
| `remote_g0b1/` | 遥控端 STM32G0B1 工程：按键、STOP 检测、INA226、指示灯、E220 UART | `RES_Remote_G0B1_MDK.ioc` 是本次保留 CubeIDE 原配置后新增的 CubeMX/Keil 配置入口；`MDK-ARM/RES_Remote_G0B1.uvprojx` 是 Keil 构建入口；先读其 `Docs/` |
| `vehicle_g0b1/` | 车载端 STM32G0B1 工程：E220 UART、两继电器、START/FAULT、FDCAN | `RES_Vehicle_G0B1_MDK.ioc` 是本次保留 CubeIDE 原配置后新增的 CubeMX/Keil 配置入口；`MDK-ARM/RES_Vehicle_G0B1.uvprojx` 是 Keil 构建入口；先读其 `Docs/` |
| `radio_bridge_stm8/` | E220 板载 STM8L151G4 桥接代码与 IAR 覆盖说明 | 两块桥接板必须烧录同一实现、同一频点表；桥接层不保存认证密钥 |
| `shared/` | 两端共用的编码、CRC16、SipHash、重放窗口、跳频和 CAN 打包合同 | 只在这里修改共享协议；端点下的 `*_build.c` 是构建包装器，避免复制多份实现 |
| `dbc/` | `RES_CAN_Validation.dbc` 和 CAN/HIL 说明 | 车载 RES → VCU 仅有 `0x510/0x511/0x512` 三帧；导入 CANDB++/分析仪前保持编码和版本可追溯 |
| `tests/` | 协议、遥控端、车载端主机单元测试与 STM8 host stub | 主机测试不代表已完成继电器、射频或 VCU HIL 验证 |
| `tools/` | 可选的 Windows 串口台架程序等辅助工具 | 只用作测试夹具；不能取代车载端的认证和安全逻辑 |
| `artifacts/` | 本次 GNU Arm 10.3 的可复现 STM32 映像与映射文件 | 由 `tools/build_stm32_g0b1_gcc.ps1` 生成；使用前核对 `HIL_BUILD_MANIFEST_20260903.md` 的哈希 |
| `docs/` | 跨端交付、接口、HIL 和整理说明 | 每次发布映像前用这里的清单生成/更新测试记录 |
| `build*`、`*/build-gcc-live/` | CMake/GCC 主机测试或本机交叉编译的生成目录 | 不是默认 Keil 发布源；保留作证据或本地缓存，按整理规范处理 |

## 3. 固件与烧录产物入口

| 目标 | CubeMX 配置 | Keil 项目 | 预期本地构建产物 | 烧录接口 |
|---|---|---|---|---|
| 遥控端 STM32G0B1CBT6 | `remote_g0b1/RES_Remote_G0B1_MDK.ioc` | `remote_g0b1/MDK-ARM/RES_Remote_G0B1.uvprojx` | 当前：`artifacts/remote/gcc/RES_Remote_G0B1.hex`、`.bin`；Keil 重建后：`remote_g0b1/MDK-ARM/Objects/` | J-Link/SWD（SWDIO、SWCLK、NRST、GND） |
| 车载端 STM32G0B1CBT6 | `vehicle_g0b1/RES_Vehicle_G0B1_MDK.ioc` | `vehicle_g0b1/MDK-ARM/RES_Vehicle_G0B1.uvprojx` | 当前：`artifacts/vehicle/gcc/RES_Vehicle_G0B1.hex`、`.bin`；Keil 重建后：`vehicle_g0b1/MDK-ARM/Objects/` | J-Link/SWD（SWDIO、SWCLK、NRST、GND） |
| 遥控端 E220 STM8L151G4 | `radio_bridge_stm8/README.md` 指定的 Ebyte/IAR 工程 | Ebyte IAR `project.eww` | 由 IAR 输出目录生成的 STM8 映像 | SWIM + RESET |
| 车载端 E220 STM8L151G4 | 同上 | 同上 | 与遥控端桥接板使用同一版本的映像 | SWIM + RESET |

`.hex`、`.bin`、`.axf` 是**构建输出**，不是手工编辑的源文件。本次已用 `tools/build_stm32_g0b1_gcc.ps1` 以 GNU Arm Embedded 10.3 生成两份可烧录映像，文件大小与 SHA-256 记录在 `artifacts/HIL_BUILD_MANIFEST_20260903.md`。之后若使用 Keil 重新构建，也必须另外记录 Keil/编译器版本和新产物哈希；旧 `build-gcc-live` 或 `build-mingw*` 内文件仅能作为历史参考。

本机还提供 `tools/flash_stm32_g0b1_jlink.ps1`。它无 `-Program` 参数时只校验映像；显式添加 `-Program` 才会经 SWD 写入，并默认让 MCU 保持暂停。真实安全回路隔离和假负载检查仍是烧录前置条件。

## 4. 协议入口

### 4.1 无线端点协议

- 权威头文件：`shared/include/res_protocol.h`。
- 帧包含版本、源/目的节点、flags、信道、序号、会话号、长度、CRC16 与 SipHash-2-4 标签。
- 两端必须使用相同的**本地未提交** 16 字节认证密钥。仓库中的 `RES_DEMO_AUTH_KEY_BYTES` 是公开示例，不能用于实际 HIL/车辆。
- 两端和两个 STM8 桥接板采用相同的三信道跳频规则；桥接板负责物理切频和扫描，终端 STM32 才做鉴权、重放保护和安全状态判断。

### 4.2 车载 RES → VCU CAN 协议

| ID | 名称 | 发送时机 | VCU 规则 |
|---:|---|---|---|
| `0x510` | `RES_STATUS` | 50 ms 周期 | 11 位标准 CAN、DLC=8；大于 150 ms 未收到合法帧、版本/保留位错误、非 READY/GO_EVENT、任何故障语义或继电器不一致均为 `RES_ERROR` |
| `0x511` | `RES_GO_EVENT` | 每次新的有效 GO 一次 | 以 `(remote_session, command_counter)` 去重；仅在最新 `0x510` 新鲜且 READY、VCU 自身 AS Ready/独立条件满足时产生一次 GO |
| `0x512` | `RES_DIAGNOSTIC` | 随 GO 事件发出 | 仅记录/交叉检查，绝不作为 GO 命令 |

详细字节位定义见 `dbc/RES_CAN_Validation.dbc`。VCU 实施说明已经复制到同级项目的 `VCU/RES_CAN_MIGRATION_AGENT_BRIEF.md`；它不属于本 RES 固件构建树。

## 5. 快速验证入口

| 目标 | 入口/资料 | 边界 |
|---|---|---|
| 主机单元测试 | `CMakeLists.txt`、`tests/` | 验证协议和状态机逻辑；不接触真实外设 |
| 遥控端串口台架 | `tools/res_serial_vehicle_harness.c` | Windows 测试夹具以安全 STOP ACK 回应；不等于车载端 HIL |
| CAN 解码/注入 | `dbc/RES_CAN_Validation.dbc` | 用 CANDB++ 或等效工具；注入非法帧时保持安全回路隔离 |
| 系统 HIL | `docs/HIL_TEST_CHECKLIST_CN.md` | 需要真实端点、桥接板、CAN/VCU HIL、示波器和人工安全措施 |

## 6. 版本与密钥的最小记录

每一次可烧录版本至少记录：源代码提交/工作树状态、两份 `.ioc` 哈希、Keil/编译器版本、两个 STM32 映像 SHA-256、桥接映像/频点表版本、VCU 版本和密钥**指纹**。不记录密钥明文。

生成文件与长期证据的放置规则见 [工作区目录整理规范](WORKSPACE_ORGANIZATION_CN.md)。当前工作区已有历史构建和备份；本索引不要求、也不会删除或移动它们。
