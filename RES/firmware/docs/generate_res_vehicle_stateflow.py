from pathlib import Path

import matplotlib.pyplot as plt
from matplotlib import font_manager
from matplotlib.patches import FancyArrowPatch, FancyBboxPatch


OUT = Path(__file__).resolve().parent
FONT_REGULAR = r"C:\Windows\Fonts\msyh.ttc"
FONT_BOLD = r"C:\Windows\Fonts\msyhbd.ttc"
font_manager.fontManager.addfont(FONT_REGULAR)
font_manager.fontManager.addfont(FONT_BOLD)
FONT = font_manager.FontProperties(fname=FONT_REGULAR)
FONT_B = font_manager.FontProperties(fname=FONT_BOLD)

C = {
    "ink": "#172033",
    "muted": "#5D6878",
    "blue": "#2869D8",
    "blue_fill": "#EAF3FF",
    "purple": "#7254C7",
    "purple_fill": "#F1EDFF",
    "orange": "#B96B0D",
    "orange_fill": "#FFF3DF",
    "red": "#C73E4D",
    "red_fill": "#FDEBEC",
    "green": "#238457",
    "green_fill": "#E8F7EF",
    "gray": "#687386",
    "gray_fill": "#F1F3F6",
    "line": "#AAB4C3",
    "white": "#FFFFFF",
}


def node(ax, x, y, w, h, title, lines, fill, edge, title_size=11.0, text_size=8.4):
    patch = FancyBboxPatch(
        (x, y), w, h,
        boxstyle="round,pad=0.25,rounding_size=0.9",
        facecolor=fill, edgecolor=edge, linewidth=1.8, zorder=3,
    )
    ax.add_patch(patch)
    ax.text(x + w / 2, y + h - 2.0, title,
            ha="center", va="center", color=edge,
            fontproperties=FONT_B, fontsize=title_size, zorder=4)
    ax.text(x + w / 2, y + h / 2 - 1.2, lines,
            ha="center", va="center", color=C["ink"],
            fontproperties=FONT, fontsize=text_size,
            linespacing=1.32, zorder=4)
    return patch


def small_node(ax, x, y, w, h, text, fill, edge, text_size=8.2):
    patch = FancyBboxPatch(
        (x, y), w, h,
        boxstyle="round,pad=0.18,rounding_size=0.65",
        facecolor=fill, edgecolor=edge, linewidth=1.35, zorder=3,
    )
    ax.add_patch(patch)
    ax.text(x + w / 2, y + h / 2, text,
            ha="center", va="center", color=C["ink"],
            fontproperties=FONT, fontsize=text_size,
            linespacing=1.25, zorder=4)
    return patch


def arrow(ax, p1, p2, color, width=1.7, style="-", rad=0.0, zorder=2):
    patch = FancyArrowPatch(
        p1, p2, arrowstyle="-|>", mutation_scale=12,
        linewidth=width, linestyle=style, color=color,
        connectionstyle=f"arc3,rad={rad}",
        shrinkA=2, shrinkB=2, zorder=zorder,
    )
    ax.add_patch(patch)
    return patch


fig, ax = plt.subplots(figsize=(14, 8.5), dpi=220)
fig.patch.set_facecolor("white")
ax.set_xlim(0, 100)
ax.set_ylim(0, 78)
ax.axis("off")

ax.text(50, 75.0, "RES赛车端状态与失效保护链路",
        ha="center", va="center", color=C["ink"],
        fontproperties=FONT_B, fontsize=18)
ax.text(50, 71.8, "仅列出赛车接收端软件状态；硬件锁存由VCU数字输出 RES_Error 驱动",
        ha="center", va="center", color=C["muted"],
        fontproperties=FONT, fontsize=9.5)

# Vehicle receiver software states.
node(ax, 3.0, 52.0, 17.0, 13.0,
     "BOOT（状态0）",
     "GPIO保持复位安全态\n初始化UART、CAN与看门狗\nR1断开，R2断开",
     C["gray_fill"], C["gray"])
node(ax, 25.0, 52.0, 19.0, 13.0,
     "WAIT_LINK（状态1）",
     "等待有效的新鉴权会话\nR1闭合，R2断开\n周期发送0x510（50 ms）",
     C["blue_fill"], C["blue"])
node(ax, 50.0, 52.0, 19.0, 13.0,
     "READY（状态2）",
     "连续3帧有效READY\nR1、R2均闭合\n链路有效，允许接收GO",
     C["green_fill"], C["green"])
node(ax, 75.0, 52.0, 20.0, 13.0,
     "GO_EVENT（状态3）",
     "收到新的鉴权GO计数\nR1、R2保持闭合\nSTART_OUT=100 ms；发送0x511",
     C["orange_fill"], C["orange"], text_size=8.2)

# Normal transitions.
arrow(ax, (20.0, 58.5), (25.0, 58.5), C["blue"])
ax.text(22.5, 60.0, "初始化完成", ha="center", va="bottom",
        color=C["muted"], fontproperties=FONT, fontsize=7.2)
arrow(ax, (44.0, 58.5), (50.0, 58.5), C["blue"])
ax.text(47.0, 60.1, "新会话 + 3帧READY\n且无本地故障", ha="center", va="bottom",
        color=C["muted"], fontproperties=FONT, fontsize=6.9, linespacing=1.15)
arrow(ax, (69.0, 58.5), (75.0, 58.5), C["orange"])
ax.text(72.0, 60.1, "新GO命令\n鉴权/序号有效", ha="center", va="bottom",
        color=C["muted"], fontproperties=FONT, fontsize=6.9, linespacing=1.15)
arrow(ax, (75.0, 53.2), (69.0, 53.2), C["orange"],
      width=1.55, rad=0.32, zorder=5)
ax.text(72.0, 48.9, "100 ms启动脉冲结束，自动返回READY",
        ha="center", va="center", color=C["orange"],
        fontproperties=FONT, fontsize=7.1)

# Shared fault trigger and fault state.
small_node(ax, 24.0, 37.2, 52.0, 7.2,
           "停止条件：鉴权STOP ｜ 已建立链路后500 ms无有效帧 ｜ 本地CAN/继电器等故障",
           C["red_fill"], C["red"], text_size=8.3)
for x in (34.5, 59.5, 85.0):
    arrow(ax, (x, 52.0), (x if x != 85.0 else 72.0, 44.4), C["red"], width=1.85)

node(ax, 35.0, 20.5, 30.0, 12.0,
     "STOPPED_FAULT（状态4）",
     "R1、R2立即断开，START_OUT撤销\n0x510上报故障状态与flags\n同一会话的READY无效，不得自动恢复",
     C["red_fill"], C["red"], title_size=11.4, text_size=8.5)
arrow(ax, (50.0, 37.2), (50.0, 32.5), C["red"], width=2.1)

# Recovery: a different authenticated boot session is mandatory.
arrow(ax, (35.0, 26.5), (25.0, 52.0), C["gray"], width=1.65, style="--", rad=-0.32)
ax.text(19.8, 35.0,
        "恢复条件\n排除本地故障\n遥控器重新上电形成不同会话\n收到鉴权HELLO后回到WAIT_LINK",
        ha="center", va="center", color=C["gray"],
        fontproperties=FONT, fontsize=7.2, linespacing=1.2,
        bbox=dict(facecolor="white", edgecolor="none", pad=1.0, alpha=0.94))

# External lock path: explicitly not another receiver state.
ax.plot([3.0, 97.0], [16.0, 16.0], color=C["line"], linewidth=0.9)
ax.text(3.2, 17.2, "外部失效保护链（非赛车端软件状态）",
        ha="left", va="bottom", color=C["muted"],
        fontproperties=FONT_B, fontsize=8.2)

small_node(ax, 3.0, 5.3, 20.0, 7.3,
           "赛车端CAN\n0x510状态帧 / 50 ms",
           C["blue_fill"], C["blue"])
small_node(ax, 28.0, 5.3, 22.0, 7.3,
           "VCU固定周期安全监督\n状态/flags异常或150 ms超时",
           C["orange_fill"], C["orange"], text_size=8.0)
small_node(ax, 55.0, 5.3, 17.0, 7.3,
           "VCU数字输出\nRES_Error 有效",
           C["red_fill"], C["red"])
small_node(ax, 77.0, 5.3, 20.0, 7.3,
           "独立硬件锁存电路\n切断并保持安全回路",
           C["red_fill"], C["red"])

arrow(ax, (23.0, 8.95), (28.0, 8.95), C["blue"], width=1.75)
arrow(ax, (50.0, 8.95), (55.0, 8.95), C["red"], width=1.9)
arrow(ax, (72.0, 8.95), (77.0, 8.95), C["red"], width=1.9)

ax.text(50.0, 2.2,
        "VCU上电、CAN总线异常或监督任务异常时，RES_Error默认置为有效；锁存故障不得由赛车端软件自行清除。",
        ha="center", va="center", color=C["muted"],
        fontproperties=FONT, fontsize=7.4)

plt.subplots_adjust(left=0.018, right=0.982, top=0.982, bottom=0.025)
fig.savefig(OUT / "RES_VEHICLE_STATEFLOW_CN.svg", facecolor="white",
            bbox_inches="tight", pad_inches=0.08)
fig.savefig(OUT / "RES_VEHICLE_STATEFLOW_CN.png", facecolor="white",
            bbox_inches="tight", pad_inches=0.08, dpi=220)
