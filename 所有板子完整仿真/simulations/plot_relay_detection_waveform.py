from pathlib import Path
import re
import struct

import numpy as np
from PIL import Image, ImageDraw, ImageFont


ROOT = Path(__file__).resolve().parent
RAW_PATH = ROOT / "relay_detection.raw"
OUT_PATH = ROOT / "relay_detection_waveform.png"


def read_ltspice_raw(path: Path):
    raw = path.read_bytes()
    marker = "Binary:\n".encode("utf-16le")
    marker_index = raw.index(marker)
    data_start = marker_index + len(marker)
    header = raw[:data_start].decode("utf-16le", errors="replace")

    nvars = int(re.search(r"No\. Variables:\s+(\d+)", header).group(1))
    npoints = int(re.search(r"No\. Points:\s+(\d+)", header).group(1))
    variables = []
    for line in header.splitlines():
        match = re.match(r"\s*(\d+)\s+(.+?)\s+\S+\s*$", line)
        if match and int(match.group(1)) < nvars:
            variables.append(match.group(2))

    record_size = 8 + 4 * (nvars - 1)
    expected = npoints * record_size
    data = raw[data_start:data_start + expected]
    if len(data) != expected:
        raise ValueError(f"Unexpected raw data size: {len(data)} != {expected}")

    times = np.empty(npoints, dtype=np.float64)
    values = np.empty((npoints, nvars - 1), dtype=np.float32)
    offset = 0
    for idx in range(npoints):
        times[idx] = struct.unpack_from("<d", data, offset)[0]
        offset += 8
        values[idx, :] = np.frombuffer(data, dtype="<f4", count=nvars - 1, offset=offset)
        offset += 4 * (nvars - 1)
    series = {variables[i + 1]: values[:, i].astype(float) for i in range(nvars - 1)}
    return times, series


def draw_polyline(draw, points, color, width=3):
    if len(points) >= 2:
        draw.line(points, fill=color, width=width, joint="curve")


times, series = read_ltspice_raw(RAW_PATH)
t_ms = times * 1000

signals = [
    ("V(ctrl) 接点控制", "V(ctrl)", (90, 90, 90)),
    ("V(sense) 检测节点", "V(sense)", (31, 119, 180)),
    ("V(actual) *_ACTUAL", "V(actual)", (34, 139, 34)),
    ("V(hash) *#", "V(hash)", (214, 39, 40)),
]

width, height = 1500, 980
# Reserve a right-side legend panel so the legend does not cover waveforms.
left, right, top, bottom = 115, 390, 90, 190
plot_w = width - left - right
plot_h = height - top - bottom
xmin, xmax = 0.0, 80.0
ymin, ymax = -0.2, 5.4

img = Image.new("RGB", (width, height), "white")
draw = ImageDraw.Draw(img)

font_path = "C:/Windows/Fonts/NotoSansSC-VF.ttf"
if not Path(font_path).exists():
    font_path = "C:/Windows/Fonts/msyh.ttc"
try:
    font_title = ImageFont.truetype(font_path, 34)
    font = ImageFont.truetype(font_path, 22)
    font_small = ImageFont.truetype(font_path, 18)
except OSError:
    font_title = ImageFont.load_default()
    font = ImageFont.load_default()
    font_small = ImageFont.load_default()


def xp(x):
    return left + int((x - xmin) / (xmax - xmin) * plot_w)


def yp(y):
    return top + int((ymax - y) / (ymax - ymin) * plot_h)


# Background regions: contact closed and open.
draw.rectangle([xp(0), top, xp(4.0), top + plot_h], fill=(246, 250, 255))
draw.rectangle([xp(4.01), top, xp(80), top + plot_h], fill=(255, 250, 245))

# Grid and axes.
for x in range(0, 81, 10):
    px = xp(x)
    draw.line([px, top, px, top + plot_h], fill=(225, 225, 225), width=1)
    draw.text((px - 12, top + plot_h + 12), str(x), fill=(50, 50, 50), font=font_small)
for y in range(0, 6):
    py = yp(y)
    draw.line([left, py, left + plot_w, py], fill=(225, 225, 225), width=1)
    draw.text((45, py - 10), f"{y} V", fill=(50, 50, 50), font=font_small)
draw.rectangle([left, top, left + plot_w, top + plot_h], outline=(40, 40, 40), width=2)

# State boundary and measurement markers.
for x, label in [(4.0, "4 ms: 接点打开"), (2.0, "2 ms 测闭合"), (50.0, "50 ms 测断开")]:
    px = xp(x)
    color = (120, 120, 120) if x == 4.0 else (80, 80, 160)
    draw.line([px, top, px, top + plot_h], fill=color, width=2)
    draw.text((px + 6, top + 8), label, fill=color, font=font_small)

# Waveforms.
for label, key, color in signals:
    y = np.clip(series[key], ymin, ymax)
    points = [(xp(float(x)), yp(float(v))) for x, v in zip(t_ms, y) if xmin <= x <= xmax]
    draw_polyline(draw, points, color, width=3)

# Legend.
legend_x, legend_y = left + plot_w + 35, 115
draw.rectangle([legend_x - 18, legend_y - 18, width - 35, legend_y + 145], fill=(255, 255, 255), outline=(180, 180, 180))
for idx, (label, _key, color) in enumerate(signals):
    y = legend_y + idx * 34
    draw.line([legend_x, y, legend_x + 45, y], fill=color, width=5)
    draw.text((legend_x + 58, y - 12), label, fill=(35, 35, 35), font=font_small)

# Measurement text.
measure_lines = [
    "闭合测量 2 ms: sense=4.733 V, ACTUAL=5.000 V, #=0 V",
    "断开测量 50 ms: sense=0.019 V, ACTUAL=0 V, #=5.000 V",
]
box_y = height - 92
draw.rectangle([left, box_y - 12, left + plot_w, height - 25], fill=(250, 250, 250), outline=(210, 210, 210))
for idx, text in enumerate(measure_lines):
    draw.text((left + 18, box_y + idx * 26), text, fill=(35, 35, 35), font=font_small)

# Labels.
draw.text((left, 28), "继电器检测板 LTspice 瞬态仿真波形", fill=(20, 20, 20), font=font_title)
draw.text((left + plot_w // 2 - 45, top + plot_h + 45), "时间 / ms", fill=(35, 35, 35), font=font)
draw.text((18, top + 260), "电压 / V", fill=(35, 35, 35), font=font)
draw.text((xp(0.6), top + 42), "接点闭合", fill=(60, 90, 130), font=font)
draw.text((xp(10), top + 42), "接点断开，RC 节点放电", fill=(130, 80, 60), font=font)

img.save(OUT_PATH)
print(OUT_PATH)
