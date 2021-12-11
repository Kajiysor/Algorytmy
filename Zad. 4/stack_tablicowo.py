import numpy as np

# ustawienie wartosci stalych

NMAX = 10
ELEMENT = 0
NEXT_POINTER = 1
PREVIOUS_POINTER = 2
EMPTY = -2
LIST_END = -1

stack = np.empty([NMAX, 3], dtype=int)  # tworzenie tablicy
for i in range(len(stack)):  # wypelnianie tablicy wartosciami poczatkowymi
    stack[i][ELEMENT] = 0
    stack[i][NEXT_POINTER] = EMPTY
    stack[i][PREVIOUS_POINTER] = EMPTY
head = 0
size = 0
cursor_list = []


def push(elmt):
    global size
    global head
    if size == 0:  # dodawanie elementu do pustej listy
        stack[0][ELEMENT] = elmt  # wstawienie elementu
        # ustawienie wskaznika nastepnego elementu na koniec listy
        stack[0][NEXT_POINTER] = LIST_END
        # ustawienie wskaznika poprzedniego elementu na koniec listy
        stack[0][PREVIOUS_POINTER] = LIST_END
        size += 1  # zwiekszenie wartosci zmiennej odpowiedzialnej za wielkosc listy
    else:  # dodawanie elementu na koniec listy
        for i in range(size):  # przejscie przez cala liste
            # warunek napotkania ostatniego elementu listy
            if stack[i][NEXT_POINTER] == LIST_END:
                # wstawienie elementu na kolejny indeks w tablicy
                stack[i+1][ELEMENT] = elmt
                # ustawienie wskaznika next ostatniego elementu na nowy element
                stack[i][NEXT_POINTER] = i+1
                # ustawienie wskaznika next nowego elementu na koniec listy
                stack[i+1][NEXT_POINTER] = LIST_END
                # ustawienie wskaznika previous nowego elementu na ostatni element
                stack[i+1][PREVIOUS_POINTER] = i
                size += 1  # zwiekszenie wartosci zmiennej odpowiedzialnej za wielkosc listy
    print(f"Added {elmt} to the stack")


def display():
    global cursor_list
    cursor_list.clear()
    next = head
    for i in range(size):
        cursor_list.append(stack[next][0])
        next = stack[next][NEXT_POINTER]
    print("==============")
    print("Current stack: ")
    print(cursor_list[::-1])
    print("==============")


def peek():
    if size == 0:
        raise Exception("Can't peek from empty stack!")
    global cursor_list
    cursor_list.clear()
    next = head
    for i in range(size):
        cursor_list.append(stack[next][0])
        next = stack[next][NEXT_POINTER]
    print(f"{cursor_list[-1]} is on top of the stack")


def pop():
    global size
    global head
    if size == 0:  # nie mozna usunac elementu z pustej tablicy
        raise Exception("Can't pop from empty stack!")
    if size == 1:  # usuniecie jedynego elementu z listy
        # ustawienie wskaznika next elementu na EMPTY
        stack[head][NEXT_POINTER] = EMPTY
        # ustawienie wskaznika previous elementu na EMPTY
        stack[head][PREVIOUS_POINTER] = EMPTY
        size -= 1  # zmniejszenie wartosci zmiennej odpowiedzialnej za wielkosc listy
    else:  # usuniecie ostatniego elementu z listy
        next = head
        for i in range(size-1):  # przejscie do ostatniego elementu listy
            next = stack[next][NEXT_POINTER]
        # ustawienie wskaznika next przedostatniego elementu aby wskazywal na koniec listy
        stack[stack[next][PREVIOUS_POINTER]][NEXT_POINTER] = LIST_END
        # ustawienie wskaznika next usuwanego elementu na EMPTY
        stack[next][NEXT_POINTER] = EMPTY
        # ustawienie wartosci zmiennej pomocniczej odpowiedzialnej za wartosc usuwanego elementu
        value = stack[next][ELEMENT]
        stack[next][ELEMENT] = 0  # wyzerowanie wartosci usuwanego elementu
        # ustawienie wskaznika previous usuwanego elementu na EMPTY
        stack[next][PREVIOUS_POINTER] = EMPTY
        size -= 1  # zmniejszenie wartosci zmiennej odpowiedzialnej za wielkosc listy
    print(f"Element {value} was popped from the stack")


def main():
    push(1)
    push(2)
    push(3)
    display()
    pop()
    peek()
    display()


if __name__ == "__main__":
    main()
