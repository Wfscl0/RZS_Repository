# RES 硬件资料

## JLCEDA

- `JLCEDA/RES_Controler.eprj2`：当前主工程；
- `JLCEDA/RES_copy.eprj2`：历史副本，修改前应先与主工程比较；
- `JLCEDA/RES_Controler_backup/`：嘉立创 EDA 自动备份，按时间保留。

不要单独改名 `RES_Controler.eprj2` 或其备份目录，否则可能破坏 EDA
自动备份识别关系。

## Netlists

- `Netlists/RES_Controller.NET`：遥控器模块级拓扑网表；
- `Netlists/Netlist_Schematic1_2026-07-21.tel`：详细原理图网表导出。

STM32 引脚分配以
`../Documentation/RES_Controller_接口汇总.md`
和固件中的 `board_pins.h` 为准。

