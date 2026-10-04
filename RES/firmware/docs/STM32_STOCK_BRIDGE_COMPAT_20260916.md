# STM32 兼容现有 STM8 演示桥

## 修改内容

在不烧录 LoRa 板 STM8 的前提下，STM32 端增加了一个明确的编译配置 `StockBridgeCompat`：

- 完整 RES UART 帧发送结束后插入 15 ms 空闲，满足厂商桥接程序约 10 ms 的 UART 空闲分帧门限；
- 保持一次只发送一帧和等待 ACK，避免演示 FIFO 收到连续粘包；
- 遥控端心跳周期为 1500 ms，ACK 等待 1800 ms；
- 车载端链路保护超时为 3000 ms，避免低频兼容测试期间被 500 ms 保护提前锁定；
- 不发送伪造 READY/GO，不旁路 STOP、INA226、CAN 或继电器故障。

生产默认配置不受影响：200 ms 心跳、260 ms ACK 窗口和 500 ms 失联保护仍保持原值。

## 已生成候选固件

构建命令：

```powershell
.\firmware\tools\build_stm32_g0b1_gcc.ps1 -Target remote -StockBridgeCompat -OutputRoot artifacts/stock_bridge_compat_20260916
.\firmware\tools\build_stm32_g0b1_gcc.ps1 -Target vehicle -StockBridgeCompat -OutputRoot artifacts/stock_bridge_compat_20260916
```

文件：

- `artifacts/stock_bridge_compat_20260916/remote/gcc/RES_Remote_G0B1.hex`
- `artifacts/stock_bridge_compat_20260916/vehicle/gcc/RES_Vehicle_G0B1.hex`

SHA-256：

- 遥控端：`F578E8DD95D82B019D3ECD84DAEBB3C85DB4B0FAF89B60831BF522BA5DE4169C`
- 车载端：`55EF48F97D25F7868DB7549416164EE254DB9BBC5AF1DAA727D883572EF53A1A`

## HIL 测试边界

此配置是对现有 STM8 演示桥的兼容验证，不是 ASF 正式运行配置。预期现象是 STOP 报文和 ACK 可以在约秒级范围内往返；若车载端本地仍有 STOP、INA226 或 CAN 故障，继电器必须保持安全释放状态。

HIL 前应确认两端固件都使用本目录下的同一兼容配置、两块 STM32 的 SWD 目标无误，并让 USB/CH340 仅用于被动观察，不能向 LoRa 板发送演示数据。若仍无 ACK，继续检查 LoRa 板的 TX/RX 连接和 CH340 输出争用；STM32 代码无法消除板上并联推挽输出。

通过 HIL 观察到 ACK 后，仍需测量最坏往返时间、连续丢包、断电、复位和恢复行为。兼容模式不能用于实际车辆运行，因为它不满足 500 ms 失联约束。
