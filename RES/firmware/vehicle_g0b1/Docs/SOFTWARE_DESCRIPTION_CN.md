# 车载端软件与烧录说明

## 工程入口

| 用途 | 文件/目录 |
|---|---|
| 原始 CubeMX/CubeIDE 配置 | `RES_Vehicle_G0B1.ioc` |
| Keil 专用 CubeMX 配置副本 | `RES_Vehicle_G0B1_MDK.ioc` |
| Keil MDK 项目 | `MDK-ARM/RES_Vehicle_G0B1.uvprojx` |
| Keil 启动向量 | `MDK-ARM/startup_stm32g0b1xx.s` |
| 车辆状态机 | `Core/Src/res_vehicle_app.c` |
| STM32 HAL/输出/CAN 适配 | `Core/Src/res_vehicle_stm32_port.c` |
| CAN 字节合同 | `../../shared/include/res_can_contract.h` |
| 无线协议 | `../../shared/include/res_protocol.h` |

`*_MDK.ioc` 仅是针对 Keil 的 CubeMX 配置副本，设置 `MDK-ARM V5.32` 且关闭 `DeletePrevious`，以保留原始 CubeIDE 工程。外设变更后需要重新检查 Keil 项目中自定义 RES 源文件、共享包装器与 include path。

## 运行架构和状态机

本端为 HAL 前后台架构：USART1 接收中断将 E220 串口字节交给无线协议流解析器；主循环调用 `RES_Vehicle_Application_Task()`，执行车载状态机、50 ms CAN 状态发送和 IWDG 刷新。FDCAN 配为只发送 RES 相关标准帧，CAN 过滤器拒绝无关接收流量。

状态机由 `res_vehicle_app.c` 实现：

- 启动后进入 WAIT_LINK：R1 逻辑闭合、R2 释放、FAULT_OUT 有效；
- 新的、经鉴权的遥控会话连续 3 帧 READY 后才进入 READY：两路继电器逻辑闭合、FAULT_OUT 无效；
- 新 GO 命令计数仅接受一次：START_OUT 高有效约 100 ms，随后回到 READY；
- STOP、无线有效帧超过约 500 ms 未到、或被报告的本地故障时进入 STOPPED_FAULT：两路继电器释放、START_OUT 低、FAULT_OUT 有效并软件锁存；
- 同会话的后续 READY 不得清锁存；只有新的鉴权会话、无本地故障且再次完成 READY 确认才允许软件状态恢复。

CAN 输出为 Classic CAN、标准 ID、DLC=8：`0x510 RES_STATUS` 约每 50 ms；`0x511 RES_GO_EVENT` 每个新 GO 一次；`0x512 RES_DIAGNOSTIC` 与 GO 事件关联。VCU 不得单独按 0x511 启动，必须按 `VCU/RES_CAN_MIGRATION_AGENT_BRIEF.md` 验证新鲜合法 0x510、READY、session/counter 去重及自己的安全前置条件。

## Keil 构建与下载

1. 在 Keil Pack Installer 安装 `Keil::STM32G0xx_DFP@2.1.0`；项目选择 `STM32G0B1CBTx`、128 KB Flash、144 KB SRAM，并引用 `STM32G0xx_128.FLM`。
2. 打开 `MDK-ARM/RES_Vehicle_G0B1.uvprojx`；项目配置为 ARMCC 5、C99、`USE_HAL_DRIVER` 与 `STM32G0B1xx`。
3. 复核 `Application/RES` 分组含 `res_protocol_build.c`、`res_can_contract_build.c`、`res_vehicle_app.c`、`res_vehicle_stm32_port.c`；这些包装器使 IDE 使用唯一的 `shared/` 实现。
4. Build 后预期产物为 `MDK-ARM/Objects/RES_Vehicle_G0B1.hex` 和 `.axf`；如需 `.bin`，由同一 `.axf` 生成并记录哈希。
5. 接 SWDIO、SWCLK、NRST、GND；在假负载状态烧录并校验后，先测复位/掉电时继电器触点释放，再接无线和 CAN。

当前工作区另提供 `../../artifacts/vehicle/gcc/RES_Vehicle_G0B1.{hex,bin,elf}`，由 GNU Arm Embedded Toolchain 10.3 从同一源码构建，便于本轮 HIL 起步。它与 Keil 构建产物必须分别记录，不能在没有哈希和工具链记录时互相替代。

## 已知 HIL 关注点

- `0x510` 反映车载软件的状态/输出命令；不是继电器物理触点反馈。
- CAN 写失败和 CAN bus-off 必须按 `../../docs/HIL_TEST_CHECKLIST_CN.md` 做故障注入，确认车载安全状态、VCU 150 ms `RES_ERROR` 和独立硬件锁存均符合预期；目前不能以源代码审查代替该测量。
- 认证失败统计和继电器实体反馈尚未完整接入所有 DBC flag，相关 flag 的 VCU 处理仍应按“置位即故障”实现。
- `RES_DEMO_AUTH_KEY_BYTES` 是公开样例。实际 HIL 必须使用双方一致、未提交的队内密钥；禁止通过关闭鉴权来调试。
- 本工程不产生 `RES_ERROR`，更不能用软件清除独立硬件锁存。恢复流程必须包含外部人工复位或 LVMS 断电，具体按硬件设计执行。
