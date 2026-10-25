# RES 遥控急停系统

校订日期：2026-10-16。当前系统为STM32G0B1双端与S017 Si4463 SPI无线模块。旧F103/SX127x与E220工程只适用于对应历史硬件。

## 当前入口

- [双端系统说明](firmware/docs/RES_SYSTEM_DESCRIPTION_CN.md)
- [现用接口汇总](Documentation/RES_Controller_接口汇总.md)
- [VCU集成契约](firmware/docs/VCU_INTEGRATION.md)
- [CAN DBC](firmware/dbc/RES_CAN_Validation.dbc)
- [车载端硬件分配](firmware/vehicle_g0b1/Docs/HARDWARE_ALLOCATION_CN.md)
- [遥控端硬件分配](firmware/remote_g0b1/Docs/HARDWARE_ALLOCATION_CN.md)
- [固件工作区](firmware/README.md)
- [正常CAN固件恢复及隔离台架记录](firmware/docs/BENCH_NO_CAN_20260924.md)
- [整车板卡网表](../网表/README.md)

现用RES_ERROR由VCU独立输出，健康12 V、故障0 V；先建立有效健康状态再允许TSMS上电。删除两路健康后才开始监测的等待设计，保留实际故障锁存。EBS安全回路经DCDC后12 V，主支路24 V。CAN使用0x510/0x511/0x512，旧0x1E4不能直接复用。

固件候选映像与实物已刷版本应分别核对；本次文档校订不证明当前实板映像。正常CAN版的历史下载记录不替代CAN连接后的READY/GO与整车验收。

## 历史资料

`firmware/RES_Controller_F103`和旧遥控拓扑网表保留追溯，不能作为当前G0B1/Si4463接线入口。`Documentation/Legacy`内旧说明书不作为现用功能定义。RES两路触点拓扑仍须最终整车原理图统一。
