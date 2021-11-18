import numpy as np

### ustawienie wartosci stalych

NMAX = 10
ELEMENT = 0
NEXT_POINTER = 1
PREVIOUS_POINTER = 2
EMPTY = -2
LIST_END = -1

lista = np.empty([NMAX, 3], dtype=int) # tworzenie tablicy
for i in range(len(lista)): # wypelnianie tablicy wartosciami poczatkowymi
    lista[i][ELEMENT] = 0
    lista[i][NEXT_POINTER] = EMPTY
    lista[i][PREVIOUS_POINTER] = EMPTY
head = 0
size = 0
cursor_list = []
sorted = []

def list_add(elmt, index = LIST_END): ### funkcja odpowiedzialna za dodawanie elementow do listy
    global size
    global head
    if size == 0: ## dodawanie elementu do pustej listy
        lista[0][ELEMENT] = elmt # wstawienie elementu
        lista[0][NEXT_POINTER] = LIST_END # ustawienie wskaznika nastepnego elementu na koniec listy
        lista[0][PREVIOUS_POINTER] = LIST_END # ustawienie wskaznika poprzedniego elementu na koniec listy
        size += 1 # zwiekszenie wartosci zmiennej odpowiedzialnej za wielkosc listy
    elif (index == -1 or index >= size): ## dodawanie elementu na koniec listy
        for i in range(size): # przejscie przez cala liste
            if lista[i][NEXT_POINTER] == LIST_END: # warunek napotkania ostatniego elementu listy
                lista[i+1][ELEMENT] = elmt # wstawienie elementu na kolejny indeks w tablicy
                lista[i][NEXT_POINTER] = i+1 # ustawienie wskaznika next ostatniego elementu na nowy element
                lista[i+1][NEXT_POINTER] = LIST_END # ustawienie wskaznika next nowego elementu na koniec listy
                lista[i+1][PREVIOUS_POINTER] = i # ustawienie wskaznika previous nowego elementu na ostatni element
                size += 1 # zwiekszenie wartosci zmiennej odpowiedzialnej za wielkosc listy
    elif index == 0: ## dodawanie elementu na 0 indeks listy
        for i in range(len(lista)): # znalezienie pierwszego wolnego indeksu w tablicy
            if lista[i][NEXT_POINTER] == EMPTY:
                empty_index = i
                break
        lista[empty_index][ELEMENT] = elmt # wstawienie elementu na wolny indeks w tablicy
        lista[empty_index][NEXT_POINTER] = head # ustawienie wskaznika next wstawionego elementu na indeks wskazywany przez head'a
        lista[empty_index][PREVIOUS_POINTER] = LIST_END # ustawienie wskaznika previous wstawionego elementu na koniec listy
        lista[head][PREVIOUS_POINTER] = empty_index # ustawienie wskaznika previous elementu wskazywanego przez head'a na indeks w ktory wstawiono element
        head = empty_index # ustawienie heada aby wskazywal nowo wstawiony element
        size += 1 # zwiekszenie wartosci zmiennej odpowiedzialnej za wielkosc listy
    else: ## dodawanie elementu na kazdy inny dowolny indeks listy
        for i in range(len(lista)): # znalezienie pierwszego wolnego indeksu tablicy
            if lista[i][NEXT_POINTER] == EMPTY:
                empty_index = i
                break
        next = head
        for i in range (index):
            next = lista[next][NEXT_POINTER] # ustawienie wartosci zmiennej next na wybrany indeks
        lista[lista[next][PREVIOUS_POINTER]][NEXT_POINTER] = empty_index # ustawienie wskaznika next poprzedniego elementu aby wskazywal na nowy element
        lista[empty_index][ELEMENT] = elmt # wstawienie nowego elementu na wolny indeks
        lista[empty_index][NEXT_POINTER] = next # ustawienie wskaznika next wstawianego elementu aby wskazywal na element ktory znajdowal sie tam poprzednio
        lista[empty_index][PREVIOUS_POINTER] = lista[next][PREVIOUS_POINTER] # ustawienie wskaznika previous wstawianego elementu aby wskazywal poprzedzajacy element
        lista[next][PREVIOUS_POINTER] = empty_index # ustawienie wskaznika previous zastepowanego elementu aby wskazywal nowy element
        size += 1 # zwiekszenie wartosci zmiennej odpowiedzialnej za wielkosc listy
    print(f"Dodano do listy element {elmt} na indeks {index}")

def print_list(): ### funkcja odpowiedzialna za wypisanie naszej listy w postaci listy
    global cursor_list
    cursor_list.clear()
    next = head
    for i in range(size):
        cursor_list.append(lista[next][0])
        next = lista[next][NEXT_POINTER]
    print (cursor_list)

def sort_list(): ### funkcja odpowiedzialna za posorotowanie listy oraz tablicy
    global size
    global sorted
    global head
    sorted.clear()
    next = head
    for i in range(size): # petla odpowiedzialna za dodanie kolejnych elementow do listy pomocnczej
        sorted.append(lista[next][0])
        next = lista[next][NEXT_POINTER]
    sorted.sort() # posortowanie listy pomocniczej
    for i in range(len(lista)): # przywrocenie postaci domyslnej naszej tablicy
        lista[i][ELEMENT] = 0
        lista[i][NEXT_POINTER] = EMPTY
        lista[i][PREVIOUS_POINTER] = EMPTY
    size = 0
    head = 0
    
    print("Posortowano liste oraz tablice")
    print(sorted)

    for i in sorted: # wstawienie posortowanych elementow w kolejnosci do tablicy
        list_add(i)


def list_contains(elmt): ### funkcja odpowiedzialna za sprawdzenie czy lista zawiera dany element, zwraca pierwszy indeks na ktory wystepuje dany element
    global head
    next = head
    for i in range(size):
        if(lista[next][ELEMENT] == elmt):
            print(f"Lista zawiera element {elmt}")
            return i;
        next = lista[next][NEXT_POINTER]
    print(f"Lista nie zawiera elementu {elmt}")
    return -999

def list_remove_index(index = -1): ### funkcja odpowiedzialna za usuniecie elementu z listy pod wskazanym indeksem
    global size
    global head
    if size == 0: ## nie mozna usunac elementu z pustej tablicy
        print("Lista jest pusta, nie mozna usunac zadnego elementu!")
        return
    
    if size == 1: ## usuniecie jedynego elementu z listy
        lista[head][NEXT_POINTER] = EMPTY # ustawienie wskaznika next elementu na EMPTY
        lista[head][PREVIOUS_POINTER] = EMPTY # ustawienie wskaznika previous elementu na EMPTY
        size -=1 # zmniejszenie wartosci zmiennej odpowiedzialnej za wielkosc listy
    elif (index == -1 or index == size): ## usuniecie ostatniego elementu z listy
        next = head
        for i in range(size-1): # przejscie do ostatniego elementu listy
            next = lista[next][NEXT_POINTER]
        lista[lista[next][PREVIOUS_POINTER]][NEXT_POINTER] = LIST_END # ustawienie wskaznika next przedostatniego elementu aby wskazywal na koniec listy
        lista[next][NEXT_POINTER] = EMPTY # ustawienie wskaznika next usuwanego elementu na EMPTY
        value = lista[next][ELEMENT] # ustawienie wartosci zmiennej pomocniczej odpowiedzialnej za wartosc usuwanego elementu
        lista[next][ELEMENT] = 0 # wyzerowanie wartosci usuwanego elementu
        lista[next][PREVIOUS_POINTER] = EMPTY # ustawienie wskaznika previous usuwanego elementu na EMPTY
        size -= 1 # zmniejszenie wartosci zmiennej odpowiedzialnej za wielkosc listy
    elif index == 0: # usuniecie pierwszego elementu listy
        temp = head
        head = lista[head][NEXT_POINTER] # ustawienie head aby wskazywal na indeks kolejnego elementu
        lista[head][PREVIOUS_POINTER] = LIST_END # ustawienie wskaznika previous nowego pierwszego elementu aby wskazywal na koniec listy
        lista[temp][NEXT_POINTER] = EMPTY # ustawienie wskaznika next starego head'a na EMPTY
        lista[temp][PREVIOUS_POINTER] = EMPTY # ustawienie wskaznika previous starego head'a na EMPTY
        value = lista[temp][ELEMENT] # ustawienie wartosci zmiennej pomocniczej odpowiedzialnej za wartosc usuwanego elementu
        lista[temp][ELEMENT] = 0 # wyzerowanie wartosci usuwanego elementu
        size -= 1 # zmniejszenie wartosci zmiennej odpowiedzialnej za wielkosc listy
    else: # usuniecie elementu z kazdnego innego dowolnego indeksu listy
        next = head
        for i in range(index):
            next = lista[next][NEXT_POINTER] # przejscie do elementu pod podanym indeksem
        value = lista[next][ELEMENT] # ustawienie wartosci zmiennej pomocniczej odpowiedzialnej za wartosc usuwanego elementu
        lista[lista[next][PREVIOUS_POINTER]][NEXT_POINTER] = lista[next][NEXT_POINTER] # ustawienie wskaznika next poprzedzajacego elementu aby wskazywal na element nastepujacy
        lista[lista[next][NEXT_POINTER]][PREVIOUS_POINTER] = lista[next][PREVIOUS_POINTER] # ustawienie wskaznika previous nastepujacego elementu aby wskazywal na element poprzedzajacy
        lista[next][ELEMENT] = 0 # wyzerowanie wartosci usuwanego elementu
        lista[next][NEXT_POINTER] = EMPTY # ustawienie wskaznika next usuwanego elementu na EMPTY
        lista[next][PREVIOUS_POINTER] = EMPTY # ustawienie wskaznika previous usuwanego elementu na EMPTY
        size -= 1 # zmniejszenie wartosci zmiennej odpowiedzialnej za wielkosc listy

    print(f"Element o wartosci {value} spod indeksu {index} zostal usuniety")  

def list_remove_element(elmt): ### funkcja odpowiedzialna za usuwanie danego elementu z listy, wykorzystuje do tego funkcje usuwajaca element spod danego indeksu
    pos = list_contains(elmt) # ustawienie wartosci pomocniczej zmiennej na pierwszy wystepujacy indeks podanego elementu
    if (pos != -999): # jezeli podany element znajduje sie w liscie, zostanie on usuniety za pomoca funkcji usuwajacej element spod danego indeksu
        list_remove_index(pos)


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
print("Ostateczna postac listy i tablicy: \n")
print_list()
print(lista)
print("==================================")