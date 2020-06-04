arr = [78, 41, 4, 27, 3, 27, 8, 39, 19, 34, 6, 41, 13, 52, 16]

print("Исходный массив:", arr)

arr_size = len(arr)
for i in range(arr_size - 1):
    for j in range(arr_size - i - 1):  # обходим весь массив в двойном цикле
        if arr[j] > arr[j + 1]:  # если левый элемент больше правого, то меняем их местами
            arr[j], arr[j + 1] = arr[j + 1], arr[j]

print("Отсортированный массив:", arr)
