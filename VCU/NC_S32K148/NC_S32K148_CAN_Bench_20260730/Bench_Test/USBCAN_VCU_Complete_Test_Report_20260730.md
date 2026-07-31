# VCU USBCAN 硬件在环完整测试报告（2026-07-30）

## 1. 结论

当前测试固件的无人正常状态链可以按照模型预期工作，但不能判定为“测试阶段无问题”。

已实测通过：

- `AS_Off -> AS_Ready -> R2D -> AS_Driving -> AS_Finished -> AS_Off`；
- Ready 的 5 s 最小等待时间及过早 RES Go 抑制；
- R2D 转向回中门槛；
- Driving 时 EPS、ESP、牵引电机命令联动；
- Finished 时 EPS、ESP和电机安全关闭；
- 制动传感器断线和气压低端故障的延时置位与恢复；
- RES Stop、ASMS断开、制动传感器断线、RES心跳超时均能触发 Emergency；
- Emergency 后安全锁可阻止未经复位的自动重启；
- Driving 状态收到 RES Stop 后 EPS、ESP和电机均正确关闭。

发现的阻断问题：

1. 从 Ready 进入 Emergency 时，ESP 仍保持 `mode=1`；
2. RES 心跳一旦进入超时状态，恢复正常心跳后不能稳定恢复；ESP生命计数状态机存在同构问题；
3. 气压传感器高端短路判据不可达；
4. Bootloader 到 `0x20000` 应用的启动/跳转不可靠，调试中多次出现只发0或1帧后停止以及 `INVSTATE UsageFault`。

因此，当前版本不应直接作为最终实车无人运行版本。

## 2. 测试环境

- VCU：S32K148，低压供电；
- J-Link：序列号 `69400240`，测试期间目标电压约 `3.267~3.312 V`；
- CAN适配器：ZLG USBCAN，`VID_0471&PID_1200`，设备序列 `00020080418`；
- Windows位置：`Port_#0003.Hub_#0002`；
- 驱动版本：`1.94.0.2`；
- CAN：CAN0，Classic CAN，500 kbit/s；
- 驱动接口：`E:\TSMaster\bin\ControlCAN.dll`；
- 测试对象：`Debug_FLASH/NC_S32K148.elf` 对应的 CAN Bench 固件；
- 功率执行端：按低压台架测试处理，不对实际车辆机械动作作结论。

ZLG控制器最终错误状态：`ErrCode=0x00000000`。

## 3. 无人正常状态链实测

一次完整有效运行的状态轨迹：

| 相对时间 | 状态 | 结果 |
| ---: | --- | --- |
| 0.02 s | AS_Off | 通过 |
| 1.45 s | AS_Ready | ASB自检通过后进入 |
| 6.45 s | R2D | Ready保持约5 s后进入 |
| 6.73 s | AS_Driving | EPS实际角度回零后进入 |
| 6.98 s | AS_Finished | IPC任务完成且轮速为零后进入 |
| 7.34 s | AS_Off | ASMS关闭、制动释放后进入 |

早于5 s发送 RES Go 时，状态保持 AS_Ready，测试通过。

### 3.1 状态对应控制输出

| 状态 | EPS workmode | ESP mode | 电机使能 | 电机扭矩 | 结果 |
| --- | ---: | ---: | ---: | ---: | --- |
| R2D | 32 | 1 | 1 | 0 Nm | 通过，电机扭矩被R2D门控 |
| Driving | 32 | 1 | 1 | 20 Nm | 通过，与IPC测试目标一致 |
| Finished | 0 | 0 | 仍可能保留TS位 | 0 Nm | 关键控制量通过 |
| Emergency（Driving进入） | 0 | 0 | 0 | 0 Nm | 通过 |
| Emergency（Ready进入） | 0 | **1** | 0 | 0 Nm | **失败** |

有效完整运行中观测到的VCU输出数量：

- `0x041 AMI_Rx`：899帧；
- `0x020 ESP_R_00`：899帧；
- `0x469 EPS命令`：899帧；
- `0x7B0 调试状态`：180帧；
- `0x0CFF08EF 电机命令`：1798帧。

## 4. 故障诊断与恢复

| 测试项 | 激励 | 观察 | 结果 |
| --- | --- | --- | --- |
| 制动传感器断线 | 制动ADC置0 | 约100 ms后LOX故障位置位 | 通过 |
| 制动传感器恢复 | 恢复约0.5 V | 故障位清除 | 通过 |
| 气压低端故障 | 气压1约1.93 V、气压2约1.21 V | 约500 ms后故障位置位 | 通过 |
| 气压低端恢复 | 恢复约9.67 V/4.83 V | 故障位清除 | 通过 |
| RES心跳超时 | 冻结心跳 | 故障位置位；Ready下约0.83 s进入Emergency | 置位通过 |
| RES心跳恢复 | 恢复递增心跳1.2 s | 故障位不清除，后续Ready被拦截 | **失败** |

气压低端测试同时调整两路输入，目的是只触发 `airprs_sensor1 < 2.5`，避免额外触发 `air2 > air1 + 1.5` 的EBS压力关系锁存。

## 5. Emergency 分支实测

| Emergency来源 | 起始状态 | 是否进入Emergency | EPS | ESP | 电机 | 结果 |
| --- | --- | --- | ---: | ---: | ---: | --- |
| RES Stop | Ready | 是，约0.22 s | 0 | **1** | 0 Nm/禁用 | ESP失败 |
| ASMS断开 | Ready | 是，约0.28 s | 0 | **1** | 0 Nm/禁用 | ESP失败 |
| 制动传感器断线 | Ready | 是，约0.38 s | 0 | **1** | 0 Nm/禁用 | ESP失败 |
| RES心跳超时 | Ready | 是，约0.83 s | 0 | **1** | 0 Nm/禁用 | ESP失败 |
| RES Stop | Driving | 是，约0.05 s | 0 | 0 | 0 Nm/禁用 | 通过 |

每次有效Emergency测试中，在 ASMS关闭并释放制动后均能回到Off；随后重新给出ASMS/任务请求，状态仍保持Off，安全锁测试通过。

## 6. 已定位的软件问题

### 6.1 Ready进入Emergency后ESP仍为mode 1（高优先级）

在 `ESP_Chart1` 的 `ESC_Engage` 分支中，只有 `brake_flag==1` 才转到 `ESC_Able`；其他值（包括Emergency设置的0）仍执行 `mode=1`。Ready时ESP正处于Engage，所以Ready直接进入Emergency会保留mode 1。Driving时ESP已处于Able，`brake_flag=0` 能正常退出，因此Driving Emergency测试通过。

代码位置：`VCU10_ert_rtw/VCU10.c` 约第1785行。

建议修复：`ESC_Engage` 对 `brake_flag==0` 明确转入 `ESC_Unable` 并立即清零模式和目标压力；生成代码应通过Simulink/Stateflow源模型修改，不直接手改生成C代码。

### 6.2 RES心跳超时后无法稳定恢复（高优先级）

`heaartbeat_chart` 在 `judge` 状态检测到心跳变化时转回 `compare`，但没有清零 `hbcnt`。旧计数仍大于30，状态很快再次回到judge，导致 `res_hbcheck` 不能连续保持有效，`comm_good` 无法累计到50，故障不能清除。

代码位置：`VCU10_ert_rtw/VCU10.c` 约第1191~1208行。

建议修复：在judge检测到有效变化时清零 `hbcnt`；同时统一检查begin/compare/same/judge所有转换的计数器进入/退出动作。

### 6.3 ESP生命计数检查存在同构恢复问题（高优先级）

`brkmotor_check_system` 的judge状态检测到生命计数变化后没有清零 `lscnt`。一旦进入超时judge，也可能无法稳定恢复，并继续阻止ASB自检。

代码位置：`VCU10_ert_rtw/VCU10.c` 约第2168~2185行。

建议与RES心跳状态机同时修改，并增加“超时后恢复”的模型测试向量。

### 6.4 气压高端短路条件不可达（中高优先级）

输入换算先把两路气压电压饱和到10.0 V（转换后最大10000 mV），后续诊断却使用 `airprs1 > 10050 || airprs2 > 10050`。因此高端判据永远不可能为真，实测注入超过满量程的调试原始值也不能触发该条件。

代码位置：饱和约第999/1017行；诊断比较约第2340行。

建议：采用低于饱和值且留有ADC误差裕量的阈值，例如按传感器、分压和ADC精度标定后设置约9.8 V；最终值需结合实物传感器容差确认。

### 6.5 Bootloader到应用启动不可靠（高优先级，集成问题）

硬复位后PC位于Bootloader区域 `0x00004E94`，应用向量位于 `0x00020000`。测试必须用J-Link设置MSP、VTOR和应用Reset_Handler才能运行。多次强制启动中出现：

- 无任何周期报文；
- 仅发出0或1帧后停止；
- PC停在约 `0x00020458`，CFSR=`0x00020000`（INVSTATE UsageFault）；
- 另一些启动可正常进入FreeRTOS，VTOR切到 `0x1FFE0000`，CFSR=0。

这说明正式投入使用前必须验证Bootloader的应用有效性检查、MSP/VTOR/Thumb入口、外设/中断清理和稳定跳转。不能依赖J-Link手动跳转作为正常上电启动方案。

## 7. 本轮未能代表实车验证的内容

- 实际EPS、ESP、逆变器和电机的机械响应、方向和幅值；
- 高压系统、制动气路真实建立/泄放时间；
- 全车所有ECU同时在线时的总线负载、仲裁和错误恢复；
- ADC传感器最终标定、线束短路到电源/地的电气边界；
- 长时间任务抖动、栈余量、内存破坏和EMC环境；
- Bootloader正常上电自动进入应用；
- 内部硬件看门狗（按当前项目要求暂不使用）。

## 8. 可重复测试脚本

- `pcan_autonomous_state_machine_test.py`：共享的完整状态机激励与判据；
- `zlg_usbcan_autonomous_state_machine_test.py`：ZLG USBCAN传输适配；
- `zlg_usbcan_emergency_transition_test.py`：独立Emergency来源测试。

ZLG脚本必须使用TSMaster随附的32位Python：

```powershell
E:\TSMaster\bin\Data\Python\3.8.5\x86\python.exe Bench_Test\zlg_usbcan_autonomous_state_machine_test.py
```

本轮只新增/修改台架测试脚本和报告，没有修改底层软件架构或正式模型控制逻辑。
