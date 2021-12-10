import math
import numpy as np
import sys
from typing import List
import random
import statistics

from numpy.core.defchararray import mod

C = (math.sqrt(7) - 1) / 2
global_temp = 1

INPUT_SIZE = 30000


def frac(x):
    return x - math.floor(x)


def hash(num: int) -> int:
    global global_temp
    hash_value = math.floor(INPUT_SIZE*frac(num * C))
    return hash_value % 100


def hash_func(values: List):
    # global INPUT_SIZE
    # INPUT_SIZE = len(values)
    temp_list = []
    for _ in range(100):
        temp_list.append([])
    for number in values:
        hashed_num = hash(number)
        # if number in temp_list[hashed_num]:
        #     for i in temp_list:
        #         if len(i) == 0:
        #             i.append(number)
        #             break
        #     continue
        temp_list[hash(number)].append(number)
    return temp_list



testsite_array = []
with open('lista2.txt') as my_file:
    for line in my_file:
        testsite_array.append(int(line))

wynik = hash_func(testsite_array)
print(wynik)
print(wynik.count([]))


lista_koncowa = []
for i in wynik:
    lista_koncowa.append(len(i))

print(f"{statistics.stdev(lista_koncowa) = }")
