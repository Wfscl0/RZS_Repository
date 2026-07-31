# VCU TSMaster 台架调试说明

数据库文件：`VCU_TSMaster_Debug.dbc`

## 1. 通道配置

- CAN0：500 kbit/s，只连接电机控制器协议。VCU发送扩展帧 `0x0CFF08EF`（10 ms）和 `0x0CFF09EF`（100 ms）。
- CAN1：500 kbit/s，连接 IPC、RES、AMI、ESP、EPS 以及本说明中的调试报文。
- 均为 Classical CAN，DLC 8；调试报文使用11位标准帧。

同一份 DBC 可以加载到两个通道，但 `0x7A0~0x7B2` 调试帧只能在 CAN1 使用。

## 2. 调试注入报文

| ID | 名称 | 方向 | 建议周期 | 用途 |
|---|---|---|---:|---|
| 0x7A0 | VCU_DBG_Control | TSMaster→VCU | 100 ms | 解锁、总使能和分组使能 |
| 0x7A1 | VCU_DBG_PedalADC | TSMaster→VCU | 100 ms | APP1、APP2、制动模拟量 |
| 0x7A2 | VCU_DBG_AirWheel | TSMaster→VCU | 100 ms | 两路气压和前后轮速传感器频率 |
| 0x7A3 | VCU_DBG_Digital | TSMaster→VCU | 100 ms | HIN1～HIN14数字输入 |
| 0x7B0 | VCU_DBG_Status | VCU→TSMaster | 100 ms | 覆盖状态、模型HIN和模型输出 |
| 0x7B1 | VCU_DBG_PedalEcho | VCU→TSMaster | 100 ms | 模型实际采用的踏板ADC值 |
| 0x7B2 | VCU_DBG_AirWheelEcho | VCU→TSMaster | 100 ms | 模型实际采用的气压和轮速输入 |

任何控制帧或对应数据帧超过500 ms没有刷新，对应覆盖组会自动退出并恢复真实硬件输入。

## 3. 启用步骤

1. 先周期发送 `0x7A1`、`0x7A2`、`0x7A3`，周期设置为100 ms。
2. 在 `0x7A0` 中设置：
   - `Dbg_Unlock = 23205`，即十六进制 `0x5AA5`；
   - `Dbg_MasterEnable = 1`；
   - 根据需要设置 `Dbg_PedalADCEnable`、`Dbg_AirWheelEnable`、`Dbg_DigitalEnable`。
3. 周期发送 `0x7A0`，周期100 ms。
4. 观察 `0x7B0`。`Dbg_ActiveMaster` 以及相应的分组 Active 位应变为1。
5. 对比 `0x7B1/0x7B2` 回显值，确认VCU实际采用了TSMaster发送的数据。

全部启用时，`0x7A0` 的原始数据示例为：

```text
A5 5A 0F 00 00 00 00 00
```

立即退出调试覆盖可发送：

```text
A5 5A 00 00 00 00 00 00
```

也可以停止发送 `0x7A0`，500 ms后自动退出。

## 4. 模拟量含义

### 踏板ADC（0x7A1）

- DBC中直接填写电压，单位V。
- APP1、APP2和制动传感器正常输入范围按0～5 V定义。
- 当前模型使用待标定查表：约0.252 V对应0，约2.000 V对应1；这只是当前占位标定，不代表最终传感器标定。

三个通道均为0.252 V时，原始帧示例：

```text
40 05 40 05 40 05 00 00
```

### 气压与轮速（0x7A2）

- `Dbg_AirPressure1/2`：直接填写MPa，范围0～1 MPa；对应0～10 V气压传感器。
- `Dbg_WheelFront_Hz/Dbg_WheelRear_Hz`：轮速接口暂不使用，调试时保持0；字段仅为后续扩展保留。
- 油压不在该调试帧中；四轮油压必须通过ESP反馈报文 `ESP_T_03(0x13)` 模拟。

两路气压0.6 MPa、轮速保持0时，原始帧示例：

```text
B2 09 B2 09 00 00 00 00
```

## 5. 数字输入（0x7A3）

| HIN | DBC信号 | 当前模型含义 |
|---|---|---|
| HIN1 | Dbg_HIN1_EBSDriverCheck | EBS驾驶员检查 |
| HIN2 | Dbg_HIN2_ShutdownS | Shutdown S |
| HIN3 | Dbg_HIN3_ShutdownE | Shutdown E |
| HIN4 | Dbg_HIN4_OutsideDI8 | 舱外DI8 |
| HIN5 | Dbg_HIN5_InsideDI8 | 舱内DI8 |
| HIN6 | Dbg_HIN6_RunButton | Run按钮 |
| HIN7 | Dbg_HIN7_TSMS | TSMS |
| HIN8 | Dbg_HIN8_ASMS | ASMS |
| HIN9～14 | Dbg_HIN9～14 | 当前模型未使用，保留 |

ASMS同时控制模型独立输出`ebs_watchdog`。台架上可测量VCU接插件PA30（内部由PTA31/FTM5_CH6驱动）：ASMS=0时为0%占空比，ASMS=1时当前配置为10 kHz、50%；该信号不包含在LOX/HOX回显中。

## 6. 其他节点模拟

要走完整状态机，除硬件调试帧外，还需要按场景周期发送：

- `RES_Msg(0x1E4)`：50 ms。`res_xorcheck = Byte0 XOR Byte1`，心跳应变化。
- `IPC_Tx_Msg1(0x11)`、`IPC_Tx_Msg2(0x12)`：建议20 ms。
- `ESP_T_03(0x13)`：20 ms，提供四轮实际油压；生命信号应循环变化。
- `ESP_T_06(0x16)`、`ESP_T_07(0x17)`：需要测试ESP附加反馈时发送。
- `EPS_Send_Msg1(0x401)`、`EPS_Send_Msg2(0x402)`：20 ms。
- `AMI_Tx(0x42)`：20 ms。

供应商ESP数据库中的 `ESP_T_01` 也使用 `0x11`，与当前IPC报文冲突。当前VCU固件明确将CAN1的 `0x11` 作为 `IPC_Tx_Msg1`，因此整合DBC没有重复加入 `ESP_T_01`。

## 7. 观察VCU输出

- CAN0：`MCU1_Rx_Command`、`MCU1_Rx_Command3`。
- CAN1：`ESP_R_00(0x20)`、`AMI_Rx(0x41)`、`EPS_ReceiveMessage(0x469)`、`IPC_Rx_Msg(0x10)`。
- 调试回显：`0x7B0～0x7B2`。

台架调试前应断开实际执行器高压/动力输出，或确保车辆架空并具备独立急停。调试覆盖只用于台架验证，不应在车辆运行时启用。
