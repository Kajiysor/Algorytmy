import math
from typing import List
import random
import statistics


C = (math.sqrt(7) - 1) / 2
global_temp = 1

INPUT_SIZE = None


def frac(x):
    return x - math.floor(x)


def hash(num: int) -> int:
    global global_temp
    hash_value = math.floor(INPUT_SIZE*frac(num * C))
    # if hash_value == num:
    #     key = (num+global_temp)  # % GLOBAL_LEN_INPUT
    #     hash_value = math.floor(INPUT_SIZE*frac(key * C))
    #     global_temp = (global_temp + 1)
    #     return hash_value
    return hash_value


def hash_func(values: List):
    # global INPUT_SIZE
    # INPUT_SIZE = len(values)
    temp_list = []
    for _ in range(100):
        temp_list.append([])
    for number in values:
        hashed_num = hash(number)
        if number in temp_list[hashed_num]:
            for x in temp_list:
                if len(x) == 0:
                    x.append(number)
                    break
            continue
        temp_list[hashed_num].append(number)
    return temp_list


random_list = []
for i in range(100):
    #random_list.append(random.randint(1, 1000)%10)
    random_list.append(i % 10)

wynik = hash_func(random_list)
print(wynik)
print(wynik.count([]))
