# Arduino Nano GPIO 测试器

适用于 Arduino Nano、ATmega328P、5 V / 16 MHz、Old Bootloader。程序启动后所有测试引脚均保持高阻输入，D0/D1 留给 USB 串口，不会自动扫描或驱动引脚。

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

## 电气限制

- GPIO 仅允许 0–5 V，任何引脚不得接入负电压或高于 VCC 的电压。
- 不要把两个输出脚设置为相反电平后直接短接。
- 建议外接信号串联 1 kΩ 电阻；单引脚持续电流控制在 20 mA 以内。
- A6/A7 只能做模拟输入；D0/D1 被 USB 串口占用。
