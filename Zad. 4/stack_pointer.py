
class Node:

    def __init__(self, data):
        self.data = data
        self.next = None


class Stack:

    def __init__(self):
        self.head = Node("head")
        self.size = 0

    def push(self, data):
        node = Node(data)
        node.next = self.head.next
        self.head.next = node
        self.size += 1

    def pop(self):
        if self.isEmpty():
            raise Exception("Can't pop from empty stack!")
        popped_item = self.head.next
        self.head.next = self.head.next.next
        self.size -= 1
        print(f"Popped {popped_item.data} from stack")

    def peek(self):
        if self.isEmpty():
            raise Exception("Can't peek from empty stack!")
        print(f"{self.head.next.data} is on top of the stack")

    def getSize(self):
        return self.size

    def isEmpty(self):
        return self.size == 0

    def display(self):
        current = self.head.next
        print("==============")
        print("Current stack: ")
        print("==============")
        while current:
            print(current.data)
            current = current.next
        print("==============")


if __name__ == "__main__":
    stack = Stack()
    for i in range(11):
        stack.push(i)
    stack.display()

    for _ in range(1, 6):
        stack.pop()
    stack.display()

    stack.peek()
