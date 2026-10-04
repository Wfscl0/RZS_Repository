# RES STM32 兼容现有 STM8 演示桥修改说明

文档日期：2026-09-16  
适用范围：RES 遥控端 STM32G0B1、车载端 STM32G0B1 及现有 E220 LoRa 板  
修改性质：不烧录 LoRa 板 STM8 时的台架/HIL 兼容测试版本

## 1. 修改背景

当前两块 LoRa 板仍运行厂商 STM8 演示桥程序。该程序通过 UART 空闲时间判断一帧结束，再把 UART 数据交给无线模块。RES STM32 端采用约 200 ms 心跳和连续控制报文时，现场出现车载端可收到部分报文、遥控端 ACK 不稳定以及 USB 端出现残帧的现象。

厂商源码中，普通 UART 空闲分帧门限约为 10 个定时计数，500 个定时计数是没有后续字节时的兜底刷新。无线发送仍可能阻塞 STM8 主循环，因此不能把现有演示桥当作具有确定低延迟的透明串口。

## 2. 本次修改目标

在不更换 PCB、不烧录 LoRa 板 STM8 的情况下，STM32 端增加一个兼容配置，让发送节奏符合现有演示桥的分帧方式，用于确认通信链路是否可以在低频条件下稳定往返。

本配置只用于兼容性验证，不改变 RES 的安全判定，也不把秒级链路延迟伪装成 ASF 合格通信。

## 3. 源码修改

### 3.1 UART 帧间空闲

文件：`firmware/shared/include/res_uart_transport.h`

新增编译宏：

```c
#ifndef RES_STOCK_BRIDGE_GAP_MS
#define RES_STOCK_BRIDGE_GAP_MS 0u
#endif
```

使用兼容配置 `RES_STOCK_BRIDGE_GAP_MS=15` 时，每次 `HAL_UART_Transmit()` 成功后调用 `HAL_Delay(15u)`，在完整 RES 帧之间留下大于演示桥约 10 ms 分帧门限的空闲时间，降低两帧合并进入 STM8 FIFO 的概率。

默认值为 0，因此生产默认编译不插入额外延迟。

### 3.2 遥控端兼容时序

文件：`firmware/remote_g0b1/Core/Src/res_remote_app.c`

定义 `RES_E220_STOCK_BRIDGE_TEST=1` 时：

| 参数 | 默认生产值 | 兼容测试值 |
|---|---:|---:|
| 心跳周期 | 200 ms | 1500 ms |
| ACK 等待时间 | 260 ms | 1800 ms |
| 遥控端链路判断 | 500 ms | 3000 ms |

兼容模式仍采用一次一帧、等待 ACK 后再产生下一次周期发送的 stop-and-wait 逻辑。STOP 报文优先级、认证、序号和信道计算保持不变。

兼容模式不发送伪造 READY/GO；本地 STOP、无效电量、故障锁存仍然有效。

### 3.3 车载端兼容时序

文件：`firmware/vehicle_g0b1/Core/Src/res_vehicle_app.c`

定义 `RES_E220_STOCK_BRIDGE_TEST=1` 时，车载端无线有效帧超时从 500 ms 调整为 3000 ms，以便与 1.5 s 的兼容测试周期匹配。

车载端仍检查认证、序号、会话和报文类型；收到 STOP 时释放运行输出并保持故障状态；CAN、本地故障和软件锁存逻辑不变。

### 3.4 编译脚本

文件：`firmware/tools/build_stm32_g0b1_gcc.ps1`

新增参数：

```powershell
-StockBridgeCompat
```

该参数自动传入：

```text
-DRES_E220_STOCK_BRIDGE_TEST=1
-DRES_STOCK_BRIDGE_GAP_MS=15
```

兼容版本单独输出到候选目录，避免覆盖已验证的生产镜像。

## 4. 编译命令

在 RES 根目录执行：

```powershell
.\firmware\tools\build_stm32_g0b1_gcc.ps1 -Target remote -StockBridgeCompat -OutputRoot artifacts/stock_bridge_compat_20260916
.\firmware\tools\build_stm32_g0b1_gcc.ps1 -Target vehicle -StockBridgeCompat -OutputRoot artifacts/stock_bridge_compat_20260916
```

## 5. 已生成固件

- [遥控端 HEX](../../artifacts/stock_bridge_compat_20260916/remote/gcc/RES_Remote_G0B1.hex)
  
  SHA-256：`F578E8DD95D82B019D3ECD84DAEBB3C85DB4B0FAF89B60831BF522BA5DE4169C`

- [车载端 HEX](../../artifacts/stock_bridge_compat_20260916/vehicle/gcc/RES_Vehicle_G0B1.hex)
  
  SHA-256：`55EF48F97D25F7868DB7549416164EE254DB9BBC5AF1DAA727D883572EF53A1A`

链接统计：

| 镜像 | CODE | DATA | BSS |
|---|---:|---:|---:|
| 遥控端 | 21832 B | 24 B | 3688 B |
| 车载端 | 18752 B | 20 B | 3540 B |

## 6. 软件验证结果

- 遥控端和车载端 GNU Arm 交叉编译成功；
- 两个镜像均完成 ELF、HEX、BIN 输出；
- CMake/CTest 主机回归测试 9/9 通过；
- 编译脚本 PowerShell 语法检查通过；
- 没有修改 STM8 固件，没有烧录 LoRa 板；
- 没有修改默认生产配置。

## 7. HIL 测试方法

1. 确认遥控端和车载端分别连接正确的 STM32 调试器，并核对目标角色。
2. 只烧录本说明中同一日期目录下的两个兼容镜像，不能一端使用兼容镜像、另一端使用生产镜像。
3. LoRa 板保持原 STM8 演示固件，STM32 与 LoRa 板的 UART 连接保持正确。
4. USB/CH340 仅用于观察，禁止从串口工具向 LoRa 板发送演示命令。
5. 先上电车载端，再上电遥控端，观察遥控 STOP 报文和车载 ACK 计数。
6. 记录至少 60 s 的 `tx_frames`、`decoded_frames`、`accepted_acks`、`unmatched_acks`、UART 错误和溢出计数。
7. 断开一侧 LoRa 电源，确认车载端在兼容测试超时后进入安全状态；恢复供电后确认不会自动解除软件锁存。
8. HIL 测试期间不要接入真实 SDC/EBS 执行器或可导致车辆启动的负载。

预期结果是：低频 STOP 报文可以出现有效 ACK，且串口错误和 FIFO 溢出不持续增长。兼容模式响应可能达到秒级，不能据此判断满足 ASF 的 500 ms 失联要求。

## 8. 限制和最终方案

本修改只能改变 STM32 发给 STM8 的 UART 节奏，不能改变 STM8 内部的无线空中速率、RF 收发阻塞时间、STM8 FIFO 容量、信道切换实现，也不能消除 CH340 与其他 TX 输出可能造成的电气争用。

因此，若兼容模式仍然无法稳定 ACK，下一步仍需使用支持 STM8 SWIM 的 ST-Link，把桥接固件烧录到两块 LoRa 板。兼容模式不应直接用于车辆正式运行。

生产版本应恢复 200 ms 心跳、260 ms ACK 窗口和 500 ms 失联保护，并在桥接固件和双端协议经过最坏时延、断链、恢复及全部 ASF 失效模式验证后才能发布。
