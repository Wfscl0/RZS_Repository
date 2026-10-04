"""Repair geometrically closed ASCII STL meshes that contain T-junction edges.

CATIA can tessellate one side of a circular/planar intersection as one edge and
the adjacent face as two collinear edges. The solid is closed, but strict STL
validators report the unmatched 1-vs-2 edge subdivision as boundary edges.
This script splits only the triangle owning the long edge at the existing
collinear boundary vertex. No vertex is moved and no surface is remeshed.
"""

from __future__ import annotations

import argparse
import collections
import math
from pathlib import Path


RESOLUTION = 1.0e-5


def qvertex(vertex):
    return tuple(round(value / RESOLUTION) for value in vertex)


def read_ascii_stl(path: Path):
    triangles = []
    current = []
    with path.open("r", encoding="ascii", errors="strict") as stream:
        for line in stream:
            words = line.split()
            if len(words) == 4 and words[0] == "vertex":
                current.append(tuple(float(value) for value in words[1:]))
                if len(current) == 3:
                    triangles.append(tuple(current))
                    current = []
    if current or not triangles:
        raise ValueError(f"Malformed or empty ASCII STL: {path}")
    return triangles


def boundary_data(triangles):
    counts = collections.Counter()
    owners = {}
    vertices = {}
    for triangle_index, triangle in enumerate(triangles):
        q = tuple(qvertex(vertex) for vertex in triangle)
        for vertex, qv in zip(triangle, q):
            vertices[qv] = vertex
        for edge_index, (left, right) in enumerate(((q[0], q[1]), (q[1], q[2]), (q[2], q[0]))):
            edge = tuple(sorted((left, right)))
            counts[edge] += 1
            owners.setdefault(edge, []).append((triangle_index, edge_index))
    boundary = [edge for edge, count in counts.items() if count == 1]
    return boundary, owners, vertices


def point_inside_segment(point, left, right, tolerance=2.0e-5):
    direction = tuple(right[i] - left[i] for i in range(3))
    offset = tuple(point[i] - left[i] for i in range(3))
    length_sq = sum(value * value for value in direction)
    if length_sq == 0:
        return False
    parameter = sum(offset[i] * direction[i] for i in range(3)) / length_sq
    if not 1.0e-7 < parameter < 1.0 - 1.0e-7:
        return False
    closest = tuple(left[i] + parameter * direction[i] for i in range(3))
    distance_sq = sum((point[i] - closest[i]) ** 2 for i in range(3))
    return distance_sq <= tolerance * tolerance


def split_one_tjunction(triangles):
    boundary, owners, vertices = boundary_data(triangles)
    boundary_vertices = list({vertex for edge in boundary for vertex in edge})

    for long_edge in boundary:
        left_q, right_q = long_edge
        left = vertices[left_q]
        right = vertices[right_q]
        candidates = []
        for middle_q in boundary_vertices:
            if middle_q in long_edge:
                continue
            middle = vertices[middle_q]
            if point_inside_segment(middle, left, right):
                distance = sum((middle[i] - left[i]) ** 2 for i in range(3))
                candidates.append((distance, middle_q, middle))
        if not candidates:
            continue

        _, middle_q, middle = min(candidates)
        triangle_index, _ = owners[long_edge][0]
        triangle = triangles[triangle_index]
        q = tuple(qvertex(vertex) for vertex in triangle)
        oriented = (
            (triangle[0], triangle[1], triangle[2], q[0], q[1]),
            (triangle[1], triangle[2], triangle[0], q[1], q[2]),
            (triangle[2], triangle[0], triangle[1], q[2], q[0]),
        )
        for edge_left, edge_right, opposite, q_left, q_right in oriented:
            if {q_left, q_right} == {left_q, right_q}:
                triangles[triangle_index] = (edge_left, middle, opposite)
                triangles.append((middle, edge_right, opposite))
                return True, long_edge, middle_q
        raise RuntimeError("Boundary edge owner did not contain the expected edge")
    return False, None, None


def normal(triangle):
    a, b, c = triangle
    u = tuple(b[i] - a[i] for i in range(3))
    v = tuple(c[i] - a[i] for i in range(3))
    cross = (
        u[1] * v[2] - u[2] * v[1],
        u[2] * v[0] - u[0] * v[2],
        u[0] * v[1] - u[1] * v[0],
    )
    length = math.sqrt(sum(value * value for value in cross))
    if length == 0:
        return (0.0, 0.0, 0.0)
    return tuple(value / length for value in cross)


def write_ascii_stl(path: Path, triangles):
    with path.open("w", encoding="ascii", newline="\n") as stream:
        stream.write("solid repaired_tjunctions\n")
        for triangle in triangles:
            nx, ny, nz = normal(triangle)
            stream.write(f"  facet normal {nx:.9g} {ny:.9g} {nz:.9g}\n")
            stream.write("    outer loop\n")
            for x, y, z in triangle:
                stream.write(f"      vertex {x:.9g} {y:.9g} {z:.9g}\n")
            stream.write("    endloop\n")
            stream.write("  endfacet\n")
        stream.write("endsolid repaired_tjunctions\n")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("input", type=Path)
    parser.add_argument("output", type=Path)
    args = parser.parse_args()

    triangles = read_ascii_stl(args.input)
    repairs = 0
    while repairs < 100:
        changed, _, _ = split_one_tjunction(triangles)
        if not changed:
            break
        repairs += 1
    write_ascii_stl(args.output, triangles)
    boundary, _, _ = boundary_data(triangles)
    print(f"repairs={repairs} remaining_boundary_edges={len(boundary)}")
    if boundary:
        raise SystemExit(2)


if __name__ == "__main__":
    main()
