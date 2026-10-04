from pathlib import Path

import matplotlib.pyplot as plt
from matplotlib import font_manager
from matplotlib.patches import FancyArrowPatch, FancyBboxPatch, Rectangle


OUT = Path(__file__).resolve().parent
FONT_REGULAR = r"C:\Windows\Fonts\msyh.ttc"
FONT_BOLD = r"C:\Windows\Fonts\msyhbd.ttc"
font_manager.fontManager.addfont(FONT_REGULAR)
font_manager.fontManager.addfont(FONT_BOLD)
FONT = font_manager.FontProperties(fname=FONT_REGULAR)
FONT_B = font_manager.FontProperties(fname=FONT_BOLD)

COLORS = {
    "ink": "#172033",
    "muted": "#5D6878",
    "line": "#AAB4C3",
    "lane_a": "#F4F7FB",
    "lane_b": "#FAFBFD",
    "normal_fill": "#EAF3FF",
    "normal_edge": "#2A6FDB",
    "radio_fill": "#F0ECFF",
    "radio_edge": "#7254C7",
    "can_fill": "#FFF4DF",
    "can_edge": "#C77B16",
    "safe_fill": "#E8F7EF",
    "safe_edge": "#238457",
    "fault_fill": "#FDEBEC",
    "fault_edge": "#C73E4D",
    "recover_fill": "#F1F3F6",
    "recover_edge": "#687386",
    "white": "#FFFFFF",
}


def box(ax, x, y, w, h, text, fill, edge, fontsize=8.8, linewidth=1.45):
    patch = FancyBboxPatch(
        (x, y), w, h,
        boxstyle="round,pad=0.25,rounding_size=0.9",
        facecolor=fill,
        edgecolor=edge,
        linewidth=linewidth,
        zorder=3,
    )
    ax.add_patch(patch)
    ax.text(
        x + w / 2, y + h / 2, text,
        ha="center", va="center",
        color=COLORS["ink"],
        fontproperties=FONT,
        fontsize=fontsize,
        linespacing=1.28,
        zorder=4,
    )
    return patch


def arrow(ax, p1, p2, color, width=1.8, style="-", rad=0.0, zorder=2):
    a = FancyArrowPatch(
        p1, p2,
        arrowstyle="-|>",
        mutation_scale=11,
        linewidth=width,
        linestyle=style,
        color=color,
        connectionstyle=f"arc3,rad={rad}",
        shrinkA=2,
        shrinkB=2,
        zorder=zorder,
    )
    ax.add_patch(a)
    return a


fig, ax = plt.subplots(figsize=(16, 10), dpi=220)
fig.patch.set_facecolor("white")
ax.set_xlim(0, 100)
ax.set_ylim(0, 82)
ax.axis("off")

ax.text(
    50, 79.4, "自研遥控急停系统（RES）工作流程",
    ha="center", va="center",
    color=COLORS["ink"],
    fontproperties=FONT_B,
    fontsize=18,
)
ax.text(
    50, 76.6,
    "正常启动链路、GO事件、急停/失联保护与故障恢复",
    ha="center", va="center",
    color=COLORS["muted"],
    fontproperties=FONT,
    fontsize=10,
)

lanes = [
    (0.8, 21.0, "遥控端", "按钮 · INA226 · STM32G0B1"),
    (21.0, 42.0, "无线链路", "E220/STM8 · LLCC68"),
    (42.0, 63.0, "赛车端", "E220 · STM32G0B1 · 继电器"),
    (63.0, 82.0, "VCU", "CAN监督 · AS Ready判断"),
    (82.0, 99.2, "锁存与安全回路", "独立硬件锁存板"),
]

for i, (x0, x1, title, subtitle) in enumerate(lanes):
    ax.add_patch(Rectangle(
        (x0, 5.0), x1 - x0, 69.5,
        facecolor=COLORS["lane_a"] if i % 2 == 0 else COLORS["lane_b"],
        edgecolor=COLORS["line"],
        linewidth=0.8,
        zorder=0,
    ))
    ax.add_patch(Rectangle(
        (x0, 70.2), x1 - x0, 4.3,
        facecolor=COLORS["ink"],
        edgecolor=COLORS["ink"],
        linewidth=0.8,
        zorder=1,
    ))
    ax.text((x0 + x1) / 2, 72.9, title, ha="center", va="center",
            color=COLORS["white"], fontproperties=FONT_B, fontsize=11)
    ax.text((x0 + x1) / 2, 71.2, subtitle, ha="center", va="center",
            color="#DDE5F0", fontproperties=FONT, fontsize=7.4)

row_labels = [
    (51.6, "② 建立认证链路"),
    (37.8, "③ 启动（GO）"),
    (21.8, "④ 急停/失效保护"),
    (8.0, "⑤ 故障排除与恢复"),
]
ax.text(
    1.7, 69.75, "① 上电与安全初始化",
    ha="left", va="top",
    color=COLORS["muted"], fontproperties=FONT_B, fontsize=7.3, zorder=5,
    bbox=dict(facecolor="white", edgecolor="none", pad=0.8, alpha=0.96),
)
for y, label in row_labels:
    ax.text(1.7, y + 5.4, label, ha="left", va="bottom",
            color=COLORS["muted"], fontproperties=FONT_B, fontsize=8.2, zorder=5)

# Box geometry shared by each lane.
xs = [2.6, 23.2, 44.2, 65.0, 83.5]
ws = [16.6, 16.6, 16.6, 15.0, 13.7]
h = 8.2

# Row 1: power-up.
b10 = box(ax, xs[0], 61.2, ws[0], h, "遥控端上电\nGPIO置安全态\nSTOP与INA226自检",
          COLORS["normal_fill"], COLORS["normal_edge"])
b11 = box(ax, xs[1], 61.2, ws[1], h, "E220/STM8上电\n串口与射频初始化\n等待完整协议帧",
          COLORS["radio_fill"], COLORS["radio_edge"])
b12 = box(ax, xs[2], 61.2, ws[2], h, "赛车端上电\nR1闭合、R2断开\n进入 WAIT_LINK",
          COLORS["normal_fill"], COLORS["normal_edge"])
b13 = box(ax, xs[3], 61.2, ws[3], h, "VCU上电\nCAN监督任务启动\nRES_ERROR默认有效",
          COLORS["can_fill"], COLORS["can_edge"])
b14 = box(ax, xs[4], 61.2, ws[4], h, "硬件锁存板\n保持安全状态\n安全回路不得误闭合",
          COLORS["safe_fill"], COLORS["safe_edge"], fontsize=8.3)

# Row 2: link.
b20 = box(ax, xs[0], 47.5, ws[0], h, "自检通过\n发送 HELLO / READY\n等待鉴权ACK",
          COLORS["normal_fill"], COLORS["normal_edge"])
b21 = box(ax, xs[1], 47.5, ws[1], h, "双向认证传输\nCRC16 + SipHash\n会话/序号/ACK/重放保护",
          COLORS["radio_fill"], COLORS["radio_edge"], fontsize=8.4)
b22 = box(ax, xs[2], 47.5, ws[2], h, "连续3帧有效 READY\nR1、R2均闭合\n状态进入 READY",
          COLORS["normal_fill"], COLORS["normal_edge"])
b23 = box(ax, xs[3], 47.5, ws[3], h, "接收 0x510（50 ms）\n检查版本、状态、flags\n150 ms独立超时监督",
          COLORS["can_fill"], COLORS["can_edge"], fontsize=8.25)
b24 = box(ax, xs[4], 47.5, ws[4], h, "RES_ERROR无效\n整车安全条件成立\n允许进入AS Ready",
          COLORS["safe_fill"], COLORS["safe_edge"], fontsize=8.3)

# Row 3: GO.
b30 = box(ax, xs[0], 33.7, ws[0], h, "操作员按下GO\n25 ms按键防抖\n仅有效链路允许发送",
          COLORS["normal_fill"], COLORS["normal_edge"])
b31 = box(ax, xs[1], 33.7, ws[1], h, "发送鉴权GO并等待ACK\n会话号 + 命令计数\n防止重发造成重复启动",
          COLORS["radio_fill"], COLORS["radio_edge"], fontsize=8.25)
b32 = box(ax, xs[2], 33.7, ws[2], h, "识别新的GO事件\n两继电器保持闭合\nSTART_OUT输出100 ms",
          COLORS["normal_fill"], COLORS["normal_edge"])
b33 = box(ax, xs[3], 33.7, ws[3], h, "接收0x511事件\n同时验证新鲜0x510\n检查全部AS Ready条件",
          COLORS["can_fill"], COLORS["can_edge"], fontsize=8.25)
b34 = box(ax, xs[4], 33.7, ws[4], h, "允许启动/继续运行\nGO不旁路安全条件\n0x511仅作为事件",
          COLORS["safe_fill"], COLORS["safe_edge"], fontsize=8.2)

# Row 4: fail-safe.
b40 = box(ax, xs[0], 16.9, ws[0], 10.0, "急停、NC线断开或检测掉电\n严重低电量/检测故障\n立即进入STOP锁存",
          COLORS["fault_fill"], COLORS["fault_edge"], fontsize=8.4, linewidth=1.7)
b41 = box(ax, xs[1], 16.9, ws[1], 10.0, "STOP关键帧重复发送\n三信道物理跳频设计\n或无线链路中断",
          COLORS["fault_fill"], COLORS["fault_edge"], fontsize=8.4, linewidth=1.7)
b42 = box(ax, xs[2], 16.9, ws[2], 10.0, "收到STOP或500 ms失联\nR1、R2立即断开\nFAULT_OUT + 0x510故障",
          COLORS["fault_fill"], COLORS["fault_edge"], fontsize=8.25, linewidth=1.7)
b43 = box(ax, xs[3], 16.9, ws[3], 10.0, "0x510故障/状态异常\n或150 ms CAN超时\n输出硬件RES_ERROR",
          COLORS["fault_fill"], COLORS["fault_edge"], fontsize=8.2, linewidth=1.7)
b44 = box(ax, xs[4], 16.9, ws[4], 10.0, "锁存RES_ERROR\n切断并保持安全回路\n故障不得自动清除",
          COLORS["fault_fill"], COLORS["fault_edge"], fontsize=8.2, linewidth=1.7)

# Row 5: recovery.
b50 = box(ax, xs[0], 5.7, ws[0], 7.1, "排除故障并释放急停\n遥控器断电重启，产生新会话",
          COLORS["recover_fill"], COLORS["recover_edge"], fontsize=8.15)
b51 = box(ax, xs[1], 5.7, ws[1], 7.1, "重新建立鉴权链路\n不得沿用旧会话解除锁存",
          COLORS["recover_fill"], COLORS["recover_edge"], fontsize=8.15)
b52 = box(ax, xs[2], 5.7, ws[2], 7.1, "新会话连续3帧READY\n且无赛车端本地故障",
          COLORS["recover_fill"], COLORS["recover_edge"], fontsize=8.15)
b53 = box(ax, xs[3], 5.7, ws[3], 7.1, "VCU按整车复位流程\n重新确认全部安全条件",
          COLORS["recover_fill"], COLORS["recover_edge"], fontsize=8.1)
b54 = box(ax, xs[4], 5.7, ws[4], 7.1, "人工复位/重新上电\n确认后才允许恢复",
          COLORS["recover_fill"], COLORS["recover_edge"], fontsize=8.0)

# Horizontal stage interactions.
for y, color, width, style in [
    (65.3, COLORS["normal_edge"], 1.65, "-"),
    (51.6, COLORS["normal_edge"], 1.85, "-"),
    (37.8, COLORS["normal_edge"], 1.85, "-"),
    (21.9, COLORS["fault_edge"], 2.05, "-"),
    (9.25, COLORS["recover_edge"], 1.55, "--"),
]:
    for i in range(4):
        arrow(ax, (xs[i] + ws[i], y), (xs[i + 1], y), color, width=width, style=style)

# Vertical progress within lanes: startup -> link -> GO.
for i in range(5):
    xmid = xs[i] + ws[i] / 2
    arrow(ax, (xmid, 61.2), (xmid, 55.7), COLORS["normal_edge"], width=1.35)
    arrow(ax, (xmid, 47.5), (xmid, 41.9), COLORS["normal_edge"], width=1.35)

# Fail-safe branches. These are deliberately red and stronger than the normal path.
arrow(ax, (xs[0] + 3.0, 47.5), (xs[0] + 3.0, 26.9), COLORS["fault_edge"], width=2.0)
ax.text(xs[0] + 3.8, 30.2, "自检失败/急停", ha="left", va="center",
        color=COLORS["fault_edge"], fontproperties=FONT_B, fontsize=7.4)
arrow(ax, (xs[1] + ws[1] - 2.6, 47.5), (xs[1] + ws[1] - 2.6, 26.9),
      COLORS["fault_edge"], width=2.0)
ax.text(xs[1] + ws[1] - 3.3, 30.2, "失联", ha="right", va="center",
        color=COLORS["fault_edge"], fontproperties=FONT_B, fontsize=7.4)
arrow(ax, (xs[3] + ws[3] - 2.5, 47.5), (xs[3] + ws[3] - 2.5, 26.9),
      COLORS["fault_edge"], width=2.0)
ax.text(xs[3] + ws[3] - 3.2, 30.2, "监督异常", ha="right", va="center",
        color=COLORS["fault_edge"], fontproperties=FONT_B, fontsize=7.4)

# Recovery returns to authenticated-link stage only after the entire chain is reset.
arrow(ax, (xs[4] + ws[4] - 1.2, 12.8), (xs[4] + ws[4] - 1.2, 47.5),
      COLORS["recover_edge"], width=1.55, style="--", rad=0.12, zorder=1)
ax.text(98.0, 31.4, "确认后返回\n链路建立阶段", ha="right", va="center",
        color=COLORS["recover_edge"], fontproperties=FONT, fontsize=7.1)

# Compact legend and engineering note.
legend_y = 2.0
ax.plot([2.5, 5.0], [legend_y, legend_y], color=COLORS["normal_edge"], linewidth=2.0)
ax.text(5.5, legend_y, "正常/控制路径", va="center", color=COLORS["ink"],
        fontproperties=FONT, fontsize=7.8)
ax.plot([16.0, 18.5], [legend_y, legend_y], color=COLORS["fault_edge"], linewidth=2.2)
ax.text(19.0, legend_y, "急停与失效保护路径", va="center", color=COLORS["ink"],
        fontproperties=FONT, fontsize=7.8)
ax.plot([33.3, 35.8], [legend_y, legend_y], color=COLORS["recover_edge"],
        linewidth=1.7, linestyle="--")
ax.text(36.3, legend_y, "人工确认后的恢复路径", va="center", color=COLORS["ink"],
        fontproperties=FONT, fontsize=7.8)
ax.text(
    98.2, legend_y,
    "设计注：最终物理跳频需双端烧录自定义STM8桥；原厂桥台架结果不等同于跳频实测。",
    ha="right", va="center", color=COLORS["muted"],
    fontproperties=FONT, fontsize=7.5,
)

plt.subplots_adjust(left=0.012, right=0.988, top=0.982, bottom=0.02)
fig.savefig(OUT / "RES_WORKFLOW_CN.svg", facecolor="white", bbox_inches="tight", pad_inches=0.08)
fig.savefig(OUT / "RES_WORKFLOW_CN.png", facecolor="white", bbox_inches="tight", pad_inches=0.08, dpi=220)
plt.close(fig)
