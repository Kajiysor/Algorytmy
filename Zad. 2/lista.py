import numpy as np

NMAX = 10
ELEMENT = 0
POINTER = 1
EMPTY = -2
LIST_END = -1

lista = np.empty([NMAX, 2], dtype=int)
for i in range(len(lista)):
    lista[i][ELEMENT] = 0
    lista[i][POINTER] = EMPTY
head = 0
size = 0
cursor_list = []
sorted = []

def list_add(elmt, index = LIST_END):
    global size
    global head
    if size == 0:
        lista[0][ELEMENT] = elmt
        lista[0][POINTER] = LIST_END
        size += 1
    elif (index == -1 or index >= size):
        for i in range(size):
            if lista[i][POINTER] == LIST_END:
                lista[i+1][ELEMENT] = elmt
                lista[i][POINTER] = i+1
                lista[i+1][POINTER] = LIST_END
                size += 1
    elif index == 0:
        for i in range(len(lista)):
            if lista[i][POINTER] == EMPTY:
                empty_index = i
                break
        lista[empty_index][ELEMENT] = elmt
        lista[empty_index][POINTER] = head
        head = empty_index
        size += 1
    else:
        for i in range(len(lista)):
            if lista[i][POINTER] == EMPTY:
                empty_index = i
                break
        # print(f"Empty Index:{empty_index} ")
        next = head
        # print(f"Index: {index}")
        for i in range(index-1):
            next = lista[next][POINTER]
            # print(f"Next: {next}")
        temp = lista[next][POINTER]
        lista[next][POINTER] = empty_index
        lista[empty_index][ELEMENT] = elmt
        lista[empty_index][POINTER] = temp
        size += 1
    print(f"Dodano do listy element {elmt} na indeks {index}")

def print_list():
    global cursor_list
    cursor_list.clear()
    # print(f"head = {head}")
    next = head
    for i in range(size):
        cursor_list.append(lista[next][0])
        next = lista[next][POINTER]
    print (cursor_list)

def sort_list():
    global size
    global sorted
    global head
    sorted.clear()
    next = head
    for i in range(size):
        sorted.append(lista[next][0])
        next = lista[next][POINTER]
        sorted.sort()
    for i in range(len(lista)):
        lista[i][ELEMENT] = 0
        lista[i][POINTER] = EMPTY
    size = 0
    head = 0
    
    print("Posortowano liste oraz tablice")
    print(sorted)

    for i in sorted:
        # print(i)
        list_add(i)


def list_contains(elmt):
    global head
    # global cursor_list
    # if elmt in cursor_list:
    #     print(f"Lista zawiera element {elmt} pod indeksem {cursor_list.index(elmt)}")
    # else:
    #     return(f"Lista nie zawiara elementu {elmt}")
    # k = 0
    # for i in range(size):
    #     if lista[i][ELEMENT] == elmt:
    #         print(f"Lista zawiera element {elmt}")
    #         return i
    #     else:
    #         k+=1
    # if k == size:
    #     print(f"Lista nie zawiera elementu {elmt}")
    #     return -999;
    next = head
    for i in range(size):
        if(lista[next][ELEMENT] == elmt):
            print(f"Lista zawiera element {elmt}")
            return i;
        next = lista[next][POINTER]
    print(f"Lista nie zawiera elementu {elmt}")
    return -999

def list_remove_index(index = -1):
    global size
    global head
    if size == 0:
        return
    
    if size == 1:
        lista[head][POINTER] = EMPTY
        size -=1
    elif (index == -1 or index == size):
        next = head
        for i in range(size-2):
            next = lista[next][POINTER]
        lista[lista[next][POINTER]][POINTER] = EMPTY
        value = lista[lista[next][POINTER]][ELEMENT]
        lista[lista[next][POINTER]][ELEMENT] = 0
        lista[next][POINTER] = LIST_END
        size -= 1
    elif index == 0:
        temp = head
        head = lista[head][POINTER]
        lista[temp][POINTER] = EMPTY
        value = lista[temp][ELEMENT]
        lista[temp][ELEMENT] = 0
        size -= 1
    else:
        next = head
        for i in range(index-1):
            next = lista[next][POINTER]
        temp = lista[next][POINTER]
        lista[next][POINTER] = lista[lista[next][POINTER]][POINTER]
        lista[temp][POINTER] = EMPTY
        value = lista[temp][ELEMENT]
        lista[temp][ELEMENT] = 0
        size -= 1

    print(f"Element o wartosci {value} spod indeksu {index} zostal usuniety")  

def list_remove_element(elmt):
    pos = list_contains(elmt)
    if (pos != -999):
        list_remove_index(pos)
        # print(f"Element {elmt} zostal usuniety z listy")
    # else:
    #     print(f"Elementu {elmt} nie ma na liscie wiec nie zostal usuniety")  


print("==================================")
print("Dodawanie elementu do listy: \n")
list_add(2)
list_add(3)
list_add(5)
list_add(8)
list_add(15, 1)
print("==================================")
print_list()
print(lista)
print("==================================")
print("Wywolanie metody contains(): \n")
list_contains(9)
print("==================================")
print("Wywolanie metody remove_index(): \n")
list_remove_index(3)
print_list()
print(lista)
print("==================================")
print("Wywolanie metody remove_element(): \n")
list_remove_element(3)
print("==================================")
print_list()
print(lista)
print("==================================")
print("Wywolanie metody sort(): \n")
sort_list()
print(lista)
print("==================================")
print_list()
print(lista)
print("==================================")
# print("Usuniecie ostatniego elementu")
# list_add(77)
# list_add(99)
# list_remove_index()
# list_remove_index()
# list_add(55)
# print("==================================")
# print_list()
# print(lista)
# print("==================================")
# list_add(77, 0)
# print_list()
# print(lista)
# print("==================================")
