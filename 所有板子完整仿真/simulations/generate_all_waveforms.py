from pathlib import Path
import re
import struct

import numpy as np
from PIL import Image, ImageDraw, ImageFont


ROOT = Path(__file__).resolve().parent
FONT_PATHS = [
    Path("C:/Windows/Fonts/NotoSansSC-VF.ttf"),
    Path("C:/Windows/Fonts/msyh.ttc"),
    Path("C:/Windows/Fonts/simhei.ttf"),
]


def font(size: int):
    for path in FONT_PATHS:
        if path.exists():
            return ImageFont.truetype(str(path), size)
    return ImageFont.load_default()


FONT_TITLE = font(34)
FONT = font(22)
FONT_SMALL = font(18)


def read_ltspice_raw(path: Path):
    raw = path.read_bytes()
    marker = "Binary:\n".encode("utf-16le")
    marker_index = raw.index(marker)
    data_start = marker_index + len(marker)
    header = raw[:data_start].decode("utf-16le", errors="replace")

    nvars = int(re.search(r"No\. Variables:\s+(\d+)", header).group(1))
    npoints = int(re.search(r"No\. Points:\s+(\d+)", header).group(1))
    variables = []
    in_variables = False
    for line in header.splitlines():
        if line.strip() == "Variables:":
            in_variables = True
            continue
        if line.strip() == "Binary:":
            break
        if in_variables:
            match = re.match(r"\s*(\d+)\s+(.+?)\s+\S+\s*$", line)
            if match:
                variables.append(match.group(2))

    record_size = 8 + 4 * (nvars - 1)
    expected = npoints * record_size
    data = raw[data_start:data_start + expected]
    if len(data) != expected:
        raise ValueError(f"{path.name}: unexpected raw data size {len(data)} != {expected}")

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


def draw_waveform(
    raw_name,
    out_name,
    title,
    signals,
    xlim_ms,
    ylim,
    regions,
    markers,
    notes,
):
    times, series = read_ltspice_raw(ROOT / raw_name)
    t_ms = times * 1000

    width, height = 1500, 980
    # Reserve a right-side legend panel so legends never cover waveforms.
    left, right, top, bottom = 115, 390, 92, 190
    plot_w = width - left - right
    plot_h = height - top - bottom
    xmin, xmax = xlim_ms
    ymin, ymax = ylim

    image = Image.new("RGB", (width, height), "white")
    draw = ImageDraw.Draw(image)

    def xp(x):
        return left + int((x - xmin) / (xmax - xmin) * plot_w)

    def yp(y):
        return top + int((ymax - y) / (ymax - ymin) * plot_h)

    for start, end, label, fill, text_color in regions:
        x0, x1 = max(start, xmin), min(end, xmax)
        if x1 <= xmin or x0 >= xmax:
            continue
        draw.rectangle([xp(x0), top, xp(x1), top + plot_h], fill=fill)
        text_w = draw.textlength(label, font=FONT_SMALL)
        label_x = xp(x0) + 10
        if label_x + text_w > left + plot_w - 4:
            label_x = max(left + 4, xp(x1) - int(text_w) - 10)
        draw.text((label_x, top + 42), label, fill=text_color, font=FONT_SMALL)

    # Grid.
    if xmax <= 20:
        xstep = 1
        label_step = 1
    elif xmax <= 100:
        xstep = 10
        label_step = 10
    elif xmax <= 1000:
        xstep = 100
        label_step = 100
    elif xmax <= 5000:
        xstep = 500
        label_step = 500
    else:
        xstep = 1000
        label_step = 1000
    for x in np.arange(np.ceil(xmin / xstep) * xstep, xmax + 0.001, xstep):
        px = xp(float(x))
        draw.line([px, top, px, top + plot_h], fill=(225, 225, 225), width=1)
        if abs((x - xmin) % label_step) < 1e-9:
            draw.text((px - 18, top + plot_h + 12), f"{x:g}", fill=(50, 50, 50), font=FONT_SMALL)

    ystep = 1 if ymax <= 6 else (5 if ymax <= 26 else 10)
    for y in np.arange(np.ceil(ymin / ystep) * ystep, ymax + 0.001, ystep):
        py = yp(float(y))
        draw.line([left, py, left + plot_w, py], fill=(225, 225, 225), width=1)
        draw.text((40, py - 10), f"{y:g} V", fill=(50, 50, 50), font=FONT_SMALL)

    draw.rectangle([left, top, left + plot_w, top + plot_h], outline=(40, 40, 40), width=2)

    for idx, (x, label, color) in enumerate(markers):
        if x < xmin or x > xmax:
            continue
        px = xp(x)
        draw.line([px, top, px, top + plot_h], fill=color, width=2)
        text_w = draw.textlength(label, font=FONT_SMALL)
        label_x = px + 6
        if label_x + text_w > left + plot_w - 4:
            label_x = max(left + 4, px - int(text_w) - 8)
        draw.text((label_x, top + 8 + (idx % 3) * 26), label, fill=color, font=FONT_SMALL)

    for label, key, color, scale in signals:
        y = np.clip(series[key] * scale, ymin, ymax)
        points = [(xp(float(x)), yp(float(v))) for x, v in zip(t_ms, y) if xmin <= x <= xmax]
        if len(points) >= 2:
            draw.line(points, fill=color, width=3, joint="curve")

    legend_x, legend_y = left + plot_w + 35, 118
    legend_h = 28 + len(signals) * 33
    draw.rectangle([legend_x - 18, legend_y - 18, width - 35, legend_y + legend_h], fill=(255, 255, 255), outline=(180, 180, 180))
    for idx, (label, _key, color, scale) in enumerate(signals):
        y = legend_y + idx * 33
        draw.line([legend_x, y, legend_x + 45, y], fill=color, width=5)
        suffix = "" if scale == 1 else f" x{scale:g}"
        draw.text((legend_x + 58, y - 12), label + suffix, fill=(35, 35, 35), font=FONT_SMALL)

    box_y = height - 102
    draw.rectangle([left, box_y - 12, left + plot_w, height - 24], fill=(250, 250, 250), outline=(210, 210, 210))
    for idx, text in enumerate(notes[:3]):
        draw.text((left + 18, box_y + idx * 26), text, fill=(35, 35, 35), font=FONT_SMALL)

    draw.text((left, 28), title, fill=(20, 20, 20), font=FONT_TITLE)
    draw.text((left + plot_w // 2 - 45, top + plot_h + 45), "时间 / ms", fill=(35, 35, 35), font=FONT)
    draw.text((18, top + 260), "电压 / V", fill=(35, 35, 35), font=FONT)

    out_path = ROOT / out_name
    image.save(out_path)
    return out_path


def draw_broken_x_waveform(
    raw_name,
    out_name,
    title,
    signals,
    segments,
    ylim,
    regions,
    markers,
    notes,
):
    times, series = read_ltspice_raw(ROOT / raw_name)
    t_ms = times * 1000

    width, height = 1500, 980
    left, right, top, bottom = 115, 390, 92, 190
    plot_w = width - left - right
    plot_h = height - top - bottom
    gap = 54
    ymin, ymax = ylim

    total_weight = sum(segment[2] for segment in segments)
    usable_w = plot_w - gap * (len(segments) - 1)
    segment_boxes = []
    cursor = left
    for xmin, xmax, weight, tick_step in segments:
        seg_w = int(usable_w * weight / total_weight)
        segment_boxes.append((xmin, xmax, tick_step, cursor, cursor + seg_w))
        cursor += seg_w + gap
    # Give rounding residue to the final segment.
    xmin, xmax, tick_step, seg_left, _seg_right = segment_boxes[-1]
    segment_boxes[-1] = (xmin, xmax, tick_step, seg_left, left + plot_w)

    image = Image.new("RGB", (width, height), "white")
    draw = ImageDraw.Draw(image)

    def segment_for(x):
        for xmin, xmax, tick_step, seg_left, seg_right in segment_boxes:
            if xmin <= x <= xmax:
                return xmin, xmax, tick_step, seg_left, seg_right
        return None

    def xp(x):
        segment = segment_for(x)
        if segment is None:
            return None
        xmin, xmax, _tick_step, seg_left, seg_right = segment
        return seg_left + int((x - xmin) / (xmax - xmin) * (seg_right - seg_left))

    def yp(y):
        return top + int((ymax - y) / (ymax - ymin) * plot_h)

    def tick_label(x):
        if x == 0:
            return "0"
        if x >= 1000:
            return f"{x / 1000:.1f}s"
        return f"{int(x)}ms"

    for start, end, label, fill, text_color in regions:
        for xmin, xmax, _tick_step, seg_left, seg_right in segment_boxes:
            x0, x1 = max(start, xmin), min(end, xmax)
            if x1 <= xmin or x0 >= xmax:
                continue
            px0, px1 = xp(x0), xp(x1)
            draw.rectangle([px0, top, px1, top + plot_h], fill=fill)
            text_w = draw.textlength(label, font=FONT_SMALL)
            if px1 - px0 < text_w + 22:
                continue
            label_x = px0 + 10
            if label_x + text_w > px1 - 4:
                label_x = max(px0 + 4, px1 - int(text_w) - 10)
            draw.text((label_x, top + 42), label, fill=text_color, font=FONT_SMALL)

    for xmin, xmax, tick_step, seg_left, seg_right in segment_boxes:
        x = np.ceil(xmin / tick_step) * tick_step
        while x <= xmax + 0.001:
            px = xp(float(x))
            draw.line([px, top, px, top + plot_h], fill=(225, 225, 225), width=1)
            draw.text((px - 22, top + plot_h + 12), tick_label(float(x)), fill=(50, 50, 50), font=FONT_SMALL)
            x += tick_step

    ystep = 1 if ymax <= 6 else (5 if ymax <= 26 else 10)
    for y in np.arange(np.ceil(ymin / ystep) * ystep, ymax + 0.001, ystep):
        py = yp(float(y))
        draw.line([left, py, left + plot_w, py], fill=(225, 225, 225), width=1)
        draw.text((40, py - 10), f"{y:g} V", fill=(50, 50, 50), font=FONT_SMALL)

    for _xmin, _xmax, _tick_step, seg_left, seg_right in segment_boxes:
        draw.rectangle([seg_left, top, seg_right, top + plot_h], outline=(40, 40, 40), width=2)

    for (_a, _b, _t, _l0, r0), (_c, _d, _u, l1, _r1) in zip(segment_boxes, segment_boxes[1:]):
        bx = (r0 + l1) // 2
        for yy in (top, top + plot_h):
            draw.line([bx - 14, yy + 10, bx - 4, yy - 10], fill=(80, 80, 80), width=2)
            draw.line([bx + 4, yy + 10, bx + 14, yy - 10], fill=(80, 80, 80), width=2)

    for idx, (x, label, color) in enumerate(markers):
        px = xp(x)
        if px is None:
            continue
        segment = segment_for(x)
        _xmin, _xmax, _tick_step, seg_left, seg_right = segment
        draw.line([px, top, px, top + plot_h], fill=color, width=2)
        text_w = draw.textlength(label, font=FONT_SMALL)
        label_x = px + 6
        if label_x + text_w > seg_right - 4:
            label_x = max(seg_left + 4, px - int(text_w) - 8)
        draw.text((label_x, top + 8 + (idx % 3) * 26), label, fill=color, font=FONT_SMALL)

    for label, key, color, scale in signals:
        y = np.clip(series[key] * scale, ymin, ymax)
        for xmin, xmax, _tick_step, _seg_left, _seg_right in segment_boxes:
            points = [(xp(float(x)), yp(float(v))) for x, v in zip(t_ms, y) if xmin <= x <= xmax]
            if len(points) >= 2:
                draw.line(points, fill=color, width=3, joint="curve")

    legend_x, legend_y = left + plot_w + 35, 118
    legend_h = 28 + len(signals) * 33
    draw.rectangle([legend_x - 18, legend_y - 18, width - 35, legend_y + legend_h], fill=(255, 255, 255), outline=(180, 180, 180))
    for idx, (label, _key, color, scale) in enumerate(signals):
        y = legend_y + idx * 33
        draw.line([legend_x, y, legend_x + 45, y], fill=color, width=5)
        suffix = "" if scale == 1 else f" x{scale:g}"
        draw.text((legend_x + 58, y - 12), label + suffix, fill=(35, 35, 35), font=FONT_SMALL)

    box_y = height - 102
    draw.rectangle([left, box_y - 12, left + plot_w, height - 24], fill=(250, 250, 250), outline=(210, 210, 210))
    for idx, text in enumerate(notes[:3]):
        draw.text((left + 18, box_y + idx * 26), text, fill=(35, 35, 35), font=FONT_SMALL)

    draw.text((left, 28), title, fill=(20, 20, 20), font=FONT_TITLE)
    draw.text((left + plot_w // 2 - 70, top + plot_h + 45), "时间 / ms（断轴）", fill=(35, 35, 35), font=FONT)
    draw.text((18, top + 260), "电压 / V", fill=(35, 35, 35), font=FONT)

    out_path = ROOT / out_name
    image.save(out_path)
    return out_path


def main():
    outputs = []
    outputs.append(draw_waveform(
        "relay_detection.raw",
        "relay_detection_waveform.png",
        "继电器检测板 LTspice 瞬态仿真波形",
        [
            ("V(ctrl) 接点控制", "V(ctrl)", (90, 90, 90), 1),
            ("V(sense) 检测节点", "V(sense)", (31, 119, 180), 1),
            ("V(actual) *_ACTUAL", "V(actual)", (34, 139, 34), 1),
            ("V(hash) *#", "V(hash)", (214, 39, 40), 1),
        ],
        (0, 80),
        (-0.2, 5.4),
        [
            (0, 4, "接点闭合", (246, 250, 255), (60, 90, 130)),
            (4.01, 80, "接点断开，RC 节点放电", (255, 250, 245), (130, 80, 60)),
        ],
        [(2, "2 ms 测闭合", (80, 80, 160)), (4, "4 ms 接点打开", (120, 120, 120)), (50, "50 ms 测断开", (80, 80, 160))],
        [
            "闭合 2 ms: sense=4.733 V, ACTUAL=5.000 V, #=0 V",
            "断开 50 ms: sense=0.019 V, ACTUAL=0 V, #=5.000 V",
        ],
    ))

    outputs.append(draw_waveform(
        "ebs.raw",
        "ebs_waveform.png",
        "EBS 板 LTspice 瞬态仿真波形",
        [
            ("V(watchdog_ok) 看门狗正常", "V(watchdog_ok)", (90, 90, 90), 1),
            ("V(ebs_trig) 触发输入", "V(ebs_trig)", (148, 103, 189), 1),
            ("V(drive) 继电器驱动逻辑", "V(drive)", (34, 139, 34), 1),
            ("V(ebs_work) 工作输出", "V(ebs_work)", (214, 39, 40), 1),
            ("V(as_lock) 锁止反馈", "V(as_lock)", (31, 119, 180), 1),
        ],
        (0, 9),
        (-1, 25.5),
        [
            (0, 2, "正常工作", (246, 250, 255), (60, 90, 130)),
            (2.01, 4, "看门狗故障", (255, 245, 245), (150, 70, 70)),
            (5, 7, "EBS_TRIG 触发故障", (255, 250, 235), (150, 95, 40)),
            (7.01, 9, "恢复", (246, 252, 246), (60, 120, 70)),
        ],
        [(1, "1 ms 正常", (80, 80, 160)), (3, "3 ms 看门狗故障", (160, 80, 80)), (6, "6 ms 触发故障", (160, 100, 40)), (8, "8 ms 恢复", (80, 130, 80))],
        [
            "正常 1 ms: EBS_WORK=24 V, AS_LOCK=4.225 V",
            "看门狗故障 3 ms: EBS_WORK=0 V；触发故障 6 ms: EBS_WORK=0 V",
            "恢复 8 ms: EBS_WORK=24 V",
        ],
    ))

    outputs.append(draw_waveform(
        "lock_latch.raw",
        "lock_latch_waveform.png",
        "锁存板 LTspice 瞬态仿真波形",
        [
            ("V(imd_error) IMD 输入", "V(imd_error)", (90, 90, 90), 1),
            ("V(imd_state) 锁存状态", "V(imd_state)", (34, 139, 34), 1),
            ("V(imd_reset) 复位输入", "V(imd_reset)", (31, 119, 180), 1),
            ("V(sdc_out) 安全回路输出", "V(sdc_out)", (214, 39, 40), 1),
        ],
        (0, 9),
        (-1, 25.5),
        [
            (0, 2, "正常", (246, 250, 255), (60, 90, 130)),
            (2.01, 5, "IMD 故障并锁存", (255, 245, 245), (150, 70, 70)),
            (5.01, 5.5, "复位拉低", (255, 250, 235), (150, 95, 40)),
            (5.51, 9, "复位后恢复", (246, 252, 246), (60, 120, 70)),
        ],
        [(1, "1 ms 正常", (80, 80, 160)), (2.5, "2.5 ms 故障", (160, 80, 80)), (4, "4 ms 保持锁存", (160, 80, 80)), (6, "6 ms 复位后", (80, 130, 80))],
        [
            "正常 1 ms: SDC_OUT=24 V",
            "IMD 故障 2.5 ms: IMD_STATE≈0 V, SDC_OUT=0 V；4 ms 仍保持锁存",
            "复位后 6 ms: IMD_STATE≈5 V, SDC_OUT=24 V",
        ],
    ))

    outputs.append(draw_waveform(
        "bspd.raw",
        "bspd_waveform.png",
        "BSPD 板 LTspice 瞬态仿真波形",
        [
            ("V(fault_cond) 故障条件", "V(fault_cond)", (90, 90, 90), 1),
            ("V(delay) 555 延时节点", "V(delay)", (31, 119, 180), 1),
            ("V(trip) 延时触发锁存", "V(trip)", (34, 139, 34), 1),
            ("V(sdc_out) 安全回路输出", "V(sdc_out)", (214, 39, 40), 1),
        ],
        (0, 900),
        (-1, 25.5),
        [
            (0, 100, "正常", (246, 250, 255), (60, 90, 130)),
            (101, 415.22, "故障条件持续，延时计时", (255, 250, 235), (150, 95, 40)),
            (415.22, 900, "延时触发，SDC 断开", (255, 245, 245), (150, 70, 70)),
        ],
        [(200, "200 ms 故障成立", (160, 100, 40)), (250, "250 ms 延时前", (80, 80, 160)), (415.22, "415.22 ms 跳变", (160, 80, 80)), (601, "故障+500 ms", (160, 80, 80))],
        [
            "故障条件 200 ms: FAULT_COND=5 V",
            "延时前 250 ms: SDC_OUT=24 V；故障+500 ms: SDC_OUT=0 V",
            "故障成立后 314.29 ms 断开，小于 500 ms",
        ],
    ))

    outputs.append(draw_broken_x_waveform(
        "bspd.raw",
        "bspd_hold_waveform.png",
        "BSPD 保持断开与电源复位验证波形（断轴）",
        [
            ("V(fault_cond) 故障条件", "V(fault_cond)", (90, 90, 90), 1),
            ("V(reset_n) BSPD 复位", "V(reset_n)", (148, 103, 189), 1),
            ("V(trip) 断开锁存", "V(trip)", (34, 139, 34), 1),
            ("V(sdc_out) 安全回路输出", "V(sdc_out)", (214, 39, 40), 1),
        ],
        [
            (0, 2200, 0.58, 500),
            (11800, 12600, 0.42, 200),
        ],
        (-1, 25.5),
        [
            (0, 100, "正常", (246, 250, 255), (60, 90, 130)),
            (101, 2000, "BSPD 冲突成立", (255, 250, 235), (150, 95, 40)),
            (2001, 12200, "冲突消失后保持断开", (255, 245, 245), (150, 70, 70)),
            (12200, 12300, "复位", (246, 252, 246), (60, 120, 70)),
        ],
        [
            (415.22, "415 ms 断开", (160, 80, 80)),
            (2000.07, "2.00 s 冲突消失", (120, 120, 120)),
            (12050, "10 s 后", (160, 80, 80)),
            (12450, "复位后", (80, 130, 80)),
        ],
        [
            "断开延迟: 314.29 ms，小于 500 ms",
            "冲突消失超过 10 s 后、复位前: SDC_OUT=0 V，仍保持断开",
            "BSPD 电源复位后: SDC_OUT=24 V，安全回路恢复",
        ],
    ))

    outputs.append(draw_waveform(
        "tsal.raw",
        "tsal_waveform.png",
        "TSAL 板 LTspice 瞬态仿真波形",
        [
            ("V(v_controller) 控制器电压缩放", "V(v_controller)", (90, 90, 90), 1),
            ("V(v_battery) 电池电压缩放", "V(v_battery)", (120, 120, 120), 1),
            ("V(red_blink) 555 闪烁源", "V(red_blink)", (255, 127, 14), 1),
            ("V(red_on) 红灯点亮判定", "V(red_on)", (214, 39, 40), 1),
            ("V(red_out_k) 红灯阴极", "V(red_out_k)", (160, 40, 40), 1),
            ("V(green_out_k) 绿灯阴极", "V(green_out_k)", (34, 139, 34), 1),
            ("V(v_safe) 电压安全判定", "V(v_safe)", (31, 119, 180), 1),
            ("V(relays_open) 继电器全断开", "V(relays_open)", (148, 103, 189), 1),
        ],
        (0, 1500),
        (-0.2, 5.4),
        [
            (0, 1200, "高压存在，红灯闪烁", (255, 245, 245), (150, 70, 70)),
            (1201, 1500, "安全，绿灯点亮", (246, 252, 246), (60, 120, 70)),
        ],
        [
            (50, "50 ms 红灯亮", (160, 80, 80)),
            (250, "250 ms 红灯灭", (160, 80, 80)),
            (360.36, "周期起点", (120, 120, 120)),
            (720.72, "下一周期", (120, 120, 120)),
            (1300, "1.3 s 安全", (80, 130, 80)),
        ],
        [
            "红灯闪烁频率: 2.775 Hz，满足 2-5 Hz",
            "红灯占空比: 51.92%，接近 50%",
            "安全 1.3 s: RED_OUT_K=5 V, GREEN_OUT_K=0 V",
        ],
    ))

    for out in outputs:
        print(out)


if __name__ == "__main__":
    main()
