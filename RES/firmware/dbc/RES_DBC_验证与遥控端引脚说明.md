# RES CAN DBC 验证与遥控端引脚说明

## 1. 文件用途

`RES_CAN_Validation.dbc`严格对应当前固件中的 Classic CAN 合同：

- 总线速率：500 kbit/s；
- `0x510 RES_STATUS`：8 字节，每 50 ms 发送；
- `0x511 RES_GO_EVENT`：新的有效 GO 事件触发发送；
- `0x512 RES_DIAGNOSTIC`：与 GO 事件伴随发送。

DBC 只描述赛车端 RES 到 VCU 的 CAN 数据。遥控端 STM32 与 LoRa 模块之间为 UART，不属于 DBC 描述范围。

## 2. 遥控端 STM32G0B1CBT6 引脚连接

| STM32 引脚 | CubeMX 名称/功能 | 外部连接 | 有效电平与注意事项 |
|---|---|---|---|
| PA9 | USART1_TX | LoRa 模块 RXD | 3.3 V UART，TX 接 RX |
| PA10 | USART1_RX | LoRa 模块 TXD | 3.3 V UART，RX 接 TX；当前 9600 bit/s、8N1 |
| PB6 | I2C1_SCL | INA226 SCL | 外部上拉到 3.3 V，建议 4.7 kΩ |
| PB7 | I2C1_SDA | INA226 SDA | 外部上拉到 3.3 V，建议 4.7 kΩ |
| PA8 | INA_ALERT | INA226 ALERT | 输入上拉；INA226 地址为 0x40 |
| PB0 | GO_BUTTON | GO 检测隔离触点 | 内部上拉，低电平有效 |
| PB1 | STOP_FAULT | 急停/断线检测隔离触点 | 内部上拉，高电平表示 STOP 或线路故障；健康状态必须可靠拉低 |
| PB10 | LED_STATE_BLUE | 4 路继电器/驱动模块 IN1 | 低电平有效；蓝灯表示有效双向链路及状态一致，不等于独立 READY/GO 许可 |
| PB11 | LED_STATE_YELLOW | 4 路继电器/驱动模块 IN2 | 低电平有效；黄灯表示 STOP/故障/未建链 |
| PB12 | LED_SOC_GREEN | 4 路继电器/驱动模块 IN3 | 低电平有效；绿灯表示电池正常 |
| PB13 | LED_SOC_RED | 4 路继电器/驱动模块 IN4 | 低电平有效；红灯表示低电量/电量采样故障 |
| PA13 | SWDIO | J-Link SWDIO | 调试接口 |
| PA14 | SWCLK | J-Link SWCLK | 调试接口 |
| NRST | NRST | J-Link RESET | 建议连接，便于可靠下载与复位 |
| 3V3 | 逻辑电源 | LoRa VIO、INA226 VCC、逻辑侧 | 不应接到 LoRa 的 5 V VCC 引脚 |
| 5V | 模块电源 | LoRa VCC及需要 5 V 的模块 | 最终脱离 USB 工作时必须提供；以实物丝印和说明书为准 |
| GND | 公共参考地 | LoRa、INA226、继电器输入侧、J-Link | 所有数字信号必须共地 |

### 急停检测触点要求

PB1 的软件定义是“低=健康，高=急停或线路故障”。隔离继电器应布置为：健康、线束完整且检测模块有电时，PB1 被触点可靠短接到 GND；急停按下、检测线断开或检测模块掉电时，该短接消失，PB1 由上拉变为高电平。不要只按继电器端子上的 `NC/NO` 名称判断，应使用万用表验证整个回路的最终电平。

### LoRa 模块供电注意事项

台架上 LoRa 模块通过 USB 供电时，PA9/PA10、VIO 与 GND 即可完成逻辑通信。装入遥控器并拔掉 USB 后，还必须给模块的主电源 `VCC` 提供其要求的电压；`VIO` 仅规定 UART/GPIO 的 3.3 V 电平，不能替代模块主电源。禁止同时由 USB 与外部 VCC 反向互供，除非模块说明书明确允许。

## 3. STOP 丢包辅助验证判据

使用 CAN 分析仪导入 DBC并记录 `0x510`。每项测试均检查报文周期约 50 ms，VCU 侧应在超过 150 ms 未收到合法 `0x510` 时置位硬件 `RES_ERROR`。

### A. STOP 至少成功接收一次

急停触发后应观察到：

- `res_state = STOPPED_FAULT`；
- `res_remote_stop = STOP_ACCEPTED`；
- `res_software_latched = SAFETY_LATCHED`；
- `res_relay1_command = OPEN`；
- `res_relay2_command = OPEN`。

同一遥控端会话内再次发送 READY，不得使状态返回 READY，两个继电器命令不得闭合。

### B. 全部 STOP 无线帧均被丢弃

通过测试夹具仅丢弃急停触发后的无线帧，或在急停瞬间屏蔽遥控端射频输出。赛车端应在最后一帧有效无线状态报文后约 500 ms 出现：

- `res_state = STOPPED_FAULT`；
- `res_radio_timeout = TIMEOUT_500MS`；
- `res_software_latched = SAFETY_LATCHED`；
- 两个继电器命令均为 `OPEN`。

这一测试证明安全结果不依赖任一 STOP 帧必须成功到达。

### C. 关键禁止组合

急停锁定后，下列组合在任何一个 `0x510` 周期都不得出现：

```text
res_state == READY
或
res_software_latched == SAFETY_LATCHED 且任一继电器命令 == CLOSED
```

若出现该组合，应判定验证失败，不得用于申诉或装车。

## 4. 限制

该 DBC 能验证赛车端公开给 VCU 的状态和最终安全动作，但不能直接证明 LoRa 空口每一帧的命令字段。若需要证明“急停后遥控端不再生成 READY”，还应同步记录遥控端 UART 原始帧，或在调试固件中输出已经解码的命令、会话号和递增序号；调试信息不得参与安全判定。
