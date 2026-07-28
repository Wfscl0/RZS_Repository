# RES 遥控端 STM32F103C8T6 固件

本工程按仓库中的《2026中国大学生方程式系列赛事规则（最终版）》设计，不沿用旧 RES 说明书中的 CAN 字节或继电器状态定义。

## 目标硬件

- MCU：STM32F103C8T6，LQFP48，外部 8 MHz 晶振；
- LoRa：SX1276/SX1278 类 SPI 模块，3.3 V 逻辑；
- 电池 ADC：ADS1115，地址 `0x48`，AIN0 单端采样；
- 按钮：GO 常开触点到 GND；SHUT 急停常闭触点到 GND；
- 指示输出：4 路 3.3 V 逻辑，进入隔离/三极管驱动后再驱动继电器或 LED；
- 下载调试：SWD，PA13/PA14。

## 已实现的安全行为

- 上电先做 2 s 全灯检查，GO 必须先稳定释放才可重新布防；
- SHUT 使用常闭回路，按钮按下、线束开路或插头脱落都会立即锁存急停；
- GO 只有在 300 ms 内收到合法接收端 ACK 时才接受，并重复发送 600 ms；
- 一旦 GO 已授权，连续 500 ms 未收到 ACK，遥控端锁存急停；恢复通信后只发送急停，不能软件复位；
- 每帧有配对 ID、启动会话 ID、序号和 CRC16，SX127x 硬件包 CRC 同时开启；
- 三个频点逐帧轮换；接收端必须使用相同频点表并在失链时轮询重捕获；
- ADS1115 采集电池电压，低电量和 ADC 故障都有独立灯态；
- IWDG 约 2 s，看门狗复位或遥控端掉电后，接收端必须依靠自己的 500 ms 心跳超时断开安全回路。

规则要求的“掉电/丢链 1.5 s 内断开安全回路”和“非可编程逻辑锁存”必须最终由赛车端接收模块与硬件安全回路保证。遥控端固件不能替代 AV1.4.4、AV1.5.3 所要求的赛车端继电器和非可编程锁存电路。

## 使用前必须修改/确认

1. 在 `Core/Inc/res_config.h` 中确认频点、发射功率、配对 ID、实际电阻分压和电池阈值。
2. 目前默认分压为 100 kΩ/27 kΩ，按 3S 锂电池阈值设置。若原理图不同，必须按实物修改并标定。
3. 默认三频点和 10 dBm 仅是开发配置。比赛前必须确认无线模块型号、天线、占用带宽、EIRP 和场地允许频段。
4. 接收端必须实现同一协议、同一频点表、帧 CRC/序号/会话检查、500 ms 超时、硬件继电器直接串入 SDC，以及只能人工复位的非可编程锁存。
5. 该工程是可测试的工程样机固件，不是 SIL 或功能安全认证成品。整车测试必须覆盖断电、遮蔽天线、连续急停、进水、振动、按钮和线束开短路。

## 编译和下载

已通过 PlatformIO + STM32CubeF1 实际编译，生成的可烧录文件为
`output/RES_Controller_F103C8T6.bin`。本次构建占用 12,164 B Flash、
408 B RAM；构建日志中的警告仅来自 STM32CubeF1 供应商文件的未使用参数。

安装 PlatformIO 后，在本目录执行：

```powershell
pio run
pio run --target upload
```

`platformio.ini` 使用 `bluepill_f103c8`、STM32Cube HAL 和 ST-Link。

主机侧状态机和协议测试可直接运行：

```powershell
gcc -std=c11 -Wall -Wextra -Werror -ICore/Inc `
  tests/test_res_logic.c Core/Src/res_fsm.c Core/Src/res_protocol.c `
  -o tests/res_logic_tests.exe
.\tests\res_logic_tests.exe
```
