# EBS 电路说明

版本：2026-10-04。连接依据：[EBS 网表](../网表/ebs.tel)。

EBS 主电源 `EBS_PWR` 为 24 V，板内 LM2596S-5.0 生成 5 V。VCU 看门狗信号和 `EBS_TRIG` 控制 RLY1。安全回路经 DCDC 降为 12 V 后送入 `SDC_IN`，驱动 12 V 线圈的 RLY2。安全回路降压不改变 EBS 主电源电压。

```text
24 V 主电源 → EBS_PWR → RLY1（24 V 线圈）→ EBS_WORK
安全回路 → DCDC（12 V 输出）→ SDC_IN → RLY2（12 V 线圈）
```

| 连接器 | 针脚 | 网络 | 说明 |
|---|---:|---|---|
| H1 | 1 | VCU_WDI | VCU 看门狗翻转信号，5 V 逻辑域 |
| H1 | 2 | EBS_TRIG | 高有效触发，直接进入板内 5 V 逻辑；外部电平需匹配 |
| H1 | 3 | EBS_CHECK | 继电器检查输出，幅值随触点状态测量 |
| H2 | 1 | SDC_IN | 安全回路经 DCDC 后的 12 V 输入 |
| H2 | 2 | EBS_WORK | 主电源触点输出，正常约 24 V，释放时失电 |
| H2 | 3 | AS_LOCK | EBS_WORK 经 22 kΩ/4.7 kΩ 分压，24 V 时约 4.23 V |
| H2 | 4 | VCU_FB | 继电器状态反馈；电平与极性按触点组合核对 |
| H3 | 1 | EBS_PWR | 24 V 主电源 |
| H3 | 2 | GND | 低压地 |

删除 EBS/RES“两路都输出 1 才开始监测”的上电等待设计。改为在 TSMS 上电前先给 `RES_ERROR` 12 V；实际故障锁存和 `R_E_RESET` 仍按 [错误锁存板说明](../错误锁存/说明.txt)执行。

本次只更新文字。`ebs.tel` 已列出 RLY2 为 SRD-12VDC-SL-C；外部 DCDC 接线和上电顺序需在全车图纸及实物中核对。验证时测量 DCDC 输出、SDC_IN、两只继电器触点与 EBS_WORK，分别检查安全回路断开和主电源掉电后的制动动作。
