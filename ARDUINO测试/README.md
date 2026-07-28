# Arduino Nano GPIO 测试器

统一实测记录见 [`测试汇总.md`](测试汇总.md)。

适用于 Arduino Nano、ATmega328P、5 V / 16 MHz。通用程序
`ArduinoNano_GPIO_Test.ino` 启动后所有测试引脚均保持高阻输入，D0/D1
留给USB串口，不会自动扫描或驱动引脚。三个板卡专用程序具有各自的安全
启动电平，必须先阅读程序头部接线说明；不能假定它们启动后全部高阻。

## 编译和烧录

在 PowerShell 中运行：

```powershell
.\build_upload.ps1 -Port COM3
```

烧录前脚本会把当前 Flash 和 EEPROM 备份到 `backups`。只编译不烧录：

```powershell
.\build_upload.ps1 -NoUpload
```

串口参数：115200 baud、8N1、行尾选择 Newline 或 Both NL & CR。

## 常用命令

```text
HELP
LIST
MODE D2 OUT
WRITE D2 1
READ D3
AREAD A0
PWM D3 128
PAIR D2 D3
SAFE
```

`PAIR D2 D3` 的用法：先断电，用跳线连接 D2 与 D3，再上电发送命令。程序依次输出低、高电平并从输入脚回读，最后恢复两脚为高阻；结果为 `PASS` 或 `FAIL`。可逐对测试其它 GPIO。

## 板卡专用程序

| 程序 | 用途 |
|---|---|
| `TSAL_Bench_Test.ino` | TSAL互补输入、模拟输入和开漏灯输出测试 |
| `LOCK_Bench_Test.ino` | 错误锁存板故障、复位、LED和安全触点测试 |
| `BSPD_Bench_Test.ino` | BSPD五路0/5 V数字输入、触发时序和安全触点测试 |

Bootloader不能只按板型猜测。BSPD测试使用的COM4设备在2026-07-28实测为
Old Bootloader：New模式无法同步，Old模式上传并回读校验成功。

## 电气限制

- GPIO 仅允许 0–5 V，任何引脚不得接入负电压或高于 VCC 的电压。
- 不要把两个输出脚设置为相反电平后直接短接。
- 建议外接信号串联 1 kΩ 电阻；单引脚持续电流控制在 20 mA 以内。
- A6/A7 只能做模拟输入；D0/D1 被 USB 串口占用。
