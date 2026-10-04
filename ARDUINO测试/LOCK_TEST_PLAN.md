# 错误锁存板台架测试

> 2026-10-04：以下保留旧板测试步骤/记录。当前方案删除 EBS/RES 两路都输出 1 才开始监测的上电等待设计，改为 TSMS 上电前先给 RES_ERROR 12 V；EBS 安全回路经 DCDC 降为 12 V。旧记录不代表这些变更已验证，当前定义见 `../错误锁存/说明.txt` 和 `../EBS/EBS说明.md`。

依据：`错误锁存/说明.txt` 与 `网表/lock.tel`；冲突时以
`lock.tel` 为准。

## Nano 接线

| Nano | 锁存板 | 方向/电平 |
|---|---|---|
| D8 | SCOUT | `INPUT_PULLUP`，低=触点闭合 |
| D7 | SCIN | 输出并保持0 V |
| D11 | R_E_RESET | 开漏模拟，低有效 |
| D10 | BMS_RESET | 开漏模拟，低有效 |
| D9 | IMD_RESET | 开漏模拟，低有效 |
| D12 | EBS_ERROR | 输出，正常 5 V，故障 0 V |
| D6 | R_E_LED | 高阻输入 |
| D5 | BMS_LED | 高阻输入 |
| D4 | IMD_LED | 高阻输入 |
| GND | 两台电源负极、锁存板 GND | 必须共地 |

H5 三个 LED 引脚是 5 V 高边输出，不是干接点。关闭时可能悬空；没有约
10 kΩ 外接下拉时，D4-D6 的低电平读数不能作为确定的关闭判据。继电器
触点 `SCIN-SCOUT` 是本轮锁存测试的主要判据。

## 单台12 V电源接法

- 12 V正极同时连接H6.1、IMD_ERROR、BMS_ERROR、RES_ERROR，作为板电源和
  三路健康电平。
- 电源负极、H6.2和Nano GND必须共地。
- EBS_ERROR由Nano D7提供5/0 V。
- 逐路测试IMD、BMS或RES时，先关闭12 V电源，再把该输入从12 V正极改接
  到GND；重新上电后验证0 V故障锁存。恢复健康时也必须先断电改回12 V。
- 单电源方案只能验证健康/故障逻辑、锁存和复位，不能实测IMD约9 V、BMS
  约10 V的翻转阈值和迟滞；阈值扫描需要第二路独立可调电源。

## 测试顺序

1. 12 V电源关闭；上传程序。程序启动时EBS为0 V，RESET和LED检测
   引脚均为高阻，避免给未上电板反向供电。
2. 接好共地、电源和上述Nano线；确认RES_ERROR不接任何Nano引脚，任何Nano引脚均
   未连接12 V。
3. 把IMD_ERROR、BMS_ERROR、RES_ERROR接到12 V正极，然后打开板电源。
4. 执行 `SET EBS HEALTHY`；由外部电源把RES置为12 V，再执行
   `RESET ALL`。四路均健康时，`CONTACT=CLOSED`。
5. 每次只制造一路故障；触点应断开。输入恢复健康后触点仍应保持
   断开，直到对应 RESET：
   - IMD：断电改线，12 V→0 V→12 V，执行 `RESET IMD`
   - BMS：断电改线，12 V→0 V→12 V，执行 `RESET BMS`
   - EBS：`SET EBS FAULT`→`SET EBS HEALTHY`，执行 `RESET RE`
   - RES：断电改线，12 V→0 V→12 V，执行 `RESET RE`
6. 在故障仍存在时执行对应 RESET，触点不得重新闭合。
7. 改接IMD/BMS/RES前，先执行 `SAFE`，再关闭12 V电源输出。

## 串口命令

`STATUS`、`SET EBS HEALTHY|FAULT`、
`RESET IMD|BMS|RE|ALL`、`MEASURE 100..10000`、`SAFE`。

## 2026-07-23 实测结果

- IMD：12 V健康、9 V故障；故障锁存、防故障中复位和恢复后复位均通过。
- BMS：12 V健康、10 V故障；故障锁存、防故障中复位和恢复后复位均通过。
- EBS：5/0 V；在RES=12 V时，故障锁存及 `R_E_RESET` 均通过。
- RES：12/0 V；故障锁存、防故障中复位和恢复后复位均通过。
- R_E锁存不能被 `IMD_RESET` 或 `BMS_RESET`解除，复位隔离通过。
- 上电且四路输入健康时，仍需执行正确 RESET 后触点才闭合；上电初态按
  失效安全断开处理。
- 旧说明中的RES正常5 V错误：20 kΩ/12 kΩ分压后只有1.875 V，不能作为
  U24在5 V供电时的有效高电平；12 V分压后为4.5 V。
- H5三路在本次测试中只确认了高电平；没有外接下拉时，关闭状态仍未验证。
