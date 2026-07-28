# BSPD 电路仿真设计说明（供 Codex 使用）

版本：2026-07-28
设计依据：

- 工程：`../../BSPD/bspd _final.eprj2`
- 唯一权威网表：`../../BSPD/bspd.tel`
- 最新 BOM：`bspd.xlsx`
- 原理图：`bspd.png`
- 分析优先级：**`../../BSPD/bspd.tel` > 原理图图片；器件型号和封装以原理图/BOM为准**
- 本目录旧 `bspd.tel` 不得再作为当前连接依据。

---

## 0. 设计冻结与外部接口

当前设计由 24 V 输入，经 LM2596S-5.0 生成 5 V。四路油压输入经 LM339 比较后做 OR，电流输入经 LM2903 比较；两类条件同时成立并持续越过 RC/施密特门阈值后触发 555 保持，最终使 5 V 常开继电器释放并断开安全回路。

| 连接器 | 针脚 | 网络 | 类型 | 当前电气定义 |
|---|---:|---|---|---|
| H1 | 1 | `CURRENT` | 模拟输入 | 0~50 A 对应 0~5 V；目标电流 11.11 A，对应 1.11 V |
| H1 | 2 | `GND` | 电源回路 | 低压地 |
| H2 | 1 | `OIL4` | 模拟输入 | 0~20 MPa 对应 0~5 V；目标油压 30 bar（3 MPa），对应 0.75 V |
| H2 | 2 | `OIL3` | 模拟输入 | 同上 |
| H2 | 3 | `OIL2` | 模拟输入 | 同上 |
| H2 | 4 | `OIL1` | 模拟输入 | 同上 |
| H3 | 1 | `SC_IN` | 无源触点 | 安全回路输入 |
| H3 | 2 | `SC_OUT` | 无源触点 | 安全回路输出；继电器失电时断开 |
| H4 | 1 | `+24VIN` | 电源输入 | 24 V 低压电源 |
| H4 | 2 | `GND` | 电源回路 | 低压地 |

### 0.1 接口校订说明

- 油压传感器量程为 0~20 MPa、输出为 0~5 V。30 bar = 3 MPa，因此目标油压阈值为 `5 × 3 / 20 = 0.75 V`。
- 电流传感器量程为 0~50 A、输出为 0~5 V。5 kW / 450 V = 11.11 A，因此目标电流阈值为 `5 × 11.11 / 50 ≈ 1.11 V`。
- 当前权威网表中 R27/R28 为 5.62 kΩ/1 kΩ，形成约 0.755 V 参考；R25/R26 为 34.8 kΩ/10 kΩ，形成约 1.116 V 参考。相对各自精确目标的偏差约为 +0.7% 和 +0.45%，两组阈值分压均已完成设计修正，接口表仍以传感器物理目标对应的 0.75 V、1.11 V 为标称值。
- `SC_IN`/`SC_OUT` 是继电器常开触点，不是 5 V 逻辑输出。掉电或驱动失效时触点断开，这是本设计的失效安全状态。
- 当前权威网表中 Q2.2接GND、Q2.3接C3定时节点，符合AO3400低边放电方向；旧网表中的反接描述已作废。

### 0.2 数字台架反馈（2026-07-28）

- 正常输入下，上电约15.128 s后安全触点闭合。
- 仅CURRENT有效或仅任一OIL有效均不触发；四路OIL与CURRENT组合均能
  触发，证明当前U4四路OR连接有效。
- 100 ms冲突不触发；持续冲突约0.22 s使触点断开。
- 清除冲突后约14.1～14.2 s恢复；冲突保持15 s期间触点始终断开。
- 恢复计时5 s后施加约700 ms冲突会重新开始计时，最终清除后约13.94 s
  才闭合。
- 24 V掉电后触点OPEN，失电安全通过。
- 本轮使用0/5 V数字输入，没有验证0.755 V和1.116 V实际模拟翻转点。
- 五路输入均有10 kΩ上拉；Nano复位高阻会造成虚假冲突。仿真应加入
  输入开路/高阻和外部控制器掉电状态。

---

## 1. 仿真目标

建立可由 LTspice XVII 直接运行的 BSPD 功能仿真，验证：

1. 任一制动压力信号超过阈值时形成 `BRAKE_VALID`；
2. 电流信号超过阈值时形成 `CURRENT_VALID`；
3. 只有 `BRAKE_VALID AND CURRENT_VALID` 同时成立时才形成 BSPD 冲突；
4. 冲突经输入持续时间滤波后，使安全回路继电器释放；
5. 冲突消失后，安全回路保持断开至少 10 s，再允许自动恢复；
6. BSPD 断电时继电器必须释放，安全回路必须断开；
7. 验证传感器开路、对地短路、对 +5 V 短路等 SCS 故障；
8. 验证Q2按当前权威网表的低边放电连接能正确保持并重新启动复位计时。

仿真主要验证**逻辑和时序**，不能代替实车试验、EMC、温度、器件老化和继电器机械寿命验证。

---

## 2. 建议的仿真工程结构

```text
bspd_sim/
├─ README.md
├─ bspd_functional.asc
├─ bspd_functional.cir
├─ models/
│  ├─ comparator_oc.sub
│  ├─ logic_gates.sub
│  ├─ schmitt.sub
│  ├─ timer555_behavior.sub
│  ├─ ao3400.sub
│  └─ relay_no.sub
├─ tests/
│  ├─ test_normal.cir
│  ├─ test_trip_500ms.cir
│  ├─ test_reset_10s.cir
│  ├─ test_retrigger.cir
│  ├─ test_power_loss.cir
│  ├─ test_scs_faults.cir
│  └─ test_q2_orientation.cir
├─ scripts/
│  └─ run_all.py
└─ results/
   ├─ summary.csv
   ├─ waveforms/
   └─ report.md
```

优先生成 LTspice 可运行文件。不得只给伪代码或框图。

---

## 3. 电路输入与输出定义

### 3.1 供电

| 信号 | 定义 |
|---|---|
| `+24VIN` | BSPD 低压输入，来自 LVMS |
| `+5V` | U1 降压后逻辑电源 |
| `GND` | 低压系统地 |

功能仿真中先用理想 `5 V` 电源替代 LM2596。  
LM2596 开关电源另建独立测试电路，不与 15 s 级时序仿真混合，以避免仿真时间过长。

### 3.2 传感器输入

| 信号 | 含义 | 低状态测试值 | 高状态测试值 |
|---|---|---:|---:|
| `OIL1` | 制动压力输入 1；0~20 MPa → 0~5 V | 0.5 V | 1.0 V |
| `OIL2` | 制动压力输入 2；0~20 MPa → 0~5 V | 0.5 V | 1.0 V |
| `OIL3` | 制动压力输入 3；0~20 MPa → 0~5 V | 0.5 V | 1.0 V |
| `OIL4` | 制动压力输入 4；0~20 MPa → 0~5 V | 0.5 V | 1.0 V |
| `CURRENT` | 功率/电流判定输入；0~50 A → 0~5 V | 0.8 V | 1.4 V |

油压目标翻转点为 0.75 V，电流目标翻转点为约 1.11 V；上表低/高状态用于跨越目标阈值。传感器模型应同时保留量程、零点误差、满量程误差和供电/地偏移。

### 3.3 输出

| 信号 | 含义 |
|---|---|
| `OUT` | U7/555 输出，高电平表示保持安全回路断开 |
| `RELAY_GATE` | U8 输出、Q3 栅极控制 |
| `SC_IN`、`SC_OUT` | 安全回路串联触点 |
| `SC_CLOSED` | 仿真辅助量，1 表示触点闭合，0 表示触点断开 |

安全状态定义：

```text
继电器失电 = SC_IN 与 SC_OUT 断开
```

继电器模型必须使用常开触点。正常状态下继电器吸合，故障或掉电时释放。

---

## 4. 阈值计算

### 4.1 制动压力比较阈值

传感器定义：

```text
0~20 MPa → 0~5 V
30 bar = 3 MPa
```

因此：

```text
V_OIL_TARGET = 5 × 3 / 20
             = 0.750 V
```

比较器逻辑：

```text
OILx_VALID = 1，当 OILx > 0.750 V（目标）
```

当前网表的 R27=5.62 kΩ、R28=1 kΩ，参考值约为 `5 × 1 / (5.62 + 1) = 0.755 V`，对应约 30.2 bar；与 0.75 V 目标偏差约 +0.7%。油压分压已修正，硬件冻结前仍需结合元件容差与比较器失调实测翻转点。

### 4.2 电流比较阈值

功率与传感器定义：

```text
P_TARGET = 5 kW
V_TS     = 450 V
0~50 A → 0~5 V
```

因此：

```text
I_TARGET       = 5000 / 450 = 11.11 A
V_CURRENT_TARGET = 5 × 11.11 / 50
                 ≈ 1.111 V
```

比较器逻辑：

```text
CURRENT_VALID = 1，当 CURRENT > 1.11 V（目标）
```

当前网表的 R25=34.8 kΩ、R26=10 kΩ，参考值约为 `5 × 10 / (34.8 + 10) = 1.116 V`，对应约 11.16 A；在 450 V 下对应约 5.02 kW。相对精确目标 1.111 V 偏高约 +0.45%，电流分压已修正，硬件冻结前仍需结合元件容差与比较器失调实测翻转点。

---

## 5. 逻辑关系

### 5.1 制动判断

U4 为四路 2 输入 OR 门，网表构成级联 OR：

```text
BRAKE_VALID = OIL1_VALID
            OR OIL2_VALID
            OR OIL3_VALID
            OR OIL4_VALID
```

### 5.2 BSPD 冲突判断

U5 为 2 输入 AND 门：

```text
CONFLICT_RAW = BRAKE_VALID AND CURRENT_VALID
```

禁止把该逻辑建模为 OR。

### 5.3 持续时间滤波

```text
U5_OUT ─ R8(39 kΩ) ─ RC_DELAY
RC_DELAY ─ C11(6.8 µF) ─ GND
RC_DELAY → U2 SN74LVC1G17
```

名义时间常数：

```text
τ = 39 kΩ × 6.8 µF = 0.2652 s
```

SN74LVC1G17 在 5 V 供电时，正向施密特阈值按官方 4.5 V、5.5 V 参数线性估算：

```text
VT+ ≈ 2.42 V ～ 3.04 V
```

对应延时：

```text
t = -RC × ln(1 - VT+/5)
t ≈ 0.175 s ～ 0.247 s
```

考虑 R8 ±1%、C11 ±10% 和继电器释放时间，仿真目标为：

```text
冲突成立至 SC 断开 < 0.5 s
```

### 5.4 555 保持与自动复位

U7 定时网络：

```text
R10 = 100 kΩ
C3  = 120 µF
```

名义延时：

```text
t_RESET ≈ 1.1 × R10 × C3
        ≈ 13.2 s
```

仅按 R10 ±1%、C3 ±20% 估算：

```text
约 10.45 s ～ 16.00 s
```

验收条件：

```text
冲突消失后 SC 保持断开时间 ≥ 10.0 s
```

若冲突在复位计时期间重新出现，C3 必须被重新放电，10 s 计时必须重新开始。

---

## 6. 关键网表连接

### 6.1 比较器

- U3：LM339DR，四路压力比较器；
- U3 输出均为开集电极，并分别由 R6、R7、R11、R12 的 10 kΩ 电阻上拉到 +5 V；
- U9：LM2903DR，B 通道用于 CURRENT 比较；
- U9 输出由 R13 10 kΩ 上拉到 +5 V；
- U9 未使用的 A 通道输入已固定到确定电平，输出悬空。

### 6.2 逻辑器件

- U4：74HC32D,653，四路 2 输入 OR；
- U5：SN74LVC1G08DBVR，2 输入 AND；
- U2：SN74LVC1G17DBVR，施密特缓冲器；
- U8：SN74LVC1G14DBVR，施密特反相器。

### 6.3 MOSFET

Q1、Q2、Q3 均为 AO3400：

```text
物理引脚：
1 = Gate
2 = Source
3 = Drain
```

Q1、Q3 按低边 NMOS 使用：

```text
Source → GND
Drain  → 被拉低节点
```

### 6.4 Q2 当前连接

唯一权威网表 `../../BSPD/bspd.tel` 中：

```text
Q2.2（Source）→ GND
Q2.3（Drain） → C3/R10/U7.6/U7.7 定时节点
```

该连接符合AO3400标准低边放电方向。旧 `as_drawn_q2` 反接方案不再代表
当前硬件，不应继续作为主设计版本。模型仍必须包含体二极管，并绘制C3
节点和Q2电流，用于验证放电、保持和重新计时行为。

---

## 7. 器件模型分类

### 7.1 官方或厂家模型

优先使用厂家提供的 SPICE/PSpice 模型：

- LM2596S-5.0/NOPB：TI 官方资料；
- SN74LVC1G17、SN74LVC1G08、SN74LVC1G14：TI 官方资料；
- 74HC32D,653：Nexperia 官方资料；
- LM339DR、LM2903DR：BOM 中为 UMW 型号，优先使用 UMW 参数；
- AO3400：GOODWORK 官方资料。

### 7.2 行为宏模型

若官方 LTspice 模型不存在或不兼容，则建立行为宏模型，并在文件头注明：

```text
THIS IS A FUNCTIONAL BEHAVIORAL MODEL.
IT IS NOT A TRANSISTOR-LEVEL OR EXACT DEVICE MODEL.
```

允许使用行为宏模型的器件：

- LM339/LM2903 开集电极比较器；
- 74HC32 OR 门；
- SN74LVC1G08 AND 门；
- SN74LVC1G17/1G14 施密特门；
- LM555 定时器；
- 继电器机械动作。

### 7.3 参考替代模型

BOM 中 U7 为 HGSEMI LM555IM/TR。若找不到该厂官方模型，可采用 LTspice 内置 555 或通用 LM555 宏模型，但必须标记为：

```text
PIN-COMPATIBLE REFERENCE MODEL, NOT THE EXACT HGSEMI DEVICE MODEL.
```

---

## 8. 行为模型最低要求

### 8.1 开集电极比较器

比较器模型必须：

1. 输出只能主动拉低；
2. 高电平依赖外部上拉电阻；
3. 支持可设置输入失调 `VOS`；
4. 支持有限传播延时；
5. 不允许用理想推挽输出替代。

推荐参数：

```text
VOS = 0 mV nominal
VOS = ±5 mV corner
TD  = 1 µs nominal
VOL = 0.15 V
```

### 8.2 施密特门

SN74LVC1G17：

```text
VTP nominal = 2.73 V
VTN nominal = 1.94 V
VTP corner  = 2.42 V、3.04 V
VTN corner  = 1.70 V、2.19 V
```

SN74LVC1G14 可采用相近参数，但必须保持反相逻辑。

### 8.3 555

行为必须包含：

```text
TRIG < 1/3 VCC → SET，OUT = HIGH
THRES > 2/3 VCC → RESET，OUT = LOW
RESET pin LOW → 强制 OUT = LOW
DISCH 在复位状态导通
```

Q1 拉低 TRIG，Q2负责将外部定时电容放电。  
冲突持续存在时，OUT 必须保持高。

### 8.4 继电器

继电器模型：

```text
线圈额定电压 = 5 V
线圈电阻约 70 Ω
动作时间 = 10 ms
释放时间 = 10 ms
触点类型 = SPDT 中的 NO 触点
```

功能仿真可不加入触点反弹；另建可选测试加入 1～5 ms 反弹。

---

## 9. 仿真测试用例

### T01：正常上电

条件：

```text
OIL1～OIL4 = 0.5 V
CURRENT = 0.8 V
```

检查：

- `BRAKE_VALID = 0`
- `CURRENT_VALID = 0`
- 无 BSPD 冲突；
- 最终继电器吸合，`SC_CLOSED = 1`；
- 记录上电后安全回路闭合时间；
- 对 555 不同初始锁存状态进行仿真，不能只依赖单一 `.ic`。

### T02：仅制动

```text
任一 OIL = 1.0 V
CURRENT = 0.8 V
```

验收：

```text
不得触发 BSPD
SC 保持闭合
```

### T03：仅电流/功率

```text
所有 OIL = 0.5 V
CURRENT = 1.4 V
```

验收：

```text
不得触发 BSPD
SC 保持闭合
```

### T04：短暂冲突

```text
BRAKE_VALID = 1
CURRENT_VALID = 1
持续 100 ms
```

验收：

```text
RC 节点不得越过 U2 正向阈值
SC 不应断开
```

### T05：持续冲突

```text
BRAKE_VALID = 1
CURRENT_VALID = 1
持续 600 ms
```

验收：

```text
从冲突成立到 SC 断开 < 500 ms
```

记录：

- `CONFLICT_RAW`
- `RC_DELAY`
- `U2_OUT`
- `U7_OUT`
- `RELAY_GATE`
- `SC_CLOSED`

### T06：10 s 自动复位

先使 BSPD 触发，再清除冲突。

验收：

```text
冲突消失后 10.0 s 内 SC 不得重新闭合
名义恢复时间应接近 13.2 s
```

### T07：复位期间再次冲突

在复位计时5 s时重新施加足以越过R8/C11与U2阈值的冲突，台架值采用
700 ms，然后再次清除。100 ms冲突应被输入滤波拒绝，不能用于本项。

验收：

```text
C3 被重新放电
10 s 计时重新开始
不得沿用第一次剩余时间
```

### T08：BSPD 掉电

先使继电器正常吸合，然后将 +5 V 或 +24VIN 断电。

验收：

```text
继电器释放
SC 断开
```

记录从掉电到触点断开的时间。

### T09：Q2低边放电确认

按当前权威网表运行含体二极管的AO3400模型，检查：

- Q2导通时C3被可靠放电；
- 冲突持续时U7输出和SC保持在触发状态；
- 冲突清除后C3正常充电；
- 恢复期间再次发生有效冲突时，C3重新放电且复位计时重新开始。

### T10：阈值扫描

分别对 OIL 和 CURRENT 做慢速斜坡：

```text
0 V → 2.5 V → 0 V
```

检查实际翻转点和比较器失调角点。

### T11：元件容差角点

至少扫描：

```text
R8 = ±1%
C11 = ±10%
U2 VTP = min/max
R10 = ±1%
C3 = ±20%
比较器 VOS = ±5 mV
```

报告：

- 最快/最慢 BSPD 断开时间；
- 最短/最长自动复位时间；
- 是否满足 500 ms 和 10 s 要求。

### T12：SCS 开路故障

模拟分别拔掉：

```text
OIL1、OIL2、OIL3、OIL4、CURRENT
```

由于当前板上输入存在上拉，开路后输入将趋近高电平。检查：

- 单独开路时逻辑状态；
- 与另一条件组合时是否触发；
- 是否会错误地产生永久制动或永久功率有效状态。

### T13：SCS 对地短路

依次将 OIL1～OIL4、CURRENT 短接 GND。

重点检查：

```text
CURRENT 对地短路时，真实功率超过阈值是否可能被永久屏蔽
```

若会屏蔽 BSPD，应在报告中标为 SCS 合规风险，不得把仿真通过判定为整个设计合规。

### T14：SCS 对 +5 V 短路

依次将输入短接 +5 V，检查误触发和安全状态。

---

## 10. 自动测量语句

在 LTspice 中加入 `.meas`，至少自动输出：

```text
t_conflict_start
t_sc_open
trip_delay = t_sc_open - t_conflict_start

t_conflict_clear
t_sc_close
reset_delay = t_sc_close - t_conflict_clear

v_oil_threshold
v_current_threshold
v_rc_at_trip
```

测试脚本应自动判定：

```text
trip_delay < 0.500 s
reset_delay >= 10.000 s
power_loss 后 SC_CLOSED = 0
```

仿真结果同时导出 CSV 和 Markdown 报告。

---

## 11. 需要绘制的波形

每个关键测试至少绘制：

1. `OIL1～OIL4`
2. `CURRENT`
3. 四路比较器输出
4. `BRAKE_VALID`
5. `CURRENT_VALID`
6. `CONFLICT_RAW`
7. `RC_DELAY`
8. `U2_OUT`
9. U7 的 `TRIG`
10. U7 的 C3 定时节点
11. `U7_OUT`
12. `RELAY_GATE`
13. 继电器线圈电流
14. `SC_CLOSED`

纵轴使用 V、A 或逻辑状态，时间轴明确标注 ms/s。

---

## 12. 电源模块的独立仿真

另建 `lm2596_power_stage.cir`：

```text
输入：24 V
输出：5 V
L1：47 µH
D2：SS34
C1：100 µF
C2：220 µF
```

优先使用 TI 官方 LM2596 模型。测试：

1. 24 V 上电启动；
2. 50 mA、100 mA、200 mA 负载；
3. 输出启动时间；
4. 纹波；
5. 负载阶跃；
6. 输入掉电。

该仿真只评价供电，不用于证明 BSPD 的 500 ms 和 10 s 时序。

---

## 13. 仿真结论边界

仿真可证明：

- 电路逻辑关系；
- 名义及容差下的触发时序；
- 复位时序；
- 掉电后继电器释放趋势；
- Q2 方向错误的电气影响；
- 一部分 SCS 故障传播路径。

仿真不能直接证明：

- 未经传感器数据表与台架标定确认的量程、零点和满量程误差；
- 450 V 之外母线电压变化时，固定 11.11 A 阈值是否仍准确代表 5 kW；
- 线束瞬态、EMC、地偏移；
- 继电器触点粘连；
- 机械振动和温度寿命；
- 所有 SCS 要求均已满足。

---

## 14. 参考器件资料

- TI LM2596  
  https://www.ti.com/lit/ds/symlink/lm2596.pdf

- TI SN74LVC1G17  
  https://www.ti.com/lit/ds/symlink/sn74lvc1g17.pdf

- TI SN74LVC1G08  
  https://www.ti.com/lit/ds/symlink/sn74lvc1g08.pdf

- TI SN74LVC1G14  
  https://www.ti.com/lit/ds/symlink/sn74lvc1g14.pdf

- Nexperia 74HC32D  
  https://www.nexperia.com/product/74HC32D

- UMW LM339 系列  
  https://www.umw-ic.com/static/pdf/e9a6ddb2e9c018b9e8a573e6b93cf96d.pdf

- GOODWORK AO3400  
  https://www.goodworksemi.com/products/ao3400/

- Songle SRD-05VDC-SL-C  
  采用厂家数据表或 LCSC/JLCPCB 对应 C35449 资料核对线圈和触点引脚。

---

## 15. 可直接交给 Codex 的任务

```text
请根据本目录中的 BSPD 电路设计说明、最新网表和 BOM，建立可由 LTspice XVII 直接运行的仿真工程。

要求：
1. 以最新网表为连接依据，不得仅凭原理图图片猜测连接。
2. 功能仿真使用理想 5 V 电源；LM2596 单独仿真。
3. 优先使用官方模型。没有官方模型时使用明确标注的行为宏模型。
4. 比较器必须建模为开集电极输出，不能用推挽比较器代替。
5. SN74LVC1G17 和 SN74LVC1G14 必须具有施密特迟滞。
6. AO3400 模型必须包含体二极管。
7. Q2严格按权威网表的2脚接GND、3脚接C3定时节点建模，并使用含体二极管的模型验证放电与重新计时。
8. 完成 T01～T14 全部测试。
9. 使用 .meas 自动测量 500 ms 触发和 10 s 复位。
10. 输出可运行的 .asc/.cir、模型文件、运行脚本、CSV 结果、波形和 report.md。
11. 不得把行为模型描述为精确器件模型。
12. 若当前电路未通过某项测试，应保留失败结果并说明原因，不得通过修改测试条件隐藏问题。
```
