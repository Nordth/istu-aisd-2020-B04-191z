stack = []#инициализация стека

#вставка эллементов на вершину стека
stack.append(1)
stack.append(2)
stack.append(3)

print(stack)

#клонирование списка

sec_stack = stack[:]

#извлечение эллементов с вершины стека
length = len(stack)
while length > -2:
    if length <= 0:
        print("false\n")
        break
    else:
        stack.pop()
        print("true\n")
    length -= 1
    

print(sec_stack)

#удаление стека
sec_stack.clear()
print(sec_stack)