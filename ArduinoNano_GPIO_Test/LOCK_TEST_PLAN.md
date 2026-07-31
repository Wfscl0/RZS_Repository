# 错误锁存板台架测试

依据：`错误锁存/说明.txt` 与 `所有板子完整仿真/fin/lock.tel`；冲突时以
`lock.tel` 为准。

## Nano 接线

| Nano | 锁存板 | 方向/电平 |
|---|---|---|
| D13 | EBS_ERROR | 输出，正常 5 V，故障 0 V |
| D12 | 不连接 | RES_ERROR是12/0 V信号，不能由Nano直接产生 |
| D11 | R_E_RESET | 开漏模拟，低有效 |
| D10 | BMS_RESET | 开漏模拟，低有效 |
| D9 | IMD_RESET | 开漏模拟，低有效 |
| D8 | SCOUT | `INPUT_PULLUP`，低=触点闭合 |
| D7 | SCIN | 输出并保持 0 V |
| D6 | R_E_LED | 高阻输入 |
| D5 | BMS_LED | 高阻输入 |
| D4 | IMD_LED | 高阻输入 |
| GND | 两台电源负极、锁存板 GND | 必须共地 |

H5 三个 LED 引脚是 5 V 高边输出，不是干接点。关闭时可能悬空；没有约
10 kΩ 外接下拉时，D4-D6 的低电平读数不能作为确定的关闭判据。继电器
触点 `SCIN-SCOUT` 是本轮锁存测试的主要判据。

## 两台电源

- 电源 A（0-12 V）：给 H6.1/H6.2 供电，并给暂不测试的 IMD/BMS 通道
  提供 12 V 健康电平。
- 电源 B（0-50 V）：只调到 0-12 V 范围；测试IMD/BMS时给当前被测通道
  提供 12 V→故障电压→12 V，测试RES时提供12/0 V。
- 两台电源负极、H6.2 和 Nano GND 共地。
- IMD 初始故障点用约 9 V，BMS 初始故障点用约 10 V；随后再缓慢扫描
  实测翻转阈值和迟滞。

## 测试顺序

1. 两台电源输出均关闭；上传程序。程序启动时 EBS/RES 均为 0 V，
   RESET 均为高阻，避免给未上电板反向供电。
2. 接好共地、电源、两个模拟输入和上述 Nano 线；检查无 12 V 接入
   Nano 引脚。
3. 打开电源 A（板电源）及提供模拟输入的电源输出。
4. 执行 `SET EBS HEALTHY`；由外部电源把RES置为12 V，再执行
   `RESET ALL`。四路均健康时，`CONTACT=CLOSED`。
5. 每次只制造一路故障；触点应立即断开。输入恢复健康后触点仍应保持
   断开，直到对应 RESET：
   - IMD：12 V→约 9 V→12 V，执行 `RESET IMD`
   - BMS：12 V→约 10 V→12 V，执行 `RESET BMS`
   - EBS：`SET EBS FAULT`→`SET EBS HEALTHY`，执行 `RESET RE`
   - RES：外部电源12 V→0 V→12 V，执行 `RESET RE`
6. 在故障仍存在时执行对应 RESET，触点不得重新闭合。
7. 改接 IMD/BMS 被测通道前，先执行 `SAFE`，再关闭两台电源输出。

## 串口命令

`STATUS`、`SET EBS HEALTHY|FAULT`、
`RESET IMD|BMS|RE|ALL`、`MEASURE 100..10000`、`SAFE`。

## 2026-07-23 实测结果

- IMD：12 V健康、9 V故障；故障锁存、防故障中复位和恢复后复位均通过。
- BMS：12 V健康、10 V故障；故障锁存、防故障中复位和恢复后复位均通过。
- EBS：5/0 V；在RES=12 V时，故障锁存及 `R_E_RESET` 均通过。
- RES：12/0 V；故障锁存、防故障中复位和恢复后复位均通过。
- R_E锁存不能被 `IMD_RESET` 或 `BMS_RESET`解除，复位隔离通过。
- 旧说明中的RES正常5 V错误：20 kΩ/12 kΩ分压后只有1.875 V，不能作为
  U24在5 V供电时的有效高电平；12 V分压后为4.5 V。
- H5三路在本次测试中只确认了高电平；没有外接下拉时，关闭状态仍未验证。
