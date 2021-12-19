
class Node:

    def __init__(self, data):
        self.data = data
        self.next = None
        self.prev = None


class Queue:

    def __init__(self):
        self.head = Node("head")
        self.tail = Node("tail")
        self.head.next = self.tail
        self.tail.prev = self.head
        self.size = 0

    def enqueue(self, data):
        node = Node(data)
        if self.tail.prev == self.head:
            self.head.next = self.tail.prev = node
            node.next = self.tail
            node.prev = self.head
            self.size += 1
        else:
            node.prev = self.tail.prev
            self.tail.prev.next = node
            self.tail.prev = node
            node.next = self.tail
            self.size += 1

    def dequeue(self):
        if self.isEmpty():
            raise Exception("Can't dequeue from empty queue!")
        #popped_item = self.head.next
        dequeued = self.head.next
        self.head.next = dequeued.next
        dequeued.next.prev = self.head
        if self.head.next == self.tail:
            self.tail.prev = self.head
        print(f"Dequeued {dequeued.data} from the queue")

    def peek(self):
        if self.isEmpty():
            raise Exception("Can't peek from empty queue!")
        print(f"{self.head.next.data} is the first element in the queue")

    def getSize(self):
        return self.size

    def isEmpty(self):
        return self.size == 0

    def display(self):
        current = self.tail.prev
        print("==============")
        print("Current queue: ")
        print("==============")
        while current != self.head:
            print(current.data)
            current = current.prev
        print("==============")


if __name__ == "__main__":
    queue = Queue()
    for i in range(11):
        queue.enqueue(i)
    queue.display()

    for _ in range(1, 6):
        queue.dequeue()
    queue.display()

    queue.peek()
