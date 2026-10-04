from pathlib import Path
from reportlab.pdfgen import canvas
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from reportlab.lib.colors import HexColor

ROOT = Path(__file__).resolve().parents[2]
OUT = Path(__file__).with_name('RES_双端逐针接线与检查.pdf')
pdfmetrics.registerFont(TTFont('CN', 'C:/Windows/Fonts/simhei.ttf'))
c = canvas.Canvas(str(OUT), pagesize=(595.28, 841.89))
c.setTitle('RES 双端逐针接线与检查 - STM32G0B1 - 2026-09-10')
INK = '#183349'
BLUE = '#176D9C'
RED = '#AD332A'

def txt(x, y, s, size=10, color=INK):
    c.setFillColor(HexColor(color)); c.setFont('CN', size); c.drawString(x, y, s)

def line(x1,y1,x2,y2,color=BLUE):
    c.setStrokeColor(HexColor(color)); c.setLineWidth(1); c.line(x1,y1,x2,y2)

def start(n, title, subtitle):
    txt(34, 804, title, 17)
    txt(34, 782, subtitle, 9)
    line(34,770,561,770)
    txt(34,22,'2026-09-10 | 当前 G0B1 固件核对版 | 台架接线，不代表整车安全验收',8)
    txt(515,22,f'{n} / 3',9)

def note(y, strings, color=INK):
    for s in strings:
        txt(36,y,s,10,color); y-=17
    return y

def wires(y, rows):
    # Identical y positions at both ends: each row is one wire, no crossing.
    for left, right, direction, label in rows:
        txt(45,y-3,left,10)
        line(189,y,319,y)
        if direction in ('right','both'):
            line(313,y+3,319,y); line(313,y-3,319,y)
        if direction in ('left','both'):
            line(189,y,195,y+3); line(189,y,195,y-3)
        txt(209,y+6,label,8,BLUE)
        txt(331,y-3,right,10)
        y-=34
    return y

def section(y,title):
    txt(34,y,title,12,BLUE); return y-23

start(1,'移动端 / 手持遥控器','STM32G0B1CBT6：板上 A9 = PA9、B10 = PB10；按丝印找针，不按照片左右数针。')
txt(45,749,'STM32 端',11); txt(331,749,'外部模块端',11)
y=wires(725,[
 ('PA9 / A9','LoRa RXD','right','UART TX'),
 ('PA10 / A10','LoRa TXD','left','UART RX'),
 ('3V3 逻辑电源','LoRa VIO','right','3.3 V'),
 ('GND / G','LoRa GND','none','信号参考地'),
 ('PB0 / B0','GO 常开按钮一端','left','按下 = LOW'),
 ('PB1 / B1','STOP 常闭按钮一端','left','正常 = LOW'),
 ('PB6 / B6','INA226 SCL','right','I2C 时钟'),
 ('PB7 / B7','INA226 SDA','both','I2C 数据'),
 ('PA8 / A8','INA226 ALERT（可选）','left','预留输入'),
 ('PB10 / B10','四路灯继电器 IN1：蓝灯','right','低有效'),
 ('PB11 / B11','四路灯继电器 IN2：黄灯','right','低有效'),
 ('PB12 / B12','四路灯继电器 IN3：绿灯','right','低有效'),
 ('PB13 / B13','四路灯继电器 IN4：红灯','right','低有效'),
])
y=section(264,'按钮与灯的另一端如何接')
note(y,[
 '直接按钮方案：GO 的另一端接 GND；STOP 的另一端接 GND。',
 'GO 使用 NO 常开触点；STOP 使用 NC 常闭触点，不可把 STOP 改成常开。',
 '若保留图中的 Relay_ButtonCheck 两路板，请改用第 3 页的替代接法。',
 '灯触点：每路 NO 接灯额定电源正极，COM 接灯正极，灯负极接该电源负极。',
 '每路 NC 不接。裸 LED 必须串限流电阻；不要直接接 5 V。',
 '四路板 GND 接控制地；VCC / JD-VCC 电压和跳帽按实物规格核实。',
 '以上 IN1~IN4 仅适用于已确认 3.3 V 兼容、低电平触发的输入。',
 'INA226 VCC 接 3.3 V，GND 接控制地；SCL/SDA 上拉只接 3.3 V。',
 'INA226 测量端 VIN+/VIN-/VBUS 须按实际模块原理图另核，不能当供电脚。',
 '固件标定：地址 0x40、分流电阻 R010；采样无效可能阻止 READY。',
 'LoRa 主电源接法见第 3 页：只接 VIO 不等于完成射频板供电。',
])
c.showPage()

start(2,'车载端 / RES 接收器','逻辑引脚已核对固件；KJ1/KJ2 的物理通道分配为本图建议，接实物前须测通断确认。')
txt(45,749,'STM32 端',11); txt(331,749,'外部模块端',11)
wires(725,[
 ('PA9 / A9','LoRa RXD','right','UART TX'),
 ('PA10 / A10','LoRa TXD','left','UART RX'),
 ('3V3 / GND','LoRa VIO / GND（两根线）','none','同名对应'),
 ('PB8 / B8','CAN 收发器 RXD','left','FDCAN RX'),
 ('PB9 / B9','CAN 收发器 TXD','right','FDCAN TX'),
 ('PA0 / A0','CAN 收发器 STB','right','高待机 / 低正常'),
 ('PB10 / B10','KJ1 驱动 IN：EBS 电源','right','逻辑 R1 / 低有效'),
 ('PB11 / B11','KJ2 驱动 IN：SDC','right','逻辑 R2 / 低有效'),
 ('PB12 / B12','适配接口 -> VCU GO 输入','right','高脉冲约 100 ms'),
 ('PB13 / B13','适配接口 -> 故障监测输入','right','高 = FAULT'),
])
y=section(374,'CAN 总线侧（不是 STM32 GPIO）')
note(y,[
 '收发器 CANH -> VCU CANBH；收发器 CANL -> VCU CANBL。',
 '非隔离接口按设计共信号地；隔离型按其手册接两侧地，不擅自跨接隔离。',
 'Classic CAN 500 kbit/s；总线只在两个物理端点各装 120 Ω。',
 'PB12/PB13 为 3.3 V 逻辑；VCU 插头针号尚未核定，不可接 12/24 V 输入。',
 'PB13 FAULT_OUT 不是 VCU 的 RES_ERROR，不能直接代替独立硬件锁存。',
])
y=section(247,'继电器触点端：两条不同回路，不能串成一条 SDC')
note(y,[
 '24V供电_OUT -> KJ1 COM -> [KJ1 NO 常开触点] -> EBS_PWR_IN',
 'SDC_IN       -> KJ2 COM -> [KJ2 NO 常开触点] -> SDC_OUT',
 'KJ1 = 参考图 RES2；KJ2 = 参考图 RES1。两个 NC 均不作上述输出。',
 '建议：IN1 控制 COM1/NO1 时，通道 1 标 KJ1；通道 2 标 KJ2。',
 '须断电测清 IN 与 COM/NO 对应；原图 RL1/RL2 交叉线不能按编号照搬。',
 'MCU 只接驱动 IN，不直接接线圈、24 V、SDC 或 EBS_PWR。',
 'ASMS 机械联动的 SDC 旁路按整车图独立实现，不用 GPIO 代替。',
],INK)
note(92,[
 '注意：WAIT_LINK 下 R1 吸合、R2 释放；按本图即 KJ1/EBS 电源先接通。',
 '该行为必须经安全设计复核；本次仅接假负载，不授权直接接真实回路。',
],RED)
c.showPage()

start(3,'供电、按钮检测板与逐项核线','端口名称以实物丝印和模块原理图为准；未确认的电源/接口针号不凭外形推断。')
y=section(745,'1. 两端各自的电源与 LoRa')
note(y,[
 '两端无线相连，不需要在车与遥控器之间拉地线。每端内部建立本地控制地。',
 '12 V 电源 -> 合适的电源模块输入；STM32 3V3 只能接稳压 3.3 V。',
 '选择一种 MCU 供电入口，未核实防倒灌前不并接 USB 与外部 3V3/5V。',
 'LoRa：PA9 -> RXD，PA10 <- TXD，VIO = 3.3 V，GND 接本地控制地。',
 'LoRa VCC/主电源及 VIO 跳帽须核实板型；VIO 不是通用的主电源入口。',
 'LoRa PC0、PB4、PB5、PB6、PB7 不接外部 STM32；当前走串口桥接。',
 '连接板虽预留 PB5 开漏复位，当前应用未使用；不是直接连 PC0 的依据。',
 'LoRa USB/CH340 不可与 MCU 同时驱动 RXD；两块板的桥接固件须匹配。',
 '继电器线圈供电按铭牌，不能靠 GPIO 供电；5 V 线圈不代表 IN 是 3.3 V 兼容。',
 'CAN 电源按实际型号接；只有标有 VIO 且支持 3.3 V 的型号才按该方式接。',
])
y=section(535,'2. Relay_ButtonCheck：替代第 1 页的直连按钮方案')
note(y,[
 '仅适用于已确认低电平触发、开路可靠释放的两路模块；不要与直连方案混用。',
 '模块 VCC -> 额定控制电源；模块 GND -> 本地控制地。',
 'IN1 -> GO 常开按钮 -> GND；COM1 -> PB0；NO1 -> GND；NC1 不接。',
 'IN2 -> STOP 常闭按钮 -> GND；COM2 -> PB1；NO2 -> GND；NC2 不接。',
 '正常：第 2 路持续吸合，PB1 为低；STOP 按下/线断/检测板断电：PB1 为高。',
 '不得用 NC2 接 PB1 来替代上述 NO2 接法，否则掉电时可能被误判为健康。',
])
y=section(399,'3. SWD 与上电前检查')
note(y,[
 '两端均：J-Link SWDIO -> PA13/DIO；SWCLK -> PA14/CLK；GND -> GND。',
 'J-Link VTref -> 目标 3.3 V 参考；nRESET -> NRST/RST（若引出）。',
 'VTref 不作为整机供电输出；按线缆标记接，不凭线色或未核实的针序接。',
 '[ ] 断开真实 SDC/EBS/动力负载；先用限流台架电源和假负载。',
 '[ ] 断电查短路、极性、排针方向；确认 COM/NO/NC 与各 IN 的对应。',
 '[ ] 检查 IN 的电压兼容性；必要时加保持低有效逻辑的接口驱动。',
 '[ ] 车载 PB10/PB11 的硬件释放设计须覆盖 MCU 断电、复位及下载。',
 '    不能仅依赖软件或失电的 3.3 V 上拉；实测触点释放且无反向供电。',
 '[ ] GO 松开高、按下低；STOP 正常低、按下/断线高。',
 '[ ] READY 后两路闭合；STOP/无线超时后两路释放；以触点测量验收。',
 '[ ] CAN、LoRa、继电器均通过台架测试后，再按整车安全流程评审接入。',
])
y=section(169,'依据与仍待确认项')
note(y,[
 '依据：firmware/remote_g0b1 与 vehicle_g0b1 的 board_config、GPIO、',
 'USART、I2C/FDCAN 源码及 Docs/HARDWARE_ALLOCATION_CN.md。',
 '触点用途依据你修正的 RES 图；实物继电器触发电平、LoRa 电源跳帽、',
 'CAN 模块型号、VCU 插头针号、INA226 测量端定义尚不能由照片全部确认。',
 '本图不改变固件。旧 F103 引脚表和旧 SPI 接线图不适用于此版本。',
],INK)
c.save()
print(OUT)
