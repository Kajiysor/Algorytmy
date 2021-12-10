import math
from typing import List
import random
import statistics


C = (math.sqrt(7) - 1) / 2
global_temp = 1

<<<<<<< HEAD
INPUT_SIZE = 30000
=======
INPUT_SIZE = None
>>>>>>> 716b1bc36a366ce3b44aa5398914d136bbd0e5f9


def frac(x):
    return x - math.floor(x)


def hash(num: int) -> int:
    global global_temp
    hash_value = math.floor(INPUT_SIZE*frac(num * C))
<<<<<<< HEAD
    return hash_value % 100
=======
    # if hash_value == num:
    #     key = (num+global_temp)  # % GLOBAL_LEN_INPUT
    #     hash_value = math.floor(INPUT_SIZE*frac(key * C))
    #     global_temp = (global_temp + 1)
    #     return hash_value
    return hash_value
>>>>>>> 716b1bc36a366ce3b44aa5398914d136bbd0e5f9


def hash_func(values: List):
    # global INPUT_SIZE
    # INPUT_SIZE = len(values)
    temp_list = []
    for _ in range(100):
        temp_list.append([])
    for number in values:
        hashed_num = hash(number)
<<<<<<< HEAD
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
=======
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
>>>>>>> 716b1bc36a366ce3b44aa5398914d136bbd0e5f9

wynik = hash_func(testsite_array)
print(wynik)
print(wynik.count([]))
<<<<<<< HEAD


lista_koncowa = []
for i in wynik:
    lista_koncowa.append(len(i))

print(f"{statistics.stdev(lista_koncowa) = }")
=======
>>>>>>> 716b1bc36a366ce3b44aa5398914d136bbd0e5f9
