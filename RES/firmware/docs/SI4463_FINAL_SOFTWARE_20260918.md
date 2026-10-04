# RES S017 Si4463 最终候选软件说明

> 2026-09-19 更新：本文件为 9 月 18 日基线；之后已修正 IRCAL 初始化等待、增加配置读回检查并烧录实测。当前板上版本、结果与待办以 [实机无线测试记录](SI4463_LIVE_TEST_20260919.md) 为准，不再使用本文件的旧映像作为最新测试版本。

状态：按 2026-09-15 版 `E:/A10-合肥工业大学-ASF.docx` 的安全动作要求完成软件修改；**未接线、未烧录、未通过实物 HIL，不能据此声明整套系统合规或保证过检**。

## 已交付

- 默认 `RES_RADIO_SI4463=1`，两端使用 SPI1、模式 0、约 1 MHz；PA4/nSEL、PA5/SCLK、PA6/SDO、PA7/SDI、PB2/nIRQ、PB3/SDN。PB2 由主循环轮询，不在中断里操作 SPI。
- 导入用户提供的 `radio_config_Si4463.h`，存为 `shared/include/radio_config_Si4463_vendor.h`，保留 WDS 原始配置。来自 `D:/AAAmanual/RES/E02 Si4463 无线串口数据传输/E02 Si4463 无线串口数据传输/Inc/`；头文件标注 Si4463 B1、30 MHz 晶振。这证明配置采用 30 MHz，并非已经测得实物晶振。
- 保留原配置的 GFSK 调制、滤波、同步字和 CRC；原文件先写校准参数，后写最终工作参数，不能仅凭文件头注释判断最终值。
- 最终配置约 433.2 MHz 起始频点、100 kHz 步长，使用 channel 0/1/2，约为 433.2/433.3/433.4 MHz。通过 START_TX/START_RX 的频道参数切换物理频点。频率合法性、占空比和 EIRP 尚未认定。
- 将原例程的 7 字节包改为固定 48 字节 RF 包：首字节为 RES 长度，其后 RES 报文，再补零。可容纳当前 41 字节 HELLO/心跳和 37 字节命令/ACK；超过 47 字节的将被拒绝，不能把未来 61 字节最大协议帧直接发入本版本。
- 使用 SPI READ_CMD_BUFF 轮询 CTS，不要求外接 GPIO1；单次 SPI 超时 2 ms，运行命令 CTS 超时 5 ms，初始化命令 20 ms，并有轮询次数上限。
- 发射异步完成，主循环持续执行安全任务；PACKET_SENT 后切回 RX。CRC 错误丢包；CTS/SPI/芯片/FIFO/发射超时会关断模块并进入安全故障。未接模块时不能获得运行许可。
- PA 输出码改为 `0x10`，不会照搬厂家配置 `0x7F` 最大档。该值不是 dBm，实际功率/天线增益必须测量和核定。

## 安全逻辑修改

1. STOP 锁存后只发送 STOP，停止正常 HELLO/心跳及 GO。STOP 可抢占普通 RF 发射。原 30 ms 连续重发会不断打断约 200 ms 的低速 RF 包，因此 S017 STOP 重复间隔改为 240 ms。
2. 普通报文采用停止等待；ACK 窗口 450 ms、GO 重发间隔 450 ms，GO 等待已有 ACK，不与普通心跳争用无线模块。心跳调度基准仍为 200 ms，但受 2.4 kbit/s 半双工限制，实际有效报文间隔通常约 400 ms，**不能再向 ASF 填写“实际每 200 ms 收到一次心跳”**。
3. 两端安全失联阈值保留 500 ms，未为慢速无线放宽。ACK 超时和安全失联超时是不同概念。车载端在接收报文分派之前检查已到期超时，防止迟到报文掩盖故障。
4. 车载软件急停锁存不再由新的遥控会话清除；重新启动遥控器不能使车载两继电器重新吸合。当前没有新增可被无线或 CAN 调用的复位接口；软件锁存由车载本地重新初始化清除，整车外部非可编程锁存仍须人工复位/LVMS 复位。
5. 运行中检测到遥控会话变化或启动 STOP 报告，释放两路继电器并取消 START。新的会话不自动恢复运行。
6. 乱序旧 READY/GO 不刷新有效时间、不累积 READY 次数。GO 事件计数必须增加，旧计数和重复计数不能再次启动。READY 不延长已经激活的 100 ms START 脉冲。
7. CAN 入队失败、bus-off、本地无线失败在车载端直接锁存故障。CAN 后续恢复不会自行解除锁存。
8. IWDG reload 从 999 改为 499，名义约 500 ms，实际值受 LSI 偏差影响；最终必须测 MCU 故障到触点断开的时延。
9. 低电平继电器定义保留。初始化首先释放两路；无线初始化健康且车载单独待机时 R1 闭合/R2 释放；三次有效 READY 后两路闭合；故障时均释放。R1 单独闭合是否适合实际 SDC/EBS 拓扑，仍须核对实物。
10. 正常状态灯保持常亮；原有 1 s 四灯自检保留，未把上电自检当作通信正常证据。

## 源码与构建

- `shared/include/res_radio_config.h`：默认后端及 RF 时间预算。
- `shared/include/res_si4463_transport.h`：SPI、CTS、配置加载、FIFO、非阻塞 TX、RX、三信道扫描、诊断量；每端仅在 port 翻译单元中编译一次。
- `shared/include/res_transport.h`：S017/旧 UART 后端选择。
- 两端 `res_*_app.c`：安全状态机修复；`res_*_port.c`：实际驱动接入及故障传播。
- CubeMX 两端普通/MDK `.ioc` 已登记 SPI1 和六个引脚，Keil `.uvprojx` 已加入 HAL SPI 源文件。实际板级初始化由 transport 调用，CubeMX 重新生成后应核对这些保留文件和 Keil 包含路径。本次未运行 CubeMX 再生成，也未声称 Keil 实际编译已经验证。
- 补齐 ST 官方 STM32G0 HAL v1.4.7 SPI 依赖，与现有 HAL 版本一致。

构建命令（在 RES 工作目录运行）：

```powershell
./firmware/tools/build_stm32_g0b1_gcc.ps1 -Target remote -OutputRoot firmware/artifacts/si4463_final_20260918
./firmware/tools/build_stm32_g0b1_gcc.ps1 -Target vehicle -OutputRoot firmware/artifacts/si4463_final_20260918
```

输出为该目录下各端 `gcc/RES_*_G0B1.hex/.bin/.elf`。目录中的 FINAL 表示本轮选定源码，不是硬件验收通过标志。旧 E220 HEX 与此版本不兼容，两端必须成对更新。

## 验证和诊断

主机回归包含 11 项测试：Si4463 SPI/FIFO/故障超时模拟、200 ms 单向空中延迟的半双工双端仿真、协议、遥控/车载状态机、四色灯、双端联动、INA226、UART 旧版及 STM8 旧版测试。它们不能替代 RF 实测。

保留 `res_uart_diag` 名字以兼容调试器观察脚本；在 S017 下 TX 计数表示提交发射，不等于发射完成。新增 `res_si4463_diag`：

| 字段 | 含义 |
|---|---|
| ready | 初始化成功且无驱动锁存故障 |
| part / chip_revision | PART_INFO 回读；part 应为 0x4463 |
| configured_xo_hz | 配置的晶振值 30000000，不是测量值 |
| tx_done / rx_packets | 发射完成/硬件 CRC 通过的接收包计数 |
| channel / scans | 当前物理信道索引及扫描计数 |
| tx_busy | RF 发射正在进行 |
| error | 1=SPI失败，2=CTS超时，3=配置表错误，4=芯片型号不符，5=芯片命令/FIFO中断，6=接收 FIFO/缓冲错误，7=发射超时 |

后续台架先核对 part、ready、tx_done、rx_packets，再核对认证 ACK、READY×3、GO 单脉冲、STOP、断电/失联、复位、CAN 断开。动作以触点测量为准，不能用 GPIO 命令位证明触点状态。

## 仍不应声明“已合规”的项目

- 实物尚未接线。30 MHz 晶振、芯片版本、模块 RF 开关 GPIO2/3 连接及电源需实测确认。
- ASF 的 LoRa/LLCC68/STM8 描述必须改成 Si4463/GFSK/SPI。Si4463 不提供 LoRa 调制，软件无法把它变成 LoRa。
- 2.4 kbit/s 参数使双向周期接近 500 ms 安全门限；主机仿真通过但真实延迟余量需要测量。若实测不够，应重新用 WDS 生成更高速率的完整调制/滤波配置，不得只改单个速率寄存器或放宽安全超时。
- 三信道失步扫描已写入，但受干扰时的捕获概率、距离、真实跳频和时间预算仍需 RF/HIL 验收；600 ms 驻留扫描不会延长 500 ms 安全门限，扫描期间失联照常急停。
- 频率、PA 码、功率、带宽、天线和发射占空比须按实际使用许可核定；厂家示例频点不等于合法使用证明。
- 现有演示认证密钥及启动会话生成方式未做本次量产安全 provisioning；正式交付应成对配置专用密钥并验证复位后的防重放，不能将共享演示密钥描述为独立配对安全认证。
- 继电器真实触点反馈、非可编程安全锁存、VCU 150 ms 独立监督、1.5 s 整体断开时限、低电量阈值与整机耐久均须实物证据。

参考：[Silicon Labs AN633](https://www.silabs.com/documents/public/application-notes/AN633.pdf)、[AN632 WDS 配置说明](https://www.silabs.com/documents/public/application-notes/AN632.pdf)、用户提供的配置文件及新版 ASF。
