class Node:  
    def __init__(self,data):  
        self.data = data  
        self.next = None
        self.prev = None
          
class List:    
    def __init__(self):  
        self.head = None 
        self.tail = None 
        self.size = 0
          

    def add(self, element, index = -1):
        print(f"Adding element: {element} on the index: {index} of the list")   
        newNode = Node(element) 
        if (index == -1 or index > self.size): 
            if(self.head == None):  
                self.head = newNode 
                self.tail = newNode 
                self.size += 1 
            else:  
                self.tail.next = newNode
                newNode.prev = self.tail 
                self.tail = newNode
                self.size += 1
        else:
            current = self.head
            newNode = Node(element)
            for i in range(index):
                current = current.next
            newNode.next = current
            newNode.prev = current.prev
            current.prev.next = newNode
            current.prev = newNode
            self.size += 1


    def remove_element(self, element):
        print(f"Removing element: {element}")
        current = self.head
        if (self.head == None):
            print("ERROR: List is empty")
            return
        elif self.head.next == None:
            self.head = None 
            self.tail = None 
            self.size = 0
        else:
            while (current != None):
                if (current.data == element):
                    current.prev.next = current.next
                    if current.next:
                        current.next.prev = current.prev
                    return
                current = current.next
            print(f"ERROR: There is no element: {element} in the list")


    def remove_index(self, index = -1):
        print(f"Removing element from index: {index}")
        current = self.head
        if(self.head == None):
            print("ERROR: List is empty")
            return
        elif self.head.next == None:
            self.head = None 
            self.tail = None 
            self.size = 0
        elif (index > self.size or index == -1):
            self.tail = self.tail.prev
            self.tail.next = None
        else:
            for i in range(index):
                current = current.next
            current.prev.next = current.next
            current.next.prev = current.prev

 
    def sort(self):
        print("Sorting the list")   
        current = self.head  
        index = None  
          
        if(self.head == None):  
            return 
        else:  
            while(current != None):  
                index = current.next;  
                  
                while(index != None):  
                    if(current.data > index.data):  
                        temp = current.data  
                        current.data = index.data  
                        index.data = temp 
                    index = index.next 
                current = current.next 


    def display(self):
        temp_list = []  
        current = self.head; 
        if(self.head == None):  
            print("ERROR: List is empty"); 
            return;  
        while(current != None):  
            temp_list.append(current.data)  
            current = current.next;
        print (temp_list, end="\n\n")
        temp_list.clear()


    def contains(self, element):
        print(f"Checking if list contains element: {element}")
        current = self.head
        if(self.head == None):
            print("ERROR: List is empty")
            return
        while (current != None):
            if current.data == element:
                print(f"Element {current.data} is in the list")
                return
            current = current.next
        print(f"ERROR: List does not contain element: {element}")


def main():
    lista = List();  
             
    lista.add(9);  
    lista.add(7);  
    lista.add(2);  
    lista.add(5);  
    lista.add(4);  
     
    print("Original list: ");  
    lista.display();  
     
    lista.sort();  
      
    print("Sorted list: ");  
    lista.display();

    lista.contains(9)
    lista.add(77, 2)
    lista.display()
    lista.remove_index(3)
    lista.display()
    lista.remove_element(9)
    lista.display()
    lista.remove_element(33)

if __name__ == "__main__":
    main()