from random import randint
import matplotlib.pyplot as plt


# Tablica liczb
A = []

# Wypelnianie tablicy A losowymi liczbami z przedzialu [0, 120]
def randomizeArray(arr, arr_size):
    arr.clear()
    for _ in range(arr_size):
        arr.append(randint(0, arr_size)) 

# Bubble Sort -> Złożoność O(n)*O(n) = O(n^2)
def bubbleSort(arr):
    il_por = 0
    il_przes = 0

    n = len(arr)
    # Pętla while -> złożoność O(n)
    while(n>0):
        # Pętla for -> złożoność O(n)
        for i in range(0, n-1):
            il_por += 1
            if(arr[i] > arr[i+1]):
                il_przes += 1
                x = arr[i]
                arr[i] = arr[i+1]
                arr[i+1] = x
        n -= 1
    return [il_por, il_przes]

# Insertion Sort -> Złożoność O(n)*O(n) = O(n^2)
def insertionSort(arr):
    il_por = 1
    il_przes = 0
    # Pętla for -> złożoność O(n)
    for i in range(1, len(arr)):
        x = arr[i]
        j = i-1
        # Pętla while -> złożoność O(n)
        while((j >= 0) & (arr[j] > x)):
            il_por += 1
            il_przes += 1
            arr[j+1] = arr[j]
            j -= 1

        arr[j+1] = x
    return [il_por, il_przes]

randomizeArray(A, 100)
print("Nieposortowana tablica: ", A)

out1 = bubbleSort(A)
print("Bubble Sort wynik: ", A)
print("Ilosc operacji porownania: ", out1[0])
print("Ilosc operacji przestawienia: ", out1[1])

print("\n\n")
randomizeArray(A, 100)
print("Nieposortowana tablica: ", A)

out2 = insertionSort(A)
print("Insertion Sort wynik: ", A)
print("Ilosc operacji porownania: ", out2[0])
print("Ilosc operacji przestawienia: ", out2[1])

ilosc_operacji_bubble = []
ilosc_operacji_insertion = []
ilosc_elementow_tablicy = []
wartosc_funkcji_kwadratowej1 = []
wartosc_funkcji_kwadratowej2 = []

for k in range(0, 500):
    B = []
    randomizeArray(B, k)
    out3 = bubbleSort(B)
    ilosc_operacji_bubble.append(out3[0]+out3[1])
    randomizeArray(B, k)
    out4 = insertionSort(B)
    ilosc_operacji_insertion.append(out4[0]+out4[1])
    ilosc_elementow_tablicy.append(k)
    wartosc_funkcji_kwadratowej1.append(0.5*(k**2))
    wartosc_funkcji_kwadratowej2.append(0.75*(k**2))



plt.plot(ilosc_elementow_tablicy, ilosc_operacji_bubble)
plt.plot(ilosc_elementow_tablicy, ilosc_operacji_insertion)
plt.plot(ilosc_elementow_tablicy, wartosc_funkcji_kwadratowej1)
plt.plot(ilosc_elementow_tablicy, wartosc_funkcji_kwadratowej2)
plt.xlabel("Ilosc elementow w tablicy")
plt.ylabel("Ilosc Operacji")
plt.legend(["Bubble Sort", "Insertion Sort", "0.5*x^2", "0.75*x^2"])
plt.savefig("sortowanie.png")