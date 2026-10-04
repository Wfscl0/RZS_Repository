# 2026 RES 项目交接说明（给后续 Agent）

> 更新时间：2026-08-22  
> 工作目录：`C:\Users\icemi\Desktop\RZS_Repository\RES`  
> 本文件描述当前真实设计、已经完成的测试以及仍未完成的工作。不得把“软件测试通过”写成“赛事合规”或“整车实测通过”。

## 1. 目标与系统边界

本项目是车队自制的遥控急停系统（RES），预期在存在少量建筑物遮挡的场地实现约 1500 m 稳定通信，并满足失效安全、故障保持、可佩戴/手持、防水、防震和自动跳频等要求。

系统链路为：

```text
遥控端按钮/电量检测
  -> 遥控端 STM32G0B1CBT6
  -> 遥控端 E220-400MBL-01（板载 STM8 + LLCC68）
  -> 无线链路
  -> 赛车端 E220-400MBL-01
  -> 赛车端 STM32G0B1CBT6
  -> 两路安全继电器 + START_OUT/FAULT_OUT + CAN
  -> VCU
  -> VCU 判断并输出 RES_ERROR
  -> 独立硬件锁存板
```

重要边界：`RES_ERROR`由 VCU 根据 RES 的 CAN 状态判断后输出，最终故障锁存位于独立硬件锁存板。赛车端软件内部也有补充性的安全状态锁存，但它不能替代 VCU 和硬件锁存板。

## 2. 当前硬件方案

### 2.1 遥控端

- 主控：STM32G0B1CBT6 模块；
- 无线：E220-400MBL-01；
- 电源：12 V、约 2500 mAh 电池，实物外形小于等于 56 × 20 × 70 mm；
- 电量检测：INA226，I2C 地址 0x40；
- 操作：启动按钮 GO、急停检测 STOP_FAULT；
- 指示：红/绿用于电量，蓝/黄用于系统状态；
- 天线：壳体前侧防水 SMA-K 母座，M10 × 1 mm。

遥控端 STM32 引脚：

| 功能 | STM32引脚 | 电气逻辑 |
|---|---|---|
| GO按钮 | PB0 | 低有效，NO按钮接地；软件防抖25 ms |
| STOP_FAULT | PB1 | 高有效；NC检测链健康时为低，急停、断线或检测模块掉电时为高 |
| INA226 ALERT | PA8 | 报警输入 |
| INA226 SCL/SDA | PB6/PB7 | I2C1 |
| LoRa TX/RX | PA9/PA10 | USART1 TX/RX，9600-8-N-1 |
| 蓝灯 | PB10 | 状态灯，当前板级配置为低有效输出 |
| 黄灯 | PB11 | 状态灯，当前板级配置为低有效输出 |
| 绿灯 | PB12 | 电量正常，当前板级配置为低有效输出 |
| 红灯 | PB13 | 低电量/严重低电量，当前板级配置为低有效输出 |

### 2.2 赛车端

- 车载 12 V -> DCDC -> STM32 + E220 + CAN 收发器；
- 不使用 INA226；
- 两路低电平触发继电器；
- 通过 Classic CAN 向 VCU 报告状态和 GO 事件；
- START_OUT 和 FAULT_OUT 是冗余 3.3 V 逻辑输出。

赛车端 STM32 引脚：

| 功能 | STM32引脚 | 电气逻辑 |
|---|---|---|
| LoRa TX/RX | PA9/PA10 | USART1 TX/RX，9600-8-N-1 |
| FDCAN RX/TX | PB8/PB9 | Classic CAN，500 kbit/s |
| 继电器1 | PB10 | 低电平吸合，必须外加4.7–10 kΩ上拉 |
| 继电器2 | PB11 | 低电平吸合，必须外加4.7–10 kΩ上拉 |
| START_OUT | PB12 | 高有效，GO事件时输出100 ms |
| FAULT_OUT | PB13 | 高有效 |
| CAN_STB | PA0 | 高=待机，低=正常 |

### 2.3 E220当前接线

STM32与E220 UART必须交叉连接：

```text
STM32 PA9 / TX  -> E220 RXD（板端15脚）
STM32 PA10 / RX <- E220 TXD（板端14脚）
STM32 3.3 V     -> E220 VIO
STM32 GND       -> E220 GND
```

两块E220板目前均短接：1-2、3-4、16-17、18-19，即射频模块供电、板载MCU供电且M0/M1为正常模式。

当E220 UART已与STM32连接时，不得再同时用该E220的USB串口驱动TX/RX，否则板载CH340与STM32可能争用总线。当前遥控端E220 USB已拔掉。

## 3. 软件工程结构

主要目录：

```text
firmware/
  remote_g0b1/       遥控端 STM32 CubeMX/CubeIDE 工程
  vehicle_g0b1/      赛车端 STM32 CubeMX/CubeIDE 工程
  shared/            无线协议、CRC、鉴权、重放保护、CAN打包
  radio_bridge_stm8/ E220板载STM8自定义无线桥
  tests/             与硬件无关的协议和状态机测试
  tools/             PC串口车辆端测试程序
  docs/              交付、VCU接入和验证要求
```

关键文件：

- 遥控端 CubeMX：`firmware/remote_g0b1/RES_Remote_G0B1.ioc`
- 遥控端状态机：`firmware/remote_g0b1/Core/Src/res_remote_app.c`
- 遥控端板级接口：`firmware/remote_g0b1/Core/Src/res_stm32_port.c`
- 赛车端 CubeMX：`firmware/vehicle_g0b1/RES_Vehicle_G0B1.ioc`
- 赛车端状态机：`firmware/vehicle_g0b1/Core/Src/res_vehicle_app.c`
- 赛车端板级接口：`firmware/vehicle_g0b1/Core/Src/res_vehicle_stm32_port.c`
- CAN协议：`firmware/shared/include/res_can_contract.h`
- VCU DBC：`C:\Users\icemi\Desktop\RZS_Repository\VCU\VCU_DBC.dbc`
- HIL检查表：`firmware/docs/VERIFICATION.md`

两端STM32系统时钟均为64 MHz，IWDG约1 s。遥控端当前台架固件使用了 `RES_E220_STOCK_BRIDGE_TEST=1`，将无线ACK/链路超时放宽以兼容原厂E220演示桥接程序；该宏不是最终比赛配置。

## 4. 无线协议与安全机制

STM32间无线帧包含协议版本、类型、源/目的节点、标志、信道、序号、会话号和载荷。协议具备：

- CRC16帧完整性检查；
- SipHash-2-4鉴权标签；
- 每次上电的新会话号；
- 单调序号和重放窗口；
- GO命令计数去重；
- 需要ACK的报文；
- 针对半双工无线桥的stop-and-wait发送；
- STOP高优先级重复发送。

仓库内的 `RES_DEMO_AUTH_KEY_BYTES` 是公开演示密钥，比赛和外场测试前必须替换成两端相同、未提交版本库的随机16字节密钥。

### 自动跳频的真实状态

最终设计包含E220板载STM8自定义桥接固件：三个实际频点为433.300、433.900、434.500 MHz，STM8调用LLCC68驱动进行物理换频，并在丢帧后扫描三个频点。相关文件位于 `firmware/radio_bridge_stm8/`。

但是截至本交接时间，两块E220实物仍在使用原厂/演示桥接固件。已完成的无线台架测试只能证明单频透明传输和双向ACK正常；STM32帧中的信道索引虽然轮转，但在烧录自定义STM8固件前不等于真实物理跳频。不得据此宣称自动跳频已完成实测。

## 5. 状态机

### 5.1 遥控端

1. 上电进入 `STARTUP_STOP`，检查急停输入和INA226；
2. 输入健康且电量有效后进入 `READY`；
3. 只有收到经过鉴权的赛车端回复并保持链路有效时，GO上升沿才会发送GO命令；
4. STOP_FAULT不做延迟防抖，一个有效高电平即进入 `STOP_LATCHED`；
5. 严重低电量或INA226持续无效也会锁存STOP；
6. 松开急停不能清除锁存，必须重新上电形成新会话。

遥控端指示灯：

- 蓝：链路有效且遥控端/赛车端状态一致；
- 黄：失联、故障或急停锁存时闪烁；
- 绿：电量检测有效且无低电量警告；
- 红：低电量常亮，严重低电量闪烁。

### 5.2 赛车端

| 工况 | 继电器1 | 继电器2 | 状态/输出 |
|---|---:|---:|---|
| 两端都未上电 | 断开 | 断开 | 由硬件默认保证 |
| 仅赛车端上电 | 闭合 | 断开 | WAIT_LINK，FAULT_OUT有效 |
| 连续3帧鉴权READY | 闭合 | 闭合 | READY，FAULT_OUT无效 |
| 新GO事件 | 闭合 | 闭合 | START_OUT 100 ms并发送CAN事件 |
| STOP或无线超时 | 断开 | 断开 | STOPPED_FAULT并软件锁存 |
| 同一会话再次READY | 断开 | 断开 | 不允许恢复 |
| 急停释放且遥控器重启，新会话连续3帧READY | 闭合 | 闭合 | 恢复READY，前提是无本地硬件故障 |

赛车端无线失联锁存阈值目前为500 ms。VCU还必须独立以150 ms的CAN状态超时产生RES_ERROR，不能只依赖赛车端软件。

## 6. CAN/DBC约定

基础参数：Classic CAN、11位标准帧、500 kbit/s、DLC=8。赛车端当前只发送，不接收VCU控制命令。

### 0x510 RES_STATUS，50 ms周期

| 字节 | 内容 |
|---:|---|
| 0 | 协议版本，固定1 |
| 1 | 状态：0 BOOT、1 WAIT_LINK、2 READY、3 GO_EVENT、4 STOPPED_FAULT |
| 2..3 | 小端故障/状态flags |
| 4 | 当前RF信道索引 |
| 5 | bit0继电器1指令，bit1继电器2指令 |
| 6..7 | 小端GO事件累计计数 |

flags低8位：

- bit0 `LINK_OK`
- bit1 `REMOTE_STOP`
- bit2 `RADIO_TIMEOUT`
- bit3 `AUTH_FAILURE`
- bit4 `RELAY_MISMATCH`
- bit5 `SESSION_RECOVERY`
- bit6 `CAN_LOCAL_FAULT`
- bit7 `SOFTWARE_LATCHED`

### 0x511 RES_GO_EVENT，事件触发

- Byte0..3：遥控端本次上电会话号，小端32位；
- Byte4..7：遥控端GO命令计数，小端32位。

VCU必须使用“会话号+命令计数”去重，并同时检查最新0x510是否新鲜、链路有效、状态为READY、两继电器闭合以及VCU自身AS Ready条件，不能单独凭0x511启动。

### 0x512 RES_DIAGNOSTIC，与GO同时发送

- Byte0..3：GO命令计数；
- Byte4..5：赛车端GO事件累计计数；
- Byte6：RF信道；
- Byte7：协议版本。

### VCU应执行的安全判断

- 超过150 ms没有有效0x510：RES_ERROR有效；
- 协议版本不为1：RES_ERROR有效；
- 状态不是READY或短暂GO_EVENT：RES_ERROR有效；
- LINK_OK=0、任一故障位有效或继电器位不等于0b11：RES_ERROR有效；
- VCU启动、CAN bus-off、解析错误、任务超时均默认RES_ERROR有效。

当前局限：DBC已定义 `AUTH_FAILURE` 和 `RELAY_MISMATCH`，但现有赛车端固件尚未把解析器的鉴权失败统计和实体继电器触点反馈完整接入这两个位。它们目前属于协议预留/部分实现项。

## 7. 已完成的测试

### 7.1 主机自动测试

Windows主机上已运行协议、遥控端状态机、赛车端状态机三组测试，结果3/3通过。覆盖：

- 帧编解码、鉴权和协议基础；
- GO必须在有效链路后才能触发；
- GO按钮防抖和重复命令抑制；
- STOP立即锁存且松开不自动恢复；
- READY、GO、STOP、失联时两继电器状态；
- START_OUT脉冲和FAULT_OUT；
- 蓝/黄/绿/红四个指示灯逻辑；
- 半双工stop-and-wait等待ACK。

### 7.2 实际无线HIL

当时台架：

```text
J-Link -> 遥控端STM32 -> 遥控端E220
赛车端E220 -> USB/COM7 -> PC车辆端测试程序
```

测试结果：30个通过鉴权的帧全部接收，PC返回30个ACK；其中1个HELLO、29个HEARTBEAT；序号12..41；STM32接收1590字节，UART错误计数为0。

这证明当前STM32-UART-E220-无线-E220-PC的双向数据链路可工作，但不代表实体按钮、继电器、CAN、真实跳频或1500 m距离已通过。

### 7.3 当前已烧录固件

- 已烧录：遥控端STM32G0B1；
- 固件：`firmware/remote_g0b1/build-gcc-live/RES_Remote_G0B1.bin`；
- SHA-256：`3EF5EC51ABC06128B513905B038BB218CB96F47F228B9EEC10BDB88A51024C10`；
- 该镜像是兼容原厂E220慢桥接的台架版本，不是最终比赛固件；
- J-Link实际可执行文件：`E:\JLink_V826\JLink.exe`；
- 烧录前备份：`firmware/remote_g0b1/backups/stm32g0b1_before_20260822.bin`；
- 备份SHA-256：`B5A41C3758763BBEC72769FAB4A2533BF2DB0B6312D93D25A695F9E4B9E02260`。

首次烧录后MCU曾进入系统ROM；在不改变OPTR内容的前提下触发Option Byte reload后已恢复从主Flash正常启动。不要无故重写RDP或其他Option Bytes。

## 8. 尚未完成，后续Agent必须继续

1. 接入INA226、GO/STOP实体按钮和四个实体指示灯，完成遥控端物理GPIO测试；当前缺少INA226时程序会安全锁存STOP，因此不能实物产生GO。
2. 准备并烧录赛车端STM32固件；当前没有赛车端可直接使用的BIN，也未做赛车端MCU实物测试。
3. 接入两路继电器，使用万用表测量COM-NO/COM-NC，不能只看继电器板LED。
4. 测试上电、复位、看门狗、掉电和下载期间继电器均保持安全状态。
5. 接入CAN收发器和VCU，验证0x510/0x511/0x512，并验证VCU在150 ms超时后产生RES_ERROR、独立锁存板保持故障。
6. 用IAR编译并通过SWIM向两块E220板载STM8烧录自定义桥接固件，确认两端频率表完全相同，再做真实物理跳频和干扰测试。
7. 替换公开演示密钥。
8. 完成CRC错误、鉴权错误、重放、断天线、断E220电源、断CAN、bus-off和继电器故障注入。
9. 最后进行1500 m少量建筑物遮挡场地测试，记录RSSI、丢包率、最坏STOP到继电器释放时间、低电量和最差天线方向。
10. 完成以上测试前，不得接入赛车最终安全回路或声明赛事合规。

## 9. 后续工作的优先顺序

建议下一个Agent按以下顺序推进：

1. 保持当前遥控端烧录镜像和备份不动，先确认工作树内已有用户修改；
2. 完成遥控端按钮/INA226/LED台架接线和实测；
3. 编译并烧录赛车端STM32，在空载条件下测试GPIO和CAN；
4. 接入继电器并做触点测试；
5. 完成VCU DBC接入和RES_ERROR硬件链路；
6. 最后烧录两个STM8无线桥并进行跳频、干扰和距离测试。
