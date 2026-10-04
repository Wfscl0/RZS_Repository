# LoRa 隔离测试记录

当前仅 MCU 与 LoRa 上电。急停、电量未接导致的 STOP 不作为无线测试失败依据。

本次新增 RES_RADIO_STOP_BENCH 编译开关和 build_stm32_g0b1_gcc.ps1 的 -RadioStopBench 参数，仅允许 remote 目标及独立 OutputRoot。该版本强制 STOP，不发送 READY/GO；每2秒发送一次STOP，ACK接受窗口1800ms，车载端500ms安全超时未改变。默认正式编译行为保持不变。

测试固件位于 firmware/artifacts/stop-radio-bench-20260914/remote/gcc。烧录及 verifybin 成功。新增测试确认健康输入及反复GO按下均只能发送STOP、周期不短于2秒；全部8项主机回归通过。

## 实机结果

基线：遥控端8秒发送829→860，接收58不变；车载端接收46不变，发送0。

慢速测试：遥控端8秒发送10→14，接收0；车载端接收46不变，发送0。

用户确认两块LoRa重新断电上电后：遥控端发送13→17、接收58不变、有效ACK0；车载端接收49不变、发送0。接收发生于启动约0.13秒，随后无新增。

结论：只改慢速发送与重新上电不能恢复RF闭环。不能由UART发送成功断言模块已收到数据，也不能由无数据区分STM32 TX线路、模块模式和RF参数。此前已捕获PingPong演示文字，两块无线板实际桥接固件及运行模式仍需检查。

## 交付状态

慢速测试结束后恢复遥控端 firmware/artifacts/asf-uart-20260912/remote/gcc/RES_Remote_G0B1.hex 并校验。车载端未改写。正常通信尚未验收通过，不能将临时2秒STOP测试版投入正式RES使用。

下一步需要直接访问LoRa板载STM8的SWIM接口或模块独立串口，确认模块收到MCU数据及实际RF固件配置。当前两路J-Link连接的是STM32 SWD，不能直接改写无线板STM8。未进行读保护解除、伪造ACK或强制READY。

## Micro-USB 直接串口检查

两块 USB VID_1A86/PID_7523 设备原先缺少驱动。安装官方 CH341SER 驱动后，设备管理枚举为 COM3、COM4，状态 Started，驱动 oem51.inf。

两端串口均成功以 9600、8N1 打开，DTR/RTS 关闭，仅接收观察 12 秒，两端均无新增数据。串口打开成功只能证明电脑到 USB 串口芯片的访问正常；静默不能证明无线失效，也未捕获上电日志。未发送测试数据，未修改 MCU 或 LoRa 固件。

下一步需确认两块 LoRa 与 STM32 的 TX/RX 信号线均已暂时断开，避免 USB 串口 TX 与 STM32 TX 同时驱动模块 RX。确认后再做 USB 串口双向发送、对端接收比对，并根据实际回显判断演示固件模式。

### USB 双向空口复测结果

在 STM32 与 LoRa 的 TX/RX 线断开、仅保留两块 LoRa 的 Micro-USB 供电和天线时，以 COM3/COM4 各发送一次唯一 ASCII 帧，结果如下：

| 方向 | 结果 | 串口表现 |
|---|---|---|
| COM3 → COM4 | PASS | 约 459 ms 后收到 `Receive Data:RESCHK_A_...` |
| COM4 → COM3 | PASS | 约 461 ms 后收到 `Receive Data:RESCHK_B_...` |

因此两块 LoRa 模块的 USB 串口、射频收发和当前空口参数均正常。约 460 ms 为现有演示固件的处理/收发延迟，接收文本分为两段到达属于正常串口分包。后续故障定位范围收敛到 STM32↔LoRa 的 TX/RX 接线、电平/共地、STM32 UART 配置或 RES 二进制帧与演示固件协议不兼容；不能再把问题归因于 LoRa 射频链路本身。

### MCU 已接回 USART 后的复测

在两块 J-Link 和两块 LoRa Micro-USB 均保持连接、STM32↔LoRa USART 接回后，被动监听 12 秒发现 COM4 持续收到 RES 二进制帧（约每 500–600 ms 一帧），COM3 无回传。遥控端诊断由 TX frames 665 增至 696、RX bytes 保持 0；车载端 TX frames 保持 0、RX bytes 保持 0、状态仍为 WAIT_LINK。由此确认遥控 STM32 正在发帧且至少有一块 LoRa 串口输出在工作，但车载 STM32 没有收到任何 UART 字节；当前故障点在车载侧 LoRa TXD→STM32 PA10（或共地/电平/接插件），而不是射频空口。

### TX/RX 修正后的复测

用户修正接线后再次上电复测：COM4 仍持续收到 RES 二进制帧；遥控端 TX frames 在 8 秒内由 1601 增至 1636、RX bytes 仍为 0；车载端 RX bytes 由 4939 增至 5440，TX frames 由 57 增至 64，UART errors/overflow 均为 0。车载端已能收到并处理遥控 STOP 帧，并向 LoRa 发送 ACK/反馈，但遥控端仍收不到任何回传。因此单向 **遥控→车载已恢复**，剩余故障收敛为 **车载 LoRa→遥控 STM32 接收回路**（优先检查遥控侧 LoRa TXD→PA10、遥控侧 GND，以及遥控 LoRa 的 RXD←PA9 发射线）。
