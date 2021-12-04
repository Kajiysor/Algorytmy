import numpy as np
from typing import List
import math

# D - wymiar przestrzeni
D = 3


class Point:

    def __init__(self, points: List[int]) -> None:
        self.points = points
        if len(self.points) > D:
            raise Exception(f"Point needs to be at most {D}-dimensional!")

        self.point_array = np.zeros(D, dtype=int)

        for i in range(len(self.points)):
            self.point_array[i] = self.points[i]

            self.point_name = str(self.point_array)


class Base:
    def __init__(self) -> None:
        self.list_of_points = []

    def add_point(self, point: Point):
        self.list_of_points.append(point)

    def print_base(self):
        print("Current base of points: ")
        for point in self.list_of_points:
            print(point.point_array)

    def point_distance(self, point_1: Point, point_2: Point) -> int:
        self.sum = 0
        for i in range(D):
            self.sum += ((point_1.point_array[i] - point_2.point_array[i])**2)
        return math.sqrt(self.sum)

    def find_nearest_point(self, point_1: Point) -> int:
        #self.temp_list = []
        self.temp_dict = {}
        for point in self.list_of_points:
            if point is point_1:
                continue
            #self.temp_list.append(self.point_distance(point_1, point))
            self.temp_dict.update(
                {point.point_name: self.point_distance(point_1, point)})
        # print(self.temp_dict)
        # print(self.temp_list)
        # return min(self.temp_list)
        self.nearest = min(self.temp_dict.items(), key=lambda x: x[1])
        print(
            f"The nearest point to {point_1.point_array} is {self.nearest[0]} and it's distance is {self.nearest[1]}")
        # print(min(self.temp_dict))


point1 = Point([1, 2])
point2 = Point([3, 4, 5])
point3 = Point([1, 2, 6])
point4 = Point([4, 5, 6])
point5 = Point([1,2,3,])
b = Base()
b.add_point(point1)
b.add_point(point2)
b.add_point(point3)
b.add_point(point4)
b.print_base()

#print(b.point_distance(point1, point2))
b.find_nearest_point(point1)
