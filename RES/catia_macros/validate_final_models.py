"""Validate CATIA-exported ASCII STL production parts.

Checks triangle count, bounding box, signed volume and edge manifoldness.
Only Python's standard library is required so the supplier can rerun it.
"""

from __future__ import annotations

import argparse
import collections
import json
import math
from pathlib import Path


def sub(a, b):
    return (a[0] - b[0], a[1] - b[1], a[2] - b[2])


def cross(a, b):
    return (
        a[1] * b[2] - a[2] * b[1],
        a[2] * b[0] - a[0] * b[2],
        a[0] * b[1] - a[1] * b[0],
    )


def dot(a, b):
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]


def qvertex(v, resolution=1.0e-5):
    return tuple(round(value / resolution) for value in v)


def analyse_ascii_stl(path: Path):
    triangles = []
    current = []
    minimum = [math.inf, math.inf, math.inf]
    maximum = [-math.inf, -math.inf, -math.inf]

    with path.open("r", encoding="ascii", errors="strict") as stream:
        for line in stream:
            words = line.split()
            if len(words) == 4 and words[0] == "vertex":
                vertex = tuple(float(value) for value in words[1:])
                current.append(vertex)
                for axis in range(3):
                    minimum[axis] = min(minimum[axis], vertex[axis])
                    maximum[axis] = max(maximum[axis], vertex[axis])
                if len(current) == 3:
                    triangles.append(tuple(current))
                    current = []
    if current or not triangles:
        raise ValueError(f"Malformed or empty STL: {path}")

    signed_volume_6 = 0.0
    area_2 = 0.0
    edges = collections.Counter()
    degenerate = 0
    for v0, v1, v2 in triangles:
        normal_2 = cross(sub(v1, v0), sub(v2, v0))
        normal_length = math.sqrt(dot(normal_2, normal_2))
        area_2 += normal_length
        if normal_length < 1.0e-9:
            degenerate += 1
        signed_volume_6 += dot(v0, cross(v1, v2))
        q = (qvertex(v0), qvertex(v1), qvertex(v2))
        for left, right in ((q[0], q[1]), (q[1], q[2]), (q[2], q[0])):
            edges[tuple(sorted((left, right)))] += 1

    bad_items = [(edge, count) for edge, count in edges.items() if count != 2]
    bad_edges = len(bad_items)
    bad_edge_samples = []
    for edge, count in bad_items[:24]:
        bad_edge_samples.append(
            {
                "count": count,
                "vertices_mm": [
                    [round(coordinate * 1.0e-5, 5) for coordinate in vertex]
                    for vertex in edge
                ],
            }
        )
    volume_mm3 = abs(signed_volume_6) / 6.0
    return {
        "file": path.name,
        "triangles": len(triangles),
        "bbox_min_mm": [round(value, 4) for value in minimum],
        "bbox_max_mm": [round(value, 4) for value in maximum],
        "size_mm": [round(maximum[i] - minimum[i], 4) for i in range(3)],
        "surface_area_mm2": round(area_2 / 2.0, 2),
        "volume_mm3": round(volume_mm3, 2),
        "volume_cm3": round(volume_mm3 / 1000.0, 3),
        "degenerate_triangles": degenerate,
        "nonmanifold_or_boundary_edges": bad_edges,
        "bad_edge_samples": bad_edge_samples,
        "watertight": bad_edges == 0 and degenerate == 0,
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("folder", type=Path)
    parser.add_argument("--density", type=float, default=1.10, help="g/cm^3")
    parser.add_argument("--unit-cost", type=float, default=0.45, help="CNY/g")
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()

    names = ("RES_MainHousing.stl", "RES_TopCover.stl", "RES_BatteryCover.stl")
    results = [analyse_ascii_stl(args.folder / name) for name in names]
    for item in results:
        item["estimated_mass_g"] = round(item["volume_cm3"] * args.density, 1)
        item["estimated_part_cost_cny"] = round(
            item["estimated_mass_g"] * args.unit_cost, 2
        )

    report = {
        "assumed_resin_density_g_cm3": args.density,
        "quoted_unit_cost_cny_g": args.unit_cost,
        "parts": results,
        "total_volume_cm3": round(sum(x["volume_cm3"] for x in results), 3),
        "total_estimated_mass_g": round(sum(x["estimated_mass_g"] for x in results), 1),
        "total_estimated_part_cost_cny": round(
            sum(x["estimated_part_cost_cny"] for x in results), 2
        ),
        "all_watertight": all(x["watertight"] for x in results),
    }
    text = json.dumps(report, ensure_ascii=False, indent=2)
    print(text)
    if args.output:
        args.output.write_text(text + "\n", encoding="utf-8")


if __name__ == "__main__":
    main()
