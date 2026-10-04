# 网表索引

整车板卡网表统一从本目录读取，路径以仓库根目录为基准为 `./网表/`。

| 文件 | 板卡 |
|---|---|
| base.tel | 基板 |
| bspd.tel | BSPD |
| ebs.tel | EBS |
| lock.tel | 错误锁存 |
| relay.tel | 继电器检测 |
| tsal.tel | TSAL 控制 |
| tsal_light.tel | TSAL 灯板 |

2026-10-04 方案：删除 EBS/RES“两路都输出 1 后才开始监测”的上电等待设计；TSMS 上电前先给 `RES_ERROR` 12 V；EBS 安全回路经 DCDC 降为 12 V。实际故障锁存保留，见 [错误锁存说明](../错误锁存/说明.txt)和 [EBS 说明](../EBS/EBS说明.md)。

`ebs.tel` 中 RLY2 为 12 V 线圈，RLY1 与 EBS 主电源仍为 24 V。旧仿真和台架记录只证明当时版本，不直接证明本次上电顺序和外部 DCDC 接线。

RES 目录内尚存旧遥控端网表导出，本目录目前未收录对应 RES 网表；旧导出仅供历史参考。
