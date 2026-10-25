from pathlib import Path
from shutil import copy2
R=Path(r'D:\git\RZS_Repository');W=Path(__file__).parent
def write(path,text):
 p=R/path; dst=W/'原文备份'/path;dst.parent.mkdir(parents=True,exist_ok=True)
 if p.exists() and not dst.exists():copy2(p,dst)
 p.write_text(text,encoding='utf8')
sys=(R/'RES/firmware/docs/RES_SYSTEM_DESCRIPTION_CN.md').read_text(encoding='utf-8-sig')
write('RES/Documentation/RES_Controller_接口汇总.md', '''# RES 现用双端接口汇总

校订日期：2026-10-16。现用硬件为 STM32G0B1CBT6 与 S017 Si4463 SPI；原 F103/SX127x 接口仅适用于历史工程，不再作为现用接线依据。具体实现见 `../firmware/docs/RES_SYSTEM_DESCRIPTION_CN.md`。

## 双端共同接口

| MCU针脚 | 模块接口 | 电气定义 |
|---|---|---|
| PA4 | S017 9 nSEL | 3.3 V逻辑，低有效片选 |
| PA5 | S017 6 SCLK | SPI时钟 |
| PA6 | S017 7 SDO | 模块输出到MCU MISO |
| PA7 | S017 8 SDI | MCU MOSI到模块输入 |
| PB2 | S017 5 nIRQ | 低有效输入 |
| PB3 | S017 10 SDN | 高关断、低工作，不是NRST |
| 3.3 V | S017 1和2 VCC | 两个供电脚都连接，禁止接5 V |
| GND | S017 11和12 | 与本端MCU共地 |
| PA13/PA14 | SWDIO/SWCLK | 独立调试接口 |

## 遥控端接口

| MCU针脚 | 信号 | 定义 |
|---|---|---|
| PB0 | GO | 低有效，25 ms消抖，按钮常开接地 |
| PB1 | STOP | 健康常闭链拉低；高为急停、断线或检测链掉电 |
| PB6/PB7 | INA226 SCL/SDA | I2C 3.3 V上拉，地址0x40，10 mΩ分流器标定 |
| PA8 | INA226 ALERT | 可选，现用轮询 |
| PB13/PB12/PB11/PB10 | 红/绿/黄/蓝灯 | 对应IN1/2/3/4，低有效 |

电量预警11.1 V、严重低电量10.5 V；采样无效阻止正常许可。阈值按实物电池及分流器核定。

## 车载端接口

| MCU针脚 | 信号 | 定义 |
|---|---|---|
| PB10/PB11 | R1/R2 | 低电平吸合，复位和故障须释放，验证实际COM–NO |
| PB12 | START_OUT | 3.3 V高有效，GO约100 ms脉冲 |
| PB13 | FAULT_OUT | 3.3 V高有效本地故障，不能代替RES_ERROR |
| PB9/PB8/PA0 | CAN TXD/RXD/STB | 必须经CAN收发器，不能直接连CANH/CANL |

## 整车安全接口

- VCU独立输出RES_ERROR，健康12 V、故障0 V。VCU无有效状态时保持故障，并保持TSMS关闭；先建立有效健康12 V，再允许TSMS上电。
- EBS主支路EBS_PWR/EBS_WORK为24 V；安全回路经外部DCDC后12 V送SDC_IN/RLY2。
- 已删除EBS/RES“两路都为1后才开始监测”的等待机制，实际硬件故障锁存及正确复位保留。
- CAN采用500 kbit/s Classic CAN；0x510状态每50 ms，0x511 GO事件，0x512诊断；VCU周期安全任务监督150 ms状态超时。
- 无线默认500 ms超时；三次有效READY只恢复RES软件许可，GO必须是新的操作者事件。软件恢复不清除整车硬件锁存或EBS机械保持。
- R1/R2触点存在历史拓扑差异，最终接入SDC/EBS的位置须以冻结整车图与实物核对；命令位不是物理反馈。

## 历史接口及验证边界

F103/SX127x LoRa、ADS1115、PB10/PB11按钮以及E220 UART是旧版本定义，现用双端不可按其接线。旧F103固件仍仅适用于对应历史硬件。
现用系统说明、DBC与状态机代码为设计实现依据；未完成的整车触点响应、CAN集成、射频和制动试验不能视为通过。
''')
for path,title,start,end in [
 ('RES/firmware/vehicle_g0b1/Docs/HARDWARE_ALLOCATION_CN.md','车载端硬件分配与接线说明','## 5 车载端接口','## 6 状态机与正常流程'),
 ('RES/firmware/remote_g0b1/Docs/HARDWARE_ALLOCATION_CN.md','遥控端硬件分配与接线说明','## 4 遥控端接口','## 5 车载端接口')]:
 common=sys.split('## 3 无线接口与杜邦线连接',1)[1].split('## 4 遥控端接口',1)[0]
 relevant=sys.split(start,1)[1].split(end,1)[0]
 text='# '+title+'\n\n校订日期：2026-10-16。适用STM32G0B1CBT6与S017 Si4463，不适用旧E220 UART或F103工程。\n\n## 共同无线接口\n'+common+'\n'+start+'\n'+relevant
 text+='\n## 调试与验收边界\n\nPA13为SWDIO，PA14为SWCLK。IWDG名义约500 ms，实际时间受LSI偏差影响，须实测。灯或继电器命令位不代表物理负载状态。下载、复位、MCU无电与交错上电状态下分别检查实际输出。\n\nVCU独立RES_ERROR健康12 V、故障0 V，先于TSMS建立有效健康状态。EBS主支路24 V，安全回路外部DCDC后12 V。整车硬件锁存保留，不由RES软件恢复清除。完整状态机和未关闭事项见 ../../docs/RES_SYSTEM_DESCRIPTION_CN.md；CAN契约见 ../../docs/VCU_INTEGRATION.md。\n'
 write(path,text)
write('RES/README.md','''# RES 遥控急停系统

校订日期：2026-10-16。当前系统为STM32G0B1双端与S017 Si4463 SPI无线模块。旧F103/SX127x与E220工程只适用于对应历史硬件。

## 当前入口

- [双端系统说明](firmware/docs/RES_SYSTEM_DESCRIPTION_CN.md)
- [现用接口汇总](Documentation/RES_Controller_接口汇总.md)
- [VCU集成契约](firmware/docs/VCU_INTEGRATION.md)
- [CAN DBC](firmware/dbc/RES_CAN_Validation.dbc)
- [车载端硬件分配](firmware/vehicle_g0b1/Docs/HARDWARE_ALLOCATION_CN.md)
- [遥控端硬件分配](firmware/remote_g0b1/Docs/HARDWARE_ALLOCATION_CN.md)
- [固件工作区](firmware/README.md)
- [正常CAN固件恢复及隔离台架记录](firmware/docs/BENCH_NO_CAN_20260924.md)
- [整车板卡网表](../网表/README.md)

现用RES_ERROR由VCU独立输出，健康12 V、故障0 V；先建立有效健康状态再允许TSMS上电。删除两路健康后才开始监测的等待设计，保留实际故障锁存。EBS安全回路经DCDC后12 V，主支路24 V。CAN使用0x510/0x511/0x512，旧0x1E4不能直接复用。

固件候选映像与实物已刷版本应分别核对；本次文档校订不证明当前实板映像。正常CAN版的历史下载记录不替代CAN连接后的READY/GO与整车验收。

## 历史资料

`firmware/RES_Controller_F103`和旧遥控拓扑网表保留追溯，不能作为当前G0B1/Si4463接线入口。`Documentation/Legacy`内旧说明书不作为现用功能定义。RES两路触点拓扑仍须最终整车原理图统一。
''')
write('RES/Documentation/README.md','''# RES 文档

- [现用双端接口汇总](RES_Controller_接口汇总.md)：2026-10-16校订，G0B1与Si4463，含整车电压域和CAN接口。
- [系统功能与状态机](../firmware/docs/RES_SYSTEM_DESCRIPTION_CN.md)
- [VCU集成契约](../firmware/docs/VCU_INTEGRATION.md)
- `Legacy/`和`Renders/Manual/`：历史说明书及渲染，只作追溯。
- `Renders/Rules/`和`Renders/Schematics/`：历史渲染页，使用前核对原文件版本。

规则原始PDF位于仓库根目录`规则/`。文档声明不构成实车验收完成，实际接线、软硬件版本和测试记录需一致。
''')
print('Updated 6 RES current-entry and hardware-allocation documents')
