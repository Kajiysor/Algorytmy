import numpy as np

# ustawienie wartosci stalych

NMAX = 10
ELEMENT = 0
NEXT_POINTER = 1
PREVIOUS_POINTER = 2
EMPTY = -2
LIST_END = -1

queue = np.empty([NMAX, 3], dtype=int)  # tworzenie tablicy
for i in range(len(queue)):  # wypelnianie tablicy wartosciami poczatkowymi
    queue[i][ELEMENT] = 0
    queue[i][NEXT_POINTER] = EMPTY
    queue[i][PREVIOUS_POINTER] = EMPTY
head = 0
size = 0
cursor_list = []


def enqueue(elmt):
    global size
    global head
    if size == 0:
        queue[0][ELEMENT] = elmt
        queue[0][NEXT_POINTER] = head
        queue[0][PREVIOUS_POINTER] = head
        size += 1
    else:
        for i in range(NMAX):
            if queue[i][NEXT_POINTER] == EMPTY:
                empty_index = i
                break
        if size < NMAX:
            queue[empty_index][PREVIOUS_POINTER] = queue[head][PREVIOUS_POINTER]
            queue[queue[head][PREVIOUS_POINTER]
                    ][NEXT_POINTER] = empty_index
            queue[empty_index][ELEMENT] = elmt
            queue[empty_index][NEXT_POINTER] = head
            queue[head][PREVIOUS_POINTER] = empty_index
            size += 1
    print(f"Queued {elmt} to the queue")


def display():
    global cursor_list
    cursor_list.clear()
    next = head
    for i in range(size):
        cursor_list.append(queue[next][0])
        next = queue[next][NEXT_POINTER]
    print("==============")
    print("Current queue: ")
    print(cursor_list[::-1])
    print("==============")


def peek():
    if size == 0:
        raise Exception("Can't peek from empty queue!")
    global cursor_list
    cursor_list.clear()
    next = head
    for i in range(size):
        cursor_list.append(queue[next][0])
        next = queue[next][NEXT_POINTER]
    print(f"{cursor_list[0]} is the first element in the queue")


def dequeue():
    global size
    global head
    if size == 0:
        raise Exception("Can't dequeue from empty queue!")
    if size == 1:
        queue[head][NEXT_POINTER] = EMPTY
        queue[head][PREVIOUS_POINTER] = EMPTY
        size -= 1
    else:
        value = queue[head][ELEMENT]
        queue[queue[head][NEXT_POINTER]
                ][PREVIOUS_POINTER] = queue[head][PREVIOUS_POINTER]
        queue[queue[head][PREVIOUS_POINTER]
                ][NEXT_POINTER] = queue[head][NEXT_POINTER]
        queue[head][ELEMENT] = 0
        queue[head][PREVIOUS_POINTER] = EMPTY
        temp = queue[head][NEXT_POINTER]
        queue[head][NEXT_POINTER] = EMPTY
        head = temp
        size -= 1

    print(f"Element {value} was dequeued")


def main():
    enqueue(1)
    enqueue(2)
    enqueue(3)
    display()
    dequeue()
    dequeue()
    display()
    enqueue(4)
    enqueue(5)
    display()
    peek()


if __name__ == "__main__":
    main()
