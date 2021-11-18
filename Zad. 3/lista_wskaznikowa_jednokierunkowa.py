class Node:  
    def __init__(self,data):  
        self.data = data  
        self.next = None
          
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
                self.tail = newNode
                self.size += 1
        else:
            current = self.head
            newNode = Node(element)
            for i in range(index-1):
                current = current.next
            tmp = current.next
            current.next = newNode
            newNode.next = tmp
            self.size += 1

            
    def remove_element(self, element):
        print(f"Removing element: {element}")
        current = self.head
        if (self.head == None):
            print("List is empty")
            return
        elif self.head.next == None:
            self.head = None 
            self.tail = None 
            self.size = 0
        else:
            while (current != None):
                if (current.next.data == element):
                    current.next = current.next.next
                    return
                current = current.next

    def remove_index(self, index = -1):
        print(f"Removing element from index: {index}")
        current = self.head
        if(self.head == None):
            print("List is empty")
            return
        elif self.head.next == None:
            self.head = None 
            self.tail = None 
            self.size = 0
        elif (index > self.size or index == -1):
            while (current != None):
                if (current.next == self.tail):
                    current.next = None
                    self.tail = current
                    return
                current = current.next
        else:
            for i in range(index-1):
                current = current.next
            current.next = current.next.next

 
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
        current = self.head; 
        if(self.head == None):  
            print("List is empty"); 
            return;  
        while(current != None):  
            print(current.data),  
            current = current.next; 
        print ("")

    def contains(self, element):
        print(f"Checking if list contains element: {element}")
        current = self.head
        if(self.head == None):
            print("List is empty")
            return
        while (current != None):
            if current.data == element:
                print(f"Element {current.data} is in the list")
                return
            current = current.next
        print(f"List does not contain element: {element}")


def main():
    sList = List();  
             
    sList.add(9);  
    sList.add(7);  
    sList.add(2);  
    sList.add(5);  
    sList.add(4);  
     
    print("Original list: ");  
    sList.display();  
     
    sList.sort();  
      
    print("Sorted list: ");  
    sList.display();

    sList.contains(9)
    sList.add(77, 11)
    sList.display()
    sList.remove_index(33)
    sList.display()

if __name__ == "__main__":
    main()