arr = []
arr_length = int(input("Введите длину массива: "))

for i in range(arr_length):
    temp = input(f"Введите {i + 1} элемент: ")
    arr.append(int(temp))

print("Исходный массив:", arr)

arr_size = len(arr)
for i in range(arr_size - 1):
    for j in range(arr_size - i - 1):  # обходим весь массив в двойном цикле
        if arr[j] > arr[j + 1]:  # если левый элемент больше правого, то меняем их местами
            arr[j], arr[j + 1] = arr[j + 1], arr[j]

print("Отсортированный массив:", arr)
