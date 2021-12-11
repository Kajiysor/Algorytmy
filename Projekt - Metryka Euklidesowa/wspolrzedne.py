import numpy as np
import scipy.spatial as spatial
from typing import List, Tuple
import math
import time

# D - wymiar przestrzeni
D = 100


class Point:

    def __init__(self, points: List[int]) -> None:
        self.coords = tuple(points)
        if len(self.coords) > D:
            raise Exception(f"Point needs to be at most {D}-dimensional!")

        self.coords_array = np.zeros(D, dtype=int)

        for i in range(len(self.coords)):
            self.coords_array[i] = self.coords[i]

        self.coords_array = tuple(self.coords_array)


class Base:
    def __init__(self) -> None:
        self.list_of_points = []
        self.list_of_points_coords = []

    def add_point(self, point: Point) -> None:
        self.list_of_points.append(point)

    def print_base(self) -> None:
        print("Current base of points: ")

        for point in self.list_of_points:
            self.list_of_points_coords.append(point.coords_array)
            print(point.coords_array)

    def point_distance(self, point_1: Point, point_2: Point) -> int:
        self.sum = 0

        for i in range(D):
            self.sum += ((point_1.coords_array[i] -
                         point_2.coords_array[i])**2)

        return math.sqrt(self.sum)

    def find_nearest_point(self, point_1: Point) -> Tuple:
        self.temp_dict = {}

        for point in self.list_of_points:
            if point is point_1:
                continue
            self.temp_distance = self.point_distance(point_1, point)
            self.temp_dict.update(
                {point.coords_array: self.temp_distance})
            if self.temp_distance == 0:
                break

        self.nearest = min(self.temp_dict.items(), key=lambda x: x[1])
        print(
            f"The nearest point to {point_1.coords_array} is {self.nearest[0]} and it's distance is {self.nearest[1]}")

        return self.nearest

    def find_nearest_using_kdtree(self, point_1: Point):
        if point_1 in self.list_of_points:
            if point_1.coords_array in self.list_of_points_coords:
                self.list_of_points_coords.remove(point_1.coords_array)

        self.point_tree = spatial.KDTree(self.list_of_points_coords)

        self.nearest_point_distance, self.nearest_point_id = self.point_tree.query(
            point_1.coords_array, k=1)
        print(
            f"The nearest point to {point_1.coords_array} is {self.list_of_points[self.nearest_point_id].coords_array} and it's distance is {self.nearest_point_distance}")


def main():
    point1 = Point([1, 2, ])
    point2 = Point([3, 4, 5])
    point3 = Point([1, 2, 7])
    point4 = Point([4, 5, 6])
    point5 = Point(list(np.random.randint(1000, size=D)))

    b = Base()
    b.add_point(point1)
    b.add_point(point2)
    b.add_point(point3)
    b.add_point(point4)
    b.add_point(point5)
    for x in range(100000):
        tmp_array = list(np.random.randint(1000, size=D))
        b.add_point(Point(tmp_array))
    print("========================")
    b.print_base()

    print("===================================================================================")
    print("Using brute force:")
    startMilis1 = int(round(time.time()*1000))
    b.find_nearest_point(point5)
    endMilis1 = int(round(time.time()*1000))
    timeTaken1 = endMilis1 - startMilis1
    print(f"{timeTaken1 = } [ms]")
    print("===================================================================================")
    print("Using kdtree:")
    startMilis2 = int(round(time.time()*1000))
    b.find_nearest_using_kdtree(point5)
    endMilis2 = int(round(time.time()*1000))
    timeTaken2 = endMilis2 - startMilis2
    print(f"{timeTaken2 = } [ms]")
    print("===================================================================================")


if __name__ == "__main__":
    main()
