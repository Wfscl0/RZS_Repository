# TSAL LTspice 重排版高精度仿真工程

打开 `TSAL_relayout_high_precision.asc`，并保持本文件夹内所有 `.asy/.lib` 与 `.asc` 在同一目录。

## 本版修复

1. 已使用当前上传的 `Netlist_Schematic1_2026-05-02(1).tel`，不再把 R64 左侧强行接地。
2. 当前网表中 POR 连接为：
   - `R64.1` 与 `U20.2` 同网：`N1N224`；
   - `R64.2`、`C18.1`、`R55.2` 同网：`N1N223`；
   - `R55.1` 接 GND；
   - `C18.2` 接 `+5VG`。
3. 版图按原理图功能块重新排布：左侧为信号来源和默认值，中上为继电器豁免/断线合成，右上为红灯判断和红灯闪烁电路，中部为绿灯判断，下中为锁存，右下为红/绿电源模块。
4. 所有符号均加入了 `WINDOW` 坐标，`InstName` 与 `Value` 不再重叠。

## 关键引脚检查

| 器件 | 引脚检查 |
|---|---|
| U18/U19 `SN74LVC1G32DBVR` | 1=A, 2=B, 3=GND, 4=Y, 5=VCC |
| U13 `SN74LV1T32DBVR` | 1=A, 2=B, 3=GND, 4=Y, 5=VCC；用于 `V_DISCONNECT OR REL_FAULT_SET` |
| U16 `SN74LV1T08DBVR` | 1=A, 2=B, 3=GND, 4=Y, 5=VCC |
| U15 `SN74LVC1G14DBVR` | 1=NC, 2=A, 3=GND, 4=Y, 5=VCC |
| U20 `SN74LVC1G17QDCKRQ1` | 1=NC, 2=A, 3=GND, 4=Y, 5=VCC |
| U12 `SN74LVC2G02DCTR` | 1A, 1B, 2Y, GND, 2A, 2B, 1Y, VCC |
| U1/U2 `TL331IDBVR` | 1=IN-, 2=GND, 3=IN+, 4=OUT(open collector), 5=VCC |
| U4 `NE555DR` | 1=GND, 2=TRIG, 3=OUT, 4=RESET, 5=CONT, 6=THRES, 7=DISCH, 8=VCC |

## 时序输入与预期输出

低边输出规则：`RED_OUT_K` / `GREEN_OUT_K` 被 MOS 拉低时，外部灯亮；高电平时，外部灯灭。

| 时间段 | 输入情况 | 预期 `RED_OUT_K` | 预期 `GREEN_OUT_K` |
|---:|---|---|---|
| 0–20 ms | 上电，电池安全，三个继电器实际断开，无故障 | 高，红灯灭 | POR 后低，绿灯亮 |
| 25–60 ms | `V_CONTROLLER > 0.6V` | 2–5 Hz 拉低闪烁 | 若仍满足绿灯条件，则绿灯亮 |
| 40–55 ms | `V_BATTERY > 0.6V` | 由红灯条件决定 | 高，绿灯灭 |
| 81–100 ms | `MAINP_ACTUAL = 0` | 由红灯条件决定 | 高，绿灯灭 |
| 120–130 ms | `MAINP_DISCONNECT=1` 且 `MAINP_SHOULD=1` | 由红灯条件决定 | 进入锁存，高，绿灯灭 |
| 131–160 ms | 断线输入恢复为 0 | 由红灯条件决定 | 仍保持锁存灭灯 |
| 161–176 ms | LVS 断电再上电 | 灭 | POR 复位锁存 |
| 176–209 ms | 无故障、安全状态 | 灭 | POR 后重新亮 |
| 210–220 ms | `V_DISCONNECT=1` | 由红灯条件决定 | 再次锁存灭灯 |

## 模型选择原则

选择优先级：**匹配度 > 来源等级**；在匹配程度相同的情况下，**官方模型 > 论坛模型 > 生成宏模型**。

| 元件 | 本工程使用模型 | 来源/理由 |
|---|---|---|
| CD74HC08D-Q100 | `CD74HC08` 高精度封装宏模型 | TI 官方索引中 `CD74HC08` / `CD74HC08-Q1` 对应 `SCHM069`。本工程用等效 LTspice 宏模型，避免 PSpice 兼容问题。 |
| SN74LVC2G02DCTR | `SN74LVC2G02DCTR` 高精度封装宏模型 | TI 官方索引中对应 `SCEM624`。 |
| SN74LVC1G32DBVR | `SN74LVC1G32DBVR` 高精度封装宏模型 | TI 官方索引中对应 `SCEM632`。 |
| SN74LV1T32DBVR | `SN74LV1T32DBVR` 高精度封装宏模型 | TI 官方索引中对应 `SCLM181`。 |
| SN74LV1T08DBVR | `SN74LV1T08DBVR` 高精度封装宏模型 | TI 官方索引中对应 `SCLM184`。 |
| SN74LVC1G14DBVR | `SN74LVC1G14DBVR` 高精度封装宏模型 | TI 官方索引中对应 `SCEM637`。 |
| SN74LVC1G17QDCKRQ1 | `SN74LVC1G17QDCKRQ1` 高精度封装宏模型 | TI 官方索引中 `SN74LVC1G17` / `SN74LVC1G17-Q1` 对应 `SCEM635`。 |
| TL331IDBVR | `TL331IDBVR` 高精度比较器宏模型 | TI 有 TL331 产品和历史 PSpice 资源，但公开反馈指出部分 TL331 下载链接可能给到 LM2903B；本工程为确保引脚和极性完全匹配，使用生成宏模型。 |
| NE555DR | `NE555DR_HP` 高精度 555 宏模型 | TI E2E 明确提到没有 NE555 模型，TLC555 是 CMOS 版本且不完全匹配；本工程使用生成宏模型。 |
| LM340MP-5.0/NOPB | `LM340MP_5V` 稳压器宏模型 | 电源模块只需 5 V 稳态和压差行为，本工程使用生成宏模型。 |
| SMBJ18CA | `SMBJ18CA_MACRO` | 基于 SMBJ18CA 双向 TVS 18 V 特性生成。 |
| SMD2920P075TF | `SMD2920P075TF_MACRO` | 基于 0.75 A hold / 1.5 A trip PPTC 生成简化宏模型。 |
| AO3480C | `AO3480C_MACRO` | 基于 AO3480C N 沟道 MOSFET 阈值、Rds(on)、Vdss 等参数生成。 |
