from random import randint
import matplotlib.pyplot as plt

# Ilosc liczb w tablicy
#ARR_SIZE = 120

# Tablica liczb
A = []

# Wypelnianie tablicy A losowymi liczbami z przedzialu [0, 120]
def randomizeArray(arr, arr_size):
    arr.clear()
    for _ in range(arr_size):
        arr.append(randint(0, arr_size)) 

# Bublle Sort
def bubbleSort(arr):
    il_por = 0
    il_przes = 0

    n = len(arr)
    while(n>0):
        for i in range(0, n-1):
            il_por += 1
            if(arr[i] > arr[i+1]):
                il_przes += 1
                x = arr[i]
                arr[i] = arr[i+1]
                arr[i+1] = x
        n -= 1
    return [il_por, il_przes]

# Insertion Sort
def insertionSort(arr):
    il_por = 1
    il_przes = 0

    for i in range(1, len(arr)):
        x = arr[i]
        j = i-1
        
        while((j >= 0) & (arr[j] > x)):
            il_por += 1
            il_przes += 1
            arr[j+1] = arr[j]
            j -= 1

        arr[j+1] = x
    return [il_por, il_przes]

randomizeArray(A, 1000)
#print("Nieposortowana tablica: ", A)

out1 = bubbleSort(A)
#print("Bubble Sort wynik: ", A)
print("Ilosc operacji porownania: ", out1[0])
print("Ilosc operacji przestawienia: ", out1[1])

print("\n\n")
randomizeArray(A, 1000)
#print("Nieposortowana tablica: ", A)

out2 = insertionSort(A)
#print("Insertion Sort wynik: ", A)
print("Ilosc operacji porownania: ", out2[0])
print("Ilosc operacji przestawienia: ", out2[1])

ilosc_operacji_bubble = []
ilosc_operacji_insertion = []
ilosc_elementow_tablicy = []

for k in range(0, 500):
    B = []
    randomizeArray(B, k)
    out3 = bubbleSort(B)
    ilosc_operacji_bubble.append(out3[0])
    randomizeArray(B, k)
    out4 = insertionSort(B)
    ilosc_operacji_insertion.append(out4[0])
    ilosc_elementow_tablicy.append(k)



plt.plot(ilosc_elementow_tablicy, ilosc_operacji_bubble)
plt.plot(ilosc_elementow_tablicy, ilosc_operacji_insertion)
plt.xlabel("Ilosc elementow w tablicy")
plt.ylabel("Ilosc Operacji")
plt.legend(["Bubble Sort", "Insertion Sort"])
plt.savefig("sortowanie.png")