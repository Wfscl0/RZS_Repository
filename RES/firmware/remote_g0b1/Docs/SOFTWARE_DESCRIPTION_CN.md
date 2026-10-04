# 遥控端软件与烧录说明

## 工程入口

| 用途 | 文件/目录 |
|---|---|
| 原始 CubeMX/CubeIDE 配置 | `RES_Remote_G0B1.ioc` |
| Keil 专用 CubeMX 配置副本 | `RES_Remote_G0B1_MDK.ioc` |
| Keil MDK 项目 | `MDK-ARM/RES_Remote_G0B1.uvprojx` |
| Keil 启动向量 | `MDK-ARM/startup_stm32g0b1xx.s` |
| 应用状态机 | `Core/Src/res_remote_app.c` |
| STM32 HAL 适配 | `Core/Src/res_stm32_port.c` |
| INA226 驱动 | `Core/Src/ina226.c` |
| 共享无线协议 | `../../shared/include/res_protocol.h` |

`*_MDK.ioc` 将 CubeMX 目标标为 `MDK-ARM V5.32`，并关闭 `DeletePrevious`，以免重生成时删除已有 CubeIDE 文件。修改外设时以 `.ioc` 为源，生成后必须复核 `main.c` 的 USER CODE 区域和 Keil 项目中 RES 源文件分组。

## 运行架构

软件是无 RTOS 的 HAL 前后台架构：UART1 中断按字节交给协议流解析器；主循环持续调用 `RES_Application_Task()`；在任务内轮询按钮、STOP 检测和 INA226，每约 100 ms 更新电源状态，再调用遥控端状态机并刷新 IWDG。

无线帧由共享实现提供 CRC16、SipHash-2-4 鉴权、会话号、序号/重放窗口和信道索引。实际无线收发由 E220 板载 STM8 桥接完成。`RES_DEMO_AUTH_KEY_BYTES` 仅为公开示例；现场 HIL 必须由本地、未提交的配置提供双方相同的随机 16 字节密钥。

状态机主要行为：

- 上电进入 `STARTUP_STOP`，先检查 STOP 输入与电量测量；
- 输入健康、电量有效且未锁存故障时进入 `READY`；
- 只有鉴权链路有效、车辆端状态一致且 GO 产生上升沿时才发送 GO；
- STOP 输入为高时立即进入 `STOP_LATCHED`，发送高优先级 STOP；松开 STOP 不清除锁存；
- 约每 200 ms 发送 HELLO/HEARTBEAT，并等待 ACK；失链与发送故障影响状态/指示；
- 蓝灯表示链路及状态一致，黄灯表示告警，绿/红灯表示电量状态。灯的具体物理极性由 `res_board_config.h` 的板级宏统一转换。

### 2026-09-11 四灯判据修订

以 `../../docs/FOUR_LAMP_CHANGE_20260911.md` 为本次修订的详细定义与验收清单。

- 蓝灯只由及时匹配本端待确认报文的有效 ACK 维持；反馈状态和继电器命令位必须一致。继电器命令不是实际触点反馈。
- 黄灯还覆盖车载 ACK 的故障标志和状态不一致；蓝灯与黄灯可以同时出现（例如双方确认 STOP），蓝灯不能作为独立 GO 许可。
- GO 首发及重发均要求本端 READY、电量有效且无本端故障、双向链路有效、车辆状态/命令一致且无车辆故障。
- INA226 初始化、型号、配置、校准与转换就绪均检查；采样失效或数据超过 300 ms 未更新进入严重告警。重试不清除 STOP 锁存。
- 阈值仍为 11.1 V/10.5 V；已有有效低电量状态的恢复阈值增加 0.2 V，第一次有效采样按原阈值判断。严重故障进入不延迟。
- 本次没有新增全灯自检、自动解锁、颜色交换或真实继电器强制动作。

## Keil 构建与下载

1. 在 Keil Pack Installer 安装 `Keil::STM32G0xx_DFP@2.1.0`；项目已为 `STM32G0B1CBTx`、128 KB Flash、144 KB SRAM 和 `STM32G0xx_128.FLM` 预置设备信息。
2. 用 Keil MDK 打开 `MDK-ARM/RES_Remote_G0B1.uvprojx`；项目配置为 ARMCC 5、C99、`USE_HAL_DRIVER`、`STM32G0B1xx`。
3. 检查 include path 同时包含 `Core/Inc`、本地 HAL/CMSIS 和 `../../shared/include`；不要另复制一份 shared 源码。
4. Build 后预期输出到 `MDK-ARM/Objects/RES_Remote_G0B1.hex` 与 `.axf`。若需要 `.bin`，用 Keil 的 fromelf 或团队受控脚本由同一 `.axf` 生成。
5. 接 SWDIO、SWCLK、NRST、GND，先读取/保留现有 Option Bytes；仅下载 Flash，不无故修改 RDP 或 BOOT 配置。烧录后先读回/校验再连接 E220。

当前工作区还提供 `../../artifacts/remote/gcc/RES_Remote_G0B1.{hex,bin,elf}`：它由 GNU Arm Embedded Toolchain 10.3 从同一源码构建，便于先行 HIL。它不是 Keil 重新构建的替代证明；测试记录必须写明实际选用的映像、工具链和 SHA-256。

## 调试观察点与限制

- 调试器可读取 `res_uart1_rx_byte_count`、`res_uart1_error_count`、`res_uart1_last_error` 与 `res_uart1_last_rx_byte`；读取时不要暂停长时间影响 IWDG。
- UART 错误回调会尝试重新启动字节接收；持续错误应作为 E220、电平、供电或串口争用故障处理。
- 当前 INA226 使用固定分流/阈值参数；电池、分流电阻或量程改变后必须重新标定并复测 STOP/低电量边界。
- 通过本端编译或串口建链不证明实际跳频、距离、抗干扰或整车安全合格；执行 `../../docs/HIL_TEST_CHECKLIST_CN.md` 后再扩大测试。
