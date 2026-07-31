"""Render close inspection views of the R6 battery labyrinth and SMA wall."""

from __future__ import annotations

import argparse
from pathlib import Path

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.art3d import Poly3DCollection

from render_final_previews import triangles


def add_mesh(ax, faces):
    ax.add_collection3d(
        Poly3DCollection(
            faces,
            facecolor=(0.68, 0.70, 0.76, 1.0),
            edgecolor=(0.04, 0.05, 0.07, 0.35),
            linewidth=0.14,
        )
    )
    ax.set_axis_off()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("folder", type=Path)
    parser.add_argument("output", type=Path)
    args = parser.parse_args()

    faces = triangles(args.folder / "RES_MainHousing.stl")
    fig = plt.figure(figsize=(12, 6), dpi=220, facecolor="white")

    bottom = fig.add_subplot(1, 2, 1, projection="3d")
    add_mesh(bottom, faces)
    bottom.set_xlim(-86, 86)
    bottom.set_ylim(-66, 66)
    bottom.set_zlim(-1, 12)
    bottom.set_box_aspect((172, 132, 22))
    bottom.view_init(elev=-90, azim=-90)
    bottom.set_title("Battery-side bottom: continuous labyrinth groove", fontsize=11)

    sma = fig.add_subplot(1, 2, 2, projection="3d")
    add_mesh(sma, faces)
    sma.set_xlim(42, 94)
    sma.set_ylim(66, 78)
    sma.set_zlim(22, 68)
    sma.set_box_aspect((52, 12, 46))
    sma.view_init(elev=0, azim=90)
    sma.set_title("Front SMA zone: full T4 wall, no relief pocket", fontsize=11)

    fig.tight_layout()
    fig.savefig(args.output, bbox_inches="tight", pad_inches=0.08)


if __name__ == "__main__":
    main()
