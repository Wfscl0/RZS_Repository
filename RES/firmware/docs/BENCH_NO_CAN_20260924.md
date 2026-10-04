# 无 CAN 台架测试记录（禁止作为整车运行版本）

用户明确选择独立无 CAN 测试，并确认车载航空插头未连接。

**当前状态：已按用户要求恢复正常 CAN 固件。** J-Link（20090928，车载端）下载及校验成功，运行后读取 `0x20000274` 得到 `res_bench_no_can=0`。CAN 未连接，实测车载 `state=4、faults=0xC0、outputs=0`，CAN 故障保护与锁存生效。遥控端固件未改，仍保留断链注入后的无线关闭和故障锁存状态。以下无 CAN 内容为历史台架测试记录，不代表当前运行模式。

## 固件

台架测试时车载烧录 `artifacts/bench_nocan_20260924/vehicle/gcc/RES_Vehicle_G0B1.hex`；BIN SHA-256：`BD4738585054E0B566FB773B5158D1991DF20D7CEC166462975C4CC39172C9EB`。

构建参数为 `-Target vehicle -BenchNoCan -OutputRoot <独立台架目录>`。未指定开关时默认保留 CAN 保护，遥控端不接受该开关。CAN 收发器在台架版保持待机，CAN 发送请求仅计入 `res_bench_can_suppressed`，不能视为 CAN 测试通过；`res_bench_no_can=1` 可供调试识别。急停、无线鉴权、500 ms 失联判定、继电器锁存及看门狗未旁路。

带 CAN 的正常构建位于 `artifacts/production_can_20260924/vehicle/gcc/`，现已烧入实物。恢复车辆连接前仍须接好 CAN 对端并完成正常模式验证；无 CAN 台架版不能用于车辆运行。

## 结果

| 测试 | 观察结果 | 结论范围 |
|---|---|---|
| READY | 两端 faults=0；遥控电压约 11.42 V；车载 state=2、relay_commands=3；PB10/PB11 均低 | 正常许可与两路驱动命令通过 |
| 实际 GO 按钮 | 用户按下并松开，start_pulses=1；rise_ms=36686、fall_ms=36786 | 软件记录一次 100 ms START 脉冲；不是示波器测量 |
| 吸合 | 用户听到继电器动作声 | 有机械动作，不能证明两个触点均导通 |
| 模拟断链 | 原 READY 状态下，通过遥控 PB3/SDN 关闭无线；未暂停 MCU 或停止看门狗 | 有效的无线发送中断试验，不等同整机断电试验 |
| 断链释放 | 车载 state=4、faults=0x84，relay_commands=0；PB10/PB11 均高，START 保持低 | 两路驱动释放和故障锁存通过 |
| 触点释放 | 用户随后测量并确认两路 COM–NO 确实不导通 | 本次断链后的触点断开得到用户实测确认；未测触点动作延迟 |

断链前 tick=159542、last_valid=159441，READY、两路驱动有效。首次采到释放时，块读取中的 tick=159933、last_valid=159441，相减 492 ms。诊断块没有原子快照保证，且 GPIO 是随后读取，故这不是精确动作时间；仅支持约 500 ms 量级的软件失联动作，不能拿 492 ms 宣称触点断开延迟或正式时限验收通过。

台架测试结束时只读确认：车载 faults=0x84、outputs=0；遥控无线因主动 SDN 注入已关断，faults=0x14。当时保持该状态供检查，没有重新恢复 READY；其后车载恢复正常 CAN 版，见本文顶部。遥控此时的无线错误是在故障注入之后读取，不用于证明此前间歇命令错误复发。

## 触点确认与后续

继续保持航空插头断开。在确认触点侧没有外部电压后，用万用表通断档分别测两只继电器的 COM–NO：释放状态应均不导通。两路须分别测，不能靠一次动作声或遥控器灯色判断。需要测试 COM–NC 时以实际端子标注为准。驱动引脚电平不等于触点反馈。

正常 CAN 版恢复后，须先结束触点测量、保持负载隔离并接好 CAN 对端，再重启两端进行后续验证；恢复许可后可能重新吸合继电器。本轮没有验证触点焊死检测、实际 SDC、整车执行机构、CAN 通信或急停按钮触点全流程。

原始记录：`artifacts/bench_nocan_20260924/outputs_observed.jsonl`、`link_loss.jsonl`。只读观察：`python RES/firmware/tools/read_live_link.py --samples 1`。`test_bench_link_loss.py` 会主动关断遥控无线，不能当作普通状态查询运行。

验证：车载状态机主机测试通过；台架版及默认 CAN 版均编译成功；台架版 J-Link 下载内置校验通过。两种构建仍有既有裸机 syscall 桩和 RWX 段链接警告。
