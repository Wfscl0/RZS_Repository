# 四灯修订候选构建记录

日期：2026-09-11。移动端源码已修改；本文件记录生成结果，不代表已烧录或完成硬件验收。

部署更新：2026-09-11 已通过 J-Link 写入本批次移动端映像，verifybin 及独立读回 SHA-256 校验通过，运行四灯 GPIO 采样通过；电量通信错误及急停输入故障仍存在，未完成整机验收。见 [烧录与运行验证](FLASH_VERIFY_20260911.md)。车载端未烧录。

- ARM 工具链：GNU Arm Embedded 10.3，沿用 STM32CubeMX 工程及 Keil 目录结构；本轮未执行 Keil 编译。
- 主机工具链：MinGW-w64 GCC 8.1，C99、Wall/Wextra/Werror/pedantic；完整 CMake 构建成功。
- CTest：6/6 通过，含协议、移动端状态机、四灯判据、两端内存链路集成、INA226 诊断、车载状态机。
- STM8 桥接源码通过主机桩语法编译；本轮没有生成或烧录 STM8 新映像。
- ARM 移动端及车载端构建成功。车载端执行逻辑未在本轮修改，不应为了文件日期统一而无条件重刷车辆。
- 旧 artifacts 映像和旧 build-gcc-live 保留。严禁将“生成候选”当作“接线、电量、无线、CAN 故障已排除”。
- 旧 GCC 6.3 的 Windows 串口夹具编译缺少 GetTickCount64 声明；改用现有 GCC 8.1 完成全部构建，未改变夹具源码来规避问题。

| 文件（相对本目录） | 字节 | SHA-256 |
|---|---:|---|
| remote/gcc/RES_Remote_G0B1.bin | 21180 | DFE10FE4358E27776A3927332B5D77730B4C05DED54218913D6E2AE598A82DA9 |
| remote/gcc/RES_Remote_G0B1.elf | 1317924 | 0BBBB77C6844626D9DBA924C2E2A3B18E547F6B4682D70CF32F55759854660C8 |
| remote/gcc/RES_Remote_G0B1.hex | 59662 | BF0B7B0A003B7D9A8998479AD19F630BAFFAD203730A0DB8DD4219823174AA0E |
| vehicle/gcc/RES_Vehicle_G0B1.bin | 17980 | 9189872BBAB9C67F8C1603245C81FA34B4431C37C2EB251C2CEBEC04AC1696C5 |
| vehicle/gcc/RES_Vehicle_G0B1.elf | 1269048 | 6A87C4E01E78AF466C57C271CF2768AE84BD869F34158AA043E5AD8778260CDC |
| vehicle/gcc/RES_Vehicle_G0B1.hex | 50662 | 3450484EE9A4C9585E1DE5829323933565D3EB0A9FF986D04207A062CD93FC8C |

详细修改及台架验收见 ../../docs/FOUR_LAMP_CHANGE_20260911.md。

烧录前最终修正：初始化显式写入 `res_firmware_revision`，确保诊断版本标记不被链接器当作未引用数据移除；以上哈希为最终重建结果，控制逻辑未因此变化。
