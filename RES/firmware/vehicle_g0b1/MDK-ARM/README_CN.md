# Keil MDK-ARM 使用说明

打开 `RES_Vehicle_G0B1.uvprojx`。首次使用先安装 `Keil::STM32G0xx_DFP@2.1.0`；构建输出位于 `Objects/`，不应手工编辑。若用 CubeMX 修改引脚，打开上级 `RES_Vehicle_G0B1_MDK.ioc`，保持 `KeepUserCode=true`，生成后复核本项目中的 RES 文件分组和共享 include path。

本项目使用 ARMCC 5/C99，调试器应为 SWD。必须先在假负载条件下验证继电器复位释放、无线 STOP、CAN 150 ms 超时和独立硬件锁存，再接入任何实际安全回路。
