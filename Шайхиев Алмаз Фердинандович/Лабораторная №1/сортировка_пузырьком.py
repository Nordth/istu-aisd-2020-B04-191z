#сортировка пузырьком
from random import randint
 
N = 5
a = []
for i in range(N):
    a.append(randint(1, 99))
print("Начальный массив:")
print(a)
 
print("Соритровка массива:") 
for i in range(N-1):
    for j in range(N-i-1):
        if a[j] > a[j+1]:
            a[j], a[j+1] = a[j+1], a[j]
    print(a)

print("Отсортированный массив:") 
print(a)