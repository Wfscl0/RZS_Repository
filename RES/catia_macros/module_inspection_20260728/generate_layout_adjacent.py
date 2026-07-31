import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle, Circle, Arc

fig, ax = plt.subplots(figsize=(13, 10))
ax.set_aspect("equal")

# 168 x 130 mm FR-4 insulation plate.
ax.add_patch(Rectangle((-84, -65), 168, 130, fill=False, lw=3, ec="black"))
for x in (-84, 76):
    for y in (-42, 22):
        ax.add_patch(Rectangle((x, y), 8, 20, fc="white", ec="black", lw=1.5))

modules = [
    ("Relay_4", -69, 7.5, 75, 55, "#df7773"),
    ("Relay_2", -37.5, -33.5, 41, 33, "#f2aa55"),
    ("INA226", -74, -33.5, 20, 27, "#88bf82"),
    ("DCDC", -69.75, -62.9, 59.5, 25.8, "#9b83b7"),
    ("STM32", 13.5, 25.17, 26.67, 36.83, "#72c0b6"),
    ("LoRa", 43.37, 9, 28, 53, "#609ed1"),
]

for name, x, y, w, h, color in modules:
    ax.add_patch(Rectangle((x, y), w, h, fc=color, ec="#222", lw=1.6, alpha=0.92))
    ax.text(x + w / 2, y + h / 2, name, ha="center", va="center", fontsize=13, weight="bold")

# LoRa + STM32 carrier PCB, 62 x 57 mm. The right edge has a shallow open notch
# around the top-right insulation-plate mounting screw.
ax.add_patch(Rectangle((12, 7), 62, 57, fill=False, ec="#005bbb", lw=2.5, ls="--"))
ax.add_patch(Arc((78, 59), 9.6, 9.6, theta1=90, theta2=270, ec="#005bbb", lw=2.5))
ax.text(43, 66.5, "62 x 57 mm LoRa/STM32 carrier PCB", ha="center", color="#005bbb", fontsize=11)

# Four VD isolator positions.
for x in (-78, 78):
    for y in (-59, 59):
        ax.add_patch(Circle((x, y), 5, fc="#555", ec="#111", lw=1.2))
        ax.text(x, y, "VD", ha="center", va="center", color="white", fontsize=8)

# Mandatory E-stop keep-out remains unchanged.
ax.add_patch(Rectangle((11, -38), 42, 42, fc="#ffd5d5", ec="#bd1717", lw=2, hatch="//"))
ax.text(32, -17, "E-STOP\nKEEP-OUT", ha="center", va="center", color="#9d0000", fontsize=11, weight="bold")

# Panel component projections.
for x in (-39, -13, 13, 39):
    ax.add_patch(Circle((x, 22), 8.2, fill=False, ec="#555", lw=1.3, ls=":"))
ax.add_patch(Circle((-48, -17), 11, fill=False, ec="#555", lw=1.3, ls=":"))

# RF orientation and primary wiring channels.
ax.annotate("LoRa RF/SMA end toward +Y front wall", xy=(57.4, 61), xytext=(44, 72),
            arrowprops=dict(arrowstyle="->", lw=1.5), ha="center", fontsize=10)
ax.annotate("short SPI/UART/power routing", xy=(41.8, 43), xytext=(40, 4),
            arrowprops=dict(arrowstyle="<->", lw=1.5, color="#005bbb"),
            ha="center", color="#005bbb", fontsize=10)

ax.set_xlim(-92, 92)
ax.set_ylim(-73, 78)
ax.set_xlabel("X / mm")
ax.set_ylabel("Y / mm")
ax.set_title("RES module layout - adjacent LoRa and STM32 carrier PCB", fontsize=17)
ax.grid(alpha=0.18)
ax.text(-90, -70,
        "Dotted circles: panel-component projection (verify depth)   |   Hatched: mandatory E-stop keep-out",
        fontsize=9)
plt.tight_layout()
plt.savefig("MODULE_LAYOUT_168x130.png", dpi=180, bbox_inches="tight")
