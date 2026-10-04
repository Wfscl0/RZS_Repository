# RES STM32 HIL 构建清单（2026-09-03）

## 用途与边界

本清单记录本工作区当前源码生成的两个 STM32G0B1 **候选烧录映像**。它们已经完成交叉编译、链接和格式转换，但尚未完成实物烧录、读回和 HIL 故障注入；不得据此宣称整车或安全功能已验证。

- 目标 MCU：STM32G0B1CBT6，Cortex-M0+，128 KB Flash、144 KB SRAM。
- 工具链：GNU Arm Embedded Toolchain 10.3-2021.10，`arm-none-eabi-gcc.exe`。
- 生成脚本：`../tools/build_stm32_g0b1_gcc.ps1`。
- 优化/宏：`-Og -g3 -std=gnu99`、`USE_HAL_DRIVER`、`STM32G0B1xx`。
- 生成时间：2026-09-03（本地工作树）。如果源码、编译器或脚本改变，必须重建并更新本清单。

## 映像与校验值

| 目标 | 文件 | 字节数 | SHA-256 |
|---|---|---:|---|
| 遥控端 | `remote/gcc/RES_Remote_G0B1.hex` | 56,872 | `58A8DCE67D35608A708B3DE8EE6B9F13CC18CAFE6068ECE45D55443345C3B32F` |
| 遥控端 | `remote/gcc/RES_Remote_G0B1.bin` | 20,188 | `3E2F45D13528F7DCBD51699FF7D7FDB247EB8A35BE22268D918EEC2D7263D013` |
| 车载端 | `vehicle/gcc/RES_Vehicle_G0B1.hex` | 50,662 | `3450484EE9A4C9585E1DE5829323933565D3EB0A9FF986D04207A062CD93FC8C` |
| 车载端 | `vehicle/gcc/RES_Vehicle_G0B1.bin` | 17,980 | `9189872BBAB9C67F8C1603245C81FA34B4431C37C2EB251C2CEBEC04AC1696C5` |

对应 `.elf` 和 `.map` 位于同一目录，仅用于调试、符号定位和尺寸审查，不能直接用于普通烧录器。

## 可复现构建

在 `firmware/` 目录执行：

```powershell
.\tools\build_stm32_g0b1_gcc.ps1 -Target remote
.\tools\build_stm32_g0b1_gcc.ps1 -Target vehicle
Get-FileHash .\artifacts\remote\gcc\RES_Remote_G0B1.hex, .\artifacts\vehicle\gcc\RES_Vehicle_G0B1.hex -Algorithm SHA256
```

如需通过本机 J-Link 做受保护的下载，先只运行校验模式，再在隔离台架上显式加入 `-Program`：

```powershell
.\tools\flash_stm32_g0b1_jlink.ps1 -Target remote
.\tools\flash_stm32_g0b1_jlink.ps1 -Target remote -Program
.\tools\flash_stm32_g0b1_jlink.ps1 -Target vehicle -Program
```

默认下载后 MCU 保持暂停；只有明确加入 `-RunAfterFlash` 才会放开运行。脚本会核对本清单 SHA-256，不匹配时拒绝写入；`-SkipHashCheck` 仅限负责人已更新和复核新清单后的受控使用。

脚本保留原 CubeIDE 配置不动。车载端原始 CubeIDE 链接脚本含 GNU 11 才支持的 `READONLY` 属性；为使本机 GNU 10.3 能重建，脚本只对车载端使用 `vehicle_g0b1/MDK-ARM/STM32G0B1CBTX_FLASH_GCC10.ld` 这个兼容副本。

## 烧录前检查

1. 在假负载、真实 SDC/LVMS 断开的条件下核对目标板卡、SWD 接线和当前映像哈希。
2. 先按端点 `Docs/HARDWARE_ALLOCATION_CN.md` 测量未上电、复位和下载时的继电器安全默认值。
3. 通过 J-Link/Keil 或受控烧录器下载后读回或执行校验，再按照 `../docs/HIL_TEST_CHECKLIST_CN.md` 进行无线、CAN、超时和故障注入测试。
4. 如果使用 Keil 重新编译的 `MDK-ARM/Objects/` 映像，不能沿用本清单哈希；应建立对应的 Keil 构建记录。
