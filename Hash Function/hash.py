import math
import numpy as np
import sys
from typing import List
import random

from numpy.core.defchararray import mod

C = (math.sqrt(5) - 1) / 2
global_temp = 1

INPUT_SIZE = 0


def frac(x):
    return x - math.floor(x)


def hash(num: int) -> int:
    global global_temp
    hash_value = math.floor(INPUT_SIZE*frac(num * C))
    if hash_value == num:
        print("yes")
        key = (num+global_temp)  # % GLOBAL_LEN_INPUT
        hash_value = math.floor(INPUT_SIZE*frac(key * C))
        global_temp = (global_temp + 1)
        return hash_value
    return hash_value


def hash_func(values: List):
    global INPUT_SIZE
    INPUT_SIZE = len(values)
    temp_list = []
    for _ in range(100):
        temp_list.append([])
    for number in values:
        # ANSWERS[number].append(hash(number))
        temp_list[hash(number)].append(number)
    return temp_list


def hash2(num: int) -> int:
    global global_temp
    # return (num*(num+3)) % GLOBAL_LEN_INPUT
    s = num * C
    x = frac(s)
    hash_value = math.floor(INPUT_SIZE*x)
    if hash_value == num:
        num = num + global_temp
        global_temp += 1
    return hash_value


def hash_func2(values: List):
    global INPUT_SIZE
    INPUT_SIZE = len(values)
    temp_list = []
    for _ in range(100):
        temp_list.append([])
    for number in values:
        temp_list[hash(number)].append(number)
    return temp_list


random_list = []
for i in range(100):
    #random_list.append(random.randint(1, 1000))
    random_list.append(0)

wynik = hash_func(random_list)
print(wynik)
print(wynik.count([]))

