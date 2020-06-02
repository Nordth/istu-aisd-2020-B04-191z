#класс Node для определения элемента списка
class Node:
    def __init__(self, value = None, next = None, prev = None ):
        self.value = value
        self.next = next
        self.prev = prev
#класс Лист покупок
class ShopList:
    def __init__(self):
        self.head = None
        self.tail = None
        self.length = 0
    
    #вставить эллемент в конец списка    
    def add(self, x):
        self.length+=1
        if self.head == None:
            self.tail = self.head = Node(x)
        else:
            self.tail.next = self.tail = Node(x)
    
    
    #получить эллемент по индексу
    def getElemByIndex(self, index):
        if index < self.length:
            checkBox = self.head
            count = 0
            while count <= index:
                if count == index:
                    print(checkBox.value)
                count += 1
                checkBox = checkBox.next


    #вставка эллемента перед заданным индексом
    def addElemBeforeIndex(self, x, index):
        if self.head == None:
            self.tail = self.head = Node(x)
        if index < self.length:
            checkBox=self.head
            count = 0
            while count <= index:
                count += 1
                if count == index:
                   checkBox.next = Node(x, checkBox.next, checkBox.prev)
                checkBox = checkBox.next

    #удаление эллемента по значению
    def delByName(self, x):
        checkBox = self.head
        if checkBox is not None:
            if checkBox.value == x:
                self.head = checkBox.next
                checkBox = None
                print('True')
                return
        while checkBox is not None:
            if checkBox.value == x:
                break
            last = checkBox
            checkBox = checkBox.next
        if checkBox == None:
            print('False')
            return
        last.next = checkBox.next
        checkBox = None
        
                
       
    #вывести список на печать        
    def printList(self):
        if self.head != None:
            current = self.head
            out = 'Список \n' +current.value +'\n'
            while current.next != None:
                current = current.next
                out += current.value + '\n'
            print(out)
            
            
    #освобождение памяти
    def clear(self):
        self.__init__()
        
        

print("создаем  список для школы\n")
newList = ShopList()#создаем пустой список продуктов
newList.add('pen')# добавим в него ручку
newList.add('lastik')# добавим в него ластик
newList.add('note')# добавим в него тетрадь
newList.printList()#Выведем наш список на печать

print("добавим на 2 место в списке линейку\n")
newList.addElemBeforeIndex('ruler', 2)#добавим перед 2 эллементом в списке  линейку
newList.printList()#Выведем наш список на печать

print("выведем эллемент с индексом 1\n")
newList.getElemByIndex(1)

print("Удалим ручку и линейку из списка\n")
newList.delByName('pen')
newList.delByName('ruler')
newList.printList()#Выведем наш список на печать

print("Попробуем удалить несуществующий элемент\n")
newList.delByName('apple')

print("Полностью очистим наш список и добавим новый эллемент\n")
newList.clear()#удаляем список
newList.add('potato')
newList.printList()
