# VCU CAN 台架调试流程

适用对象：`Models/DBC_Debug/VCU10.slx`（模型版本 1.43）及独立CAN台架测试副本固件。  
数据库：`DBC/VCU_TSMaster_Debug.dbc`。  
模型基础步长与 CoreApp 周期均为 10 ms。

## 1. 调试前结论与安全限制

当前模型可用于 CAN 输入覆盖、传感器换算、ESP/EPS/RES/IPC 接口和状态机的台架验证。已通过模型检查与调试接口仿真：

- 四组 CAN 覆盖可同时激活，`Dbg_Active*=0x0F`。
- 踏板、气压、轮速和数字输入回显与注入值一致。
- 任一调试报文停止刷新 500 ms 后，对应输入组自动退回真实硬件输入。
- 模型中的调试覆盖及500 ms回退逻辑已完成仿真验证。

连接电机、ESP、EPS 等执行器前必须注意：

1. AS_Emergency会在同一模型周期把TS和电机需求扭矩强制为0。前期仍应断开逆变器高压或断开CAN0，只观察报文。
2. `brake_on` 不是由制动踏板 ADC 判断，而是由 ESP 四轮油压反馈判断。制动踏板 ADC 当前仅完成换算和调试回显。
3. 按当前需求不使用轮速传感器，非调试模式下前后轮速固定为0；`0x7A2`中的轮速字段仅保留，不参与本轮台架验收。
4. Stateflow本地标志均已设置显式初值，避免MIL仿真与嵌入式BSS初值不一致。
5. 数据字典仍保留 `oilprs_*` 信号，但当前有效油压来自ESP `0x013`，这些残留项没有参与生成代码。

## 2. 总线配置

| 通道 | 用途 | 波特率 | 帧类型 |
|---|---|---:|---|
| CAN0 | 电机专用 | 500 kbit/s | 29 位扩展帧 |
| CAN1 | ESP、EPS、RES、IPC、AMI、调试报文 | 500 kbit/s | 11 位标准帧 |

台架两端正确终端时，断电测量 CAN_H 与 CAN_L 之间应约为 60 Ω。初次调试只连接 CAN1；CAN0 与逆变器保持断开。

## 3. 调试报文

### 3.1 TSMaster 发给 VCU

| ID | 名称 | 周期 | 用途 |
|---:|---|---:|---|
| `0x7A0` | `VCU_DBG_Control` | 100 ms | 解锁和各组覆盖使能 |
| `0x7A1` | `VCU_DBG_PedalADC` | 100 ms | APP1、APP2、制动踏板 ADC |
| `0x7A2` | `VCU_DBG_AirWheel` | 100 ms | 两路气压和两路轮速 |
| `0x7A3` | `VCU_DBG_Digital` | 100 ms | HIN1～HIN14 数字输入 |
| `0x013` | `ESP_T_03` | 20 ms | 四轮实际油压、ESP LifeSig |
| `0x011` | `IPC_Tx_Msg1` | 20 ms | ESP 目标压力和自动驾驶扭矩 |
| `0x012` | `IPC_Tx_Msg2` | 20 ms | 转角、速度、任务完成、车速 |
| `0x042` | `AMI_Tx` | 20 ms | 自动驾驶任务选择 |
| `0x1E4` | `RES_Msg` | 50 ms | RES 通信、Go、Stop、心跳和 XOR |
| `0x401` | `EPS_Send_Msg1` | 20 ms | EPS 实际转角和状态反馈 |
| `0x402` | `EPS_Send_Msg2` | 20 ms | EPS 计数和实际角度扩展反馈 |

`Dbg_ControlCounter/Dbg_PedalCounter/Dbg_DigitalCounter` 等载荷字段当前不参与超时判断，可以保持 0。底层在每次正确接收 DLC=8 的报文时自动增加内部接收计数，模型使用该内部计数判断新鲜度。

### 3.2 VCU 输出

| ID | 名称 | 周期 | 主要判据 |
|---:|---|---:|---|
| `0x7B0` | `VCU_DBG_Status` | 100 ms | Active、Requested、HIN、LOX、HOX、Age |
| `0x7B1` | `VCU_DBG_PedalEcho` | 100 ms | 踏板实际选用值和覆盖状态 |
| `0x7B2` | `VCU_DBG_AirWheelEcho` | 100 ms | 气压/轮速实际选用值 |
| `0x020` | `ESP_R_00` | 20 ms | ESP 模式和四轮目标压力 |
| `0x041` | `AMI_Rx` | 20 ms | AS 状态：1/2/4/8/16/32/64 |
| `0x469` | `EPS_ReceiveMessage` | 20 ms | EPS 工作模式、目标角度和回中命令 |
| `0x010` | `IPC_Rx_Msg` | 50 ms | RES/转向状态及任务回传 |
| `0x0BA～0x0BC` | `VCU_JY60_*` | 500 ms | IMU 转发 |

CAN0 另有：

- `0x0CFF08EF`：电机控制命令，10 ms，扩展帧。
- `0x0CFF09EF`：电机参数命令，100 ms，扩展帧。

## 4. 调试覆盖建立

### 4.1 安全初值

先建立四个 100 ms 周期发送项，建议初值如下：

| ID | 物理值/原始数据 | 原始 8 字节示例 |
|---:|---|---|
| `0x7A0` | Unlock=`0x5AA5`，Master=1，Pedal=1，AirWheel=1，Digital=1 | `A5 5A 0F 00 00 00 00 00` |
| `0x7A1` | APP1=1.0 V，APP2=1.0 V，Brake=0.5 V | `D5 14 D5 14 6B 0A 00 00` |
| `0x7A2` | Air1=0.40 MPa，Air2=0.20 MPa，轮速保持0 | `77 06 3B 03 00 00 00 00` |
| `0x7A3` | HIN1、4、5、6、7=1，ASMS=0，其余=0 | `79 00 00 00 00 00 00 00` |

`0x7A1/0x7A2` 的示例值受量化影响，TSMaster 使用 DBC 物理信号编辑时会自动取最近的原始值。

### 4.2 覆盖判据

启动四帧后检查 `0x7B0`：

- `Dbg_RequestedMaster/PedalADC/AirWheel/Digital` 均为 1。
- `Dbg_ActiveMaster/PedalADC/AirWheel/Digital` 均为 1。
- 原始 Byte0=`0x0F`，Byte1=`0x0F`。
- `Dbg_ControlAge` 应在 0～100 ms 附近周期回落。
- `Dbg_ControlRxCount` 应持续变化。

再检查：

- `0x7B1` 的 APP1、APP2、Brake 与 `0x7A1` 一致，`Dbg_EchoPedalActive=1`。
- `0x7B2` 的 Air1、Air2、Front、Rear 与 `0x7A2` 一致。
- `0x7B0.Dbg_EchoHINRaw` 与 `0x7A3` 前两字节一致。

若 Requested=1 而某组 Active=0，说明该组数据帧没有被 CAN1 正确接收、DLC 不是 8，或该组已经超过 500 ms 未刷新。

## 5. 传感器链路测试

### 5.1 踏板

当前 APP 标定关系为：

```text
APP归一化值 = clamp((电压 - 0.252 V) / (2.000 V - 0.252 V), 0, 1)
手动扭矩 = (APP1归一化 + APP2归一化) / 2 × 50 Nm
```

推荐测试点：0.252 V、1.000 V、2.000 V。APP1 与 APP2 归一化偏差达到 0.1 并持续 3 个模型周期（约 30 ms）后，模型将踏板扭矩置 0；两路恢复一致后下一周期解除。

制动踏板不是驾驶员制动请求来源，正常范围内只用于换算和回显；但电压连续约100 ms低于0.1 V或高于4.9 V会置位`brake_fault`，使`brake_on`和ASB安全许可失效，并点亮EBS错误输出。恢复到有效范围约500 ms后解除故障。

### 5.2 气压

两路传感器物理量均为0～1 MPa、输出0～10 V，分别走底板AIN4/AIN5的0～10 V采样通道。模型内部使用bar：

- DBC 0.40 MPa 对应模型内部约 4.0 bar。
- Air1 ≥0.35 MPa 是 ASB 自检条件之一。
- HIN1=1 且Air2（电磁阀下游）≥0.60 MPa时，`ebs_working=1`，在AS状态下会进入Emergency。
- Air2 >0.55 MPa 时，可使手动模式所需的 `ebs_check` 退出故障状态。
- 任一路 ≤0.10 MPa 会点亮 EBS 气压错误逻辑。

### 5.3 轮速

本版暂不使用轮速传感器，手写接口固定向模型提供0。`0x7A2`中的两个轮速字段保留用于后续扩展，本轮调试保持0即可。

## 6. 数字开关操作

HIN 对应关系：

| 位 | 信号 |
|---:|---|
| 0 | EBS Driver Check |
| 1 | Shutdown S |
| 2 | Shutdown E |
| 3 | 舱外 DI8 |
| 4 | 舱内 DI8 |
| 5 | Run Button |
| 6 | TSMS |
| 7 | ASMS |

DI8 和 Run Button 是低电平按下、松开后再次按下可切换的状态机输入。以 `F9` 为静态初值：

1. ASMS=1时，DI8使用HIN5（舱内DI8）。在对应静态值上把bit4拉低100～200 ms，再恢复，完成一次DI8按键动作。
2. Run使用HIN6。在对应静态值上把bit5拉低100～200 ms，再恢复，完成一次Run按键动作。
3. `0x7B0.Dbg_ModelHOX` bit3为DI8、bit4为Run，可用于确认切换结果。

`ebs_watchdog`是独立根输出，不占LOX/HOX位。用示波器测量VCU接插件PA30（内部由PTA31/FTM5_CH6驱动）：ASMS=0时应为0%占空比，ASMS=1时当前配置应为10 kHz、50%。

输出位定义：

| 字节 | 位 | 含义 |
|---|---:|---|
| ModelLOX | 0 | Brake LED |
| ModelLOX | 1 | AS Blue LED |
| ModelLOX | 2 | AS Yellow LED |
| ModelLOX | 3 | EBS Error LED |
| ModelLOX | 4 | RES Error |
| ModelLOX | 5～6 | 预留 |
| ModelHOX | 0 | EBS Trigger |
| ModelHOX | 1 | BMS Error LED |
| ModelHOX | 2 | IMD Error LED |
| ModelHOX | 3 | DI8 |
| ModelHOX | 4 | Run |
| ModelHOX | 5 | R2D Buzzer |
| ModelHOX | 6 | Emergency Buzzer |
| ModelHOX | 7 | 预留 |

## 7. 外部节点模拟

### 7.1 RES `0x1E4`

必须满足：

- `res_communication=1`。
- `res_heartbeat` 每帧或至少 100 ms 内变化一次。
- `res_xorcheck = Byte0 XOR Byte1`。

示例：

```text
仅通信：Byte0=0x04，Byte1=HB，Byte2=0x04 XOR HB
通信+Go：Byte0=0x14，Byte1=HB，Byte2=0x14 XOR HB
通信+Stop：Byte0=0x05，Byte1=HB，Byte2=0x05 XOR HB
```

心跳连续约 110 ms 不变化，`res_hbcheck` 会失效；连续 10 次 XOR 错误，`xorcheck` 会失效。

### 7.2 ESP `0x013`

设置：

- `curPrsFL=1.00 MPa`
- `curPrsFR=1.00 MPa`
- `curPrsRL=1.00 MPa`
- `curPrsRR=1.00 MPa`
- `esp13_lifeSig` 按 0～15 循环递增

ASB/Brake 判据为：FL、FR ≥0.848 MPa，RL、RR ≥0.742 MPa。LifeSig 连续约 110 ms 不变化时，`brkmotor_check` 会失效。当前模型没有利用 `esp13_checkSum` 判定有效性，但建议仍按供应商协议填写。

### 7.3 IPC、AMI、EPS

- `0x011`：四轮目标压力初始设 0；`ipc_motor_torque=0 Nm`。进入 AS Driving 后再小步增加。
- `0x012`：`ipc_cmd_angle=0`、`ipc_eps_velocity=20`、`ipc_task_finish=0`、前后车速=0。
- `0x042`：`ami_astask=1` 用于普通 AS 流程；值 5 会进入 Inspection，包含 EPS 正弦扫描和 27 s 超时，不用于初次调试。
- `0x401`：将 `eps_angle=0`，使模型的 `steer_zero=1`；错误码设 0。
- `0x402`：计数可递增，实际角度设 0。

## 8. 手动驾驶链路

初次测试仍保持 CAN0/逆变器断开。

1. `0x7A3` 设置 ASMS=0、TSMS=1、HIN4/HIN6 静态为 1。
2. Air2 设置为 0.60 MPa，HIN1=0，避免进入 `ebs_working`。
3. `0x013` 四轮实际油压设置为 1.00 MPa并持续刷新 LifeSig，使 `brake_on=1`。
4. 对 HIN4 执行一次低脉冲，建立 DI8；对 HIN6 执行一次低脉冲，建立 Run。
5. 检查ModelHOX bit3=1、bit4=1；`AMI_Rx.ami_process=2`表示Manual Driving。
6. 改变 APP1/APP2，检查 CAN0 `MCU1_Rx_Demand_Torque` 是否符合踏板公式；保持逆变器断开。
7. 制造 APP1/APP2 偏差，确认约 30 ms 后需求扭矩为 0。

## 9. 自动驾驶完整链路

建议重新上电，从已验证的四组调试覆盖开始。

1. 保持 `ipc_motor_torque=0 Nm`。
2. `0x7A3`：ASMS=1、TSMS=1、HIN1=1；Air1=0.40 MPa，不能达到 0.60 MPa。
3. 用 HIN5、HIN6 的低脉冲分别建立 DI8 和 Run。
4. `0x042.ami_astask=1`。
5. 持续发送合法 `0x1E4`，先保持 `res_go=0`。
6. 持续发送 `0x013`，四轮压力均 1.00 MPa，LifeSig 递增。
7. 维持 `0x401.eps_angle=0`。
8. 当 TS、ASB 自检和任务条件满足后，检查 `0x041.ami_process=4`（AS Ready）。
9. 保持 Ready 至少 5 s，再把 `res_go` 置 1；应先看到 `ami_process=8`（R2D），`0x469.eps_command_middle=0x55`。
10. EPS 零位反馈成立后，应进入 `ami_process=16`（AS Driving），`eps_command_middle` 回到 0。
11. 只在 CAN0 无执行器或逆变器可靠禁能时，小步增加 `ipc_motor_torque`，检查 `0x0CFF08EF` 扭矩字段。
12. 保持轮速为0，把`ipc_task_finish=1`，应进入`ami_process=32`（AS Finished），ModelHOX bit0出现EBS Trigger。

## 10. 故障与超时测试

| 测试 | 操作 | 通过判据 |
|---|---|---|
| 单组覆盖超时 | 仅停止 `0x7A1`，继续其他调试帧 | 500 ms 后 ActivePedal=0，其他 Active 不变，`0x7B1`退回硬件值 |
| 总控制超时 | 停止 `0x7A0` | 500 ms 后 Requested=0、Active=0 |
| 踏板不一致 | APP1/APP2 归一化差≥0.1 | 约30 ms后手动扭矩为0 |
| RES 心跳故障 | 冻结 heartbeat | 约110 ms后 ASB 自检不再成立 |
| RES XOR 故障 | 连续发送错误 XOR | 10次后 ASB 自检不再成立 |
| ESP LifeSig故障 | 冻结 LifeSig | 约110 ms后 brkmotor_check=0 |
| EBS Emergency | AS状态下HIN1=1、Air2升至0.60 MPa | `ami_process=64`、TS/扭矩清零、EBS告警/触发输出变化 |

EBS Emergency和RES Stop项只能在CAN0/执行器断开时测试。Emergency时需求扭矩与CAN0电机使能位均应在同一模型周期清零。

## 11. 退出调试

1. 把 `Dbg_MasterEnable` 和全部分组 Enable 置 0，继续发送 `0x7A0` 至 `0x7B0 Active=0`。
2. 停止 `0x7A1～0x7A3`，等待至少 500 ms，确认全部输入已回到硬件。
3. 关闭 TSMS、Run、DI8，并确认 CAN0 Enable=0。
4. 停止所有模拟节点报文，再断开 VCU 电源。
5. 保存 TSMaster 报文记录，至少包含 `0x7A0～0x7A3`、`0x7B0～0x7B2`、`0x010/0x020/0x041/0x469` 和相关外部节点报文。
