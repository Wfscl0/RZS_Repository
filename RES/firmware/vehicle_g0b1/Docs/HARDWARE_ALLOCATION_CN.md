# 车载端硬件分配与 HIL 接线说明

适用工程：`RES_Vehicle_G0B1`；MCU：STM32G0B1CBT6，LQFP48，3.3 V 逻辑。

> **当前版本（2026-09-18）**：默认固件已经改为 S017 Si4463。无线接线以 [S017 接线说明](../../docs/SI4463_S017_HARDWARE_WIRING_MODIFICATION_20260918.md) 为准：PA4=nSEL、PA5=SCLK、PA6=SDO、PA7=SDI、PB2=nIRQ、PB3=SDN。下文 E220/PA9/PA10 仅为旧版资料，不能用于 S017。IWDG 当前 reload=499，名义约 500 ms，实际时延需实测。软件说明见 [最终候选版本](../../docs/SI4463_FINAL_SOFTWARE_20260918.md)。

## 引脚与默认安全状态

| 功能 | STM32 引脚 | CubeMX 配置 | 默认/运行逻辑 | HIL 接线要点 |
|---|---|---|---|---|
| SWDIO | PA13 | Serial Wire | 调试 | 接 SWD/J-Link 的 SWDIO |
| SWCLK/BOOT0 | PA14 | Serial Wire | 调试 | 接 SWCLK；避免无故改 Option Bytes |
| CAN 收发器待机 | PA0 | GPIO 输出 | 高=待机；应用初始化后置低进入正常模式 | 先核对收发器 STB 真值表 |
| E220 UART TX | PA9 | USART1 TX，9600-8-N-1 | 3.3 V UART | 接 E220 `RXD` |
| E220 UART RX | PA10 | USART1 RX，IRQ | 空闲高 | 接 E220 `TXD` |
| CAN RX | PB8 | FDCAN1 RX | Classic CAN，500 kbit/s | 接 CAN 收发器 RXD/MCU RX |
| CAN TX | PB9 | FDCAN1 TX | Classic CAN，500 kbit/s | 接 CAN 收发器 TXD/MCU TX |
| 继电器 1 | PB10 | 推挽输出 | 低电平吸合；复位初始高（释放） | 外加 4.7–10 kΩ 上拉，测 COM/NO 触点 |
| 继电器 2 | PB11 | 推挽输出 | 低电平吸合；复位初始高（释放） | 外加 4.7–10 kΩ 上拉，测 COM/NO 触点 |
| START_OUT | PB12 | 推挽输出 | 高有效；有效 GO 时约 100 ms | 只能接 VCU/逻辑夹具，不能旁路安全判定 |
| FAULT_OUT | PB13 | 推挽输出 | 高有效；故障/未知时有效 | 记录与 VCU `RES_ERROR` 的区别 |

系统时钟为 HSI16 → PLL（/1 ×8 /2）= 64 MHz；IWDG 为 LSI `/32`、reload 999，名义约 1 s。FDCAN 名义时序：prescaler 8、TSEG1 13、TSEG2 2、SJW 2，16 TQ/bit，500 kbit/s，87.5% 采样点，Classic CAN（非 CAN-FD）。

## 连接与安全要求

1. 两路继电器模块按“低触发”设计，但采购批次可能改变真值表。先让 MCU 断电/复位，测继电器线圈和 COM/NO；不以模块 LED 代替触点测量。
2. PB10/PB11 必须有硬件上拉，以保证 MCU 未上电、下载中、复位或 GPIO 未初始化时保持释放。任何测试都先与真实 SDC/动力回路隔离。
3. CAN 收发器与 VCU/CAN 工具共地；物理总线只在两端使用 120 Ω 终端。接入分析仪前确认不会形成第三个终端。
4. PA0 初始高以使 CAN 收发器待机，之后应用置低。若实物收发器的 STB 极性相反，只改 `res_vehicle_board_config.h` 并完整复测，不能在状态机中零散反相。
5. 车载端只发送 RES CAN 状态/事件，不接收 VCU 控制命令。`RES_ERROR` 由 VCU 根据 `0x510` 的合法性和 150 ms 超时驱动，车载 PB13 `FAULT_OUT` 不是该硬件锁存输出。

## HIL 上电测量顺序

1. 以假负载替代真实安全回路。MCU 无电、NRST 低、下载中和 IWDG 复位时，两个继电器触点都必须释放。
2. 仅给车载端供电：记录 PB10/PB11、PB12、PB13、PA0 与触点状态。应用进入 WAIT_LINK 时预期为 R1 逻辑闭合、R2 释放、FAULT_OUT 有效；这项必须确认不造成真实危险。
3. 接 E220 与遥控端，完成新会话 3 次有效 READY 后才检查两路继电器逻辑闭合。
4. 以 CAN 分析仪确认 0x510 标准帧每约 50 ms 发送；再按总 HIL 清单验证 0x511/0x512、150 ms VCU 超时和独立锁存。

## 边界

车载端软件可报告继电器**逻辑命令**，但当前 CAN `RelayBits` 不是物理触点反馈。无独立反馈电路时，不得在 HIL 或赛事材料中将其写成继电器触点已被测得闭合。
