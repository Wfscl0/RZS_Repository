# RES 软件交付与烧录说明

## 1. 交付内容

本目录包含四个需要烧录的固件实例：

1. 遥控器外部主控：STM32G0B1CBT6；
2. 赛车端外部主控：STM32G0B1CBT6；
3. 遥控器 E220-400MBL-01 板载 STM8L151G4 无线桥；
4. 赛车端 E220-400MBL-01 板载 STM8L151G4 无线桥。

两个 STM32 工程共享协议、CRC16、SipHash-2-4 鉴权、会话号、序号与
重放窗口。两个 STM8 工程使用相同的三频点表，并实际调用 LLCC68
驱动切换射频中心频率。

## 2. STM32 工程入口

### 遥控器

- CubeMX：`remote_g0b1/RES_Remote_G0B1.ioc`
- CubeIDE：`remote_g0b1/STM32CubeIDE`
- 应用状态机：`remote_g0b1/Core/Src/res_remote_app.c`
- 板级适配：`remote_g0b1/Core/Src/res_stm32_port.c`

引脚：PB0=GO，PB1=STOP_FAULT，PA8=INA_ALERT，PB6/PB7=I2C1，
PA9/PA10=USART1 TX/RX，PB10--PB13=四个指示灯。

### 赛车端

- CubeMX：`vehicle_g0b1/RES_Vehicle_G0B1.ioc`
- CubeIDE：`vehicle_g0b1/STM32CubeIDE`
- 应用状态机：`vehicle_g0b1/Core/Src/res_vehicle_app.c`
- 板级适配：`vehicle_g0b1/Core/Src/res_vehicle_stm32_port.c`

引脚：PB10/PB11=两个低有效继电器驱动，PB12=START_OUT，
PB13=FAULT_OUT，PB8/PB9=FDCAN1 RX/TX，PA9/PA10=USART1 TX/RX，
PA0=CAN_STB。

两端时钟均为 64 MHz，USART1 为 9600-8-N-1，IWDG 约 1 s。赛车端
Classic CAN 为 500 kbit/s、采样点 87.5%。

## 3. E220 无线桥工程

打开：

`radio_bridge_stm8/E220_IAR_SDK/3_代码工程/0_Project/IAR_for_Stm8/Uart_PingPong/project.eww`

遥控器和赛车端烧录同一份程序。桥接层只负责完整帧转发、CRC 预检、
物理换频和丢帧扫描，最终鉴权与安全状态判断仍在 STM32 上完成。

当前台架频点为 433.300、433.900、434.500 MHz，接收扫描驻留 240 ms，
空中速率配置索引为 4。比赛使用前必须依据赛事分配和现场法规确认
频点、带宽、发射功率、EIRP 与占空比，不能只修改一端。

## 4. 赛车端状态逻辑

- 全部断电：两个继电器由硬件保持断开；
- 仅赛车端上电：继电器 1 闭合、继电器 2 断开；
- 新会话连续收到 3 帧有效 READY：两个继电器闭合；
- 新 GO 计数：两个继电器保持闭合，START_OUT 输出 100 ms，同时发送
  CAN GO 事件；
- 真实 STOP 或连续 500 ms 无有效无线帧：两个继电器断开并锁存；
- 锁存后同会话 READY 无效；释放急停并重启遥控器，形成新鉴权会话，
  连续 3 帧 READY 后才允许恢复。

赛车端不会自行生成 `RES_ERROR`。VCU 必须监控 0x510 状态帧，检测
超时、协议版本、状态与继电器反馈组合，并驱动独立的 RES_ERROR
硬件输出；实现要求见 `VCU_INTEGRATION.md`。

## 5. CAN 约定

- 0x510：RES_STATUS，每 50 ms；
- 0x511：RES_GO_EVENT，每次新的操作员 GO 动作只发送一次；
- 0x512：RES_DIAGNOSTIC，与 GO 事件同时发送诊断副本。

所有报文均为 11 位标准 ID、Classic CAN、8 字节。VCU 不应仅凭
0x511 启动车辆，还应同时验证新鲜的 0x510、READY 状态和自身安全条件。

## 6. 烧录前必须修改

`RES_DEMO_AUTH_KEY_BYTES` 是公开演示密钥，没有现场安全意义。应在两端
替换为相同的随机 16 字节队内密钥，建议放入不提交版本库的本地头文件。

还必须实测继电器模块的有效电平。当前程序按低电平吸合配置，并要求
PB10/PB11 外加 4.7--10 kOhm 上拉，使 MCU 复位、掉电和下载期间继电器
保持释放。

## 7. 已完成的软件验证与尚未完成项

主机测试使用 `-Wall -Wextra -Werror -pedantic`，协议、遥控器状态机、
赛车端状态机共 3 组测试已通过；STM8 桥接源文件也通过主机语法编译。
两个 IOC 已经 CubeMX 命令行重新读取并生成验证。

当前电脑没有 ARM GCC/IAR STM8 编译器，因此尚未产生可直接烧录的
目标文件。请分别在 STM32CubeIDE 和 IAR 中完整编译，并严格执行
`VERIFICATION.md` 的台架、HIL、故障注入和 1500 m 场地测试。完成这些
测试前，不能把该原型声明为赛事合规或直接接入赛车安全回路。
