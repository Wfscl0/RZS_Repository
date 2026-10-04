"""Render lightweight inspection previews from the final ASCII STL files."""

from __future__ import annotations

import argparse
from pathlib import Path

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.art3d import Poly3DCollection


def triangles(path: Path):
    result = []
    current = []
    with path.open("r", encoding="ascii") as stream:
        for line in stream:
            words = line.split()
            if len(words) == 4 and words[0] == "vertex":
                current.append(tuple(float(value) for value in words[1:]))
                if len(current) == 3:
                    result.append(tuple(current))
                    current = []
    return result


def draw(ax, path: Path, elevation: float, azimuth: float, title: str):
    faces = triangles(path)
    collection = Poly3DCollection(
        faces,
        facecolor=(0.38, 0.40, 0.44, 1.0),
        edgecolor=(0.04, 0.05, 0.06, 0.18),
        linewidth=0.10,
    )
    ax.add_collection3d(collection)
    values = [coordinate for face in faces for point in face for coordinate in point]
    xs = values[0::3]
    ys = values[1::3]
    zs = values[2::3]
    centres = ((min(xs) + max(xs)) / 2, (min(ys) + max(ys)) / 2, (min(zs) + max(zs)) / 2)
    span = max(max(xs) - min(xs), max(ys) - min(ys), max(zs) - min(zs)) / 2
    ax.set_xlim(centres[0] - span, centres[0] + span)
    ax.set_ylim(centres[1] - span, centres[1] + span)
    ax.set_zlim(centres[2] - span, centres[2] + span)
    ax.set_box_aspect((1, 1, 1))
    ax.view_init(elev=elevation, azim=azimuth)
    ax.set_title(title, fontsize=11)
    ax.set_axis_off()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("folder", type=Path)
    parser.add_argument("output", type=Path)
    args = parser.parse_args()

    fig = plt.figure(figsize=(15, 5), dpi=180, facecolor="white")
    specs = (
        ("RES_MainHousing.stl", 38, -52, "Main housing — open side"),
        ("RES_TopCover.stl", -30, -52, "Top cover — underside"),
        ("RES_BatteryCover.stl", 32, 128, "Battery cover — sealing side"),
    )
    for index, (name, elev, azim, title) in enumerate(specs, start=1):
        draw(fig.add_subplot(1, 3, index, projection="3d"), args.folder / name, elev, azim, title)
    fig.tight_layout()
    fig.savefig(args.output, bbox_inches="tight", pad_inches=0.05)


if __name__ == "__main__":
    main()
