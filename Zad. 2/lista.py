import numpy as np

NMAX = 10

lista = np.empty([NMAX, 2], dtype=int)
for i in range(len(lista)):
    lista[i][0] = 0
    lista[i][1] = -2
head = 0
size = 0
cursor_list = []

def list_add(elmt, index = -1):
    global size
    global head
    if size == 0:
        lista[0][0] = elmt
        lista[0][1] = -1
        size += 1
    elif (index == -1 or index >= size):
        for i in range(size):
            if lista[i][1] == -1:
                lista[i+1][0] = elmt
                lista[i][1] = i+1
                lista[i+1][1] = -1
                size += 1
    elif index == 1:
        for i in range(len(lista)):
            if lista[i][1] == -2:
                empty_index = i
                break
        lista[empty_index][0] = elmt
        lista[empty_index][1] = head
        head = empty_index
        size += 1
    else:
        for i in range(len(lista)):
            if lista[i][1] == -2:
                empty_index = i
                break
        print(f"Empty Index:{empty_index} ")
        next = head
        print(f"Index: {index}")
        for i in range(index-1):
            next = lista[next][1]
            print(f"Next: {next}")
        temp = lista[next][1]
        lista[next][1] = empty_index
        lista[empty_index][0] = elmt
        lista[empty_index][1] = temp
        size += 1

def print_list():
    global cursor_list
    next = head
    for i in range(size):
        cursor_list.append(lista[next][0])
        next = lista[next][1]
    print (cursor_list)

def sort_list():
    global size
    sorted = []
    next = head
    for i in range(size):
        sorted.append(lista[next][0])
        next = lista[next][1]
        sorted.sort()
    print(sorted)
    for i in range(len(lista)):
        lista[i][0] = 0
        lista[i][1] = -2
    size = 0

    for i in sorted:
        # print(i)
        list_add(i)

def list_contains(elmt):
    # global cursor_list
    # if elmt in cursor_list:
    #     print(f"Lista zawiera element {elmt} pod indeksem {cursor_list.index(elmt)}")
    # else:
    #     return(f"Lista nie zawiara elementu {elmt}")
    k = 0
    for i in range(size):
        if lista[i][0] == elmt:
            print(f"Lista zawiera element {elmt}")
            break
        else:
            k+=1
    if k == size:
        print(f"Lista nie zawiera elementu {elmt}")

        


list_add(2)
list_add(3)
list_add(5)
list_add(8)
list_add(15, 1)
print_list()
print(lista)
list_contains(3)
sort_list()
print(lista)
