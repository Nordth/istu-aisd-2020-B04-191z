def merge(left, right):
    result = []
    i, j = 0, 0

    # добавляем наименьшие элементы в результирующий массив
    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1

    # добавляем оставшиеся элементы в результирующий массив
    while i < len(left):
        result.append(left[i])
        i += 1
    while j < len(right):
        result.append(right[j])
        j += 1
    return result


def merge_sort(arr):
    if len(arr) < 2:
        return arr  # базовый случай
    else:
        middle = int(len(arr) / 2)
        left = merge_sort(arr[:middle])
        right = merge_sort(arr[middle:])
        return merge(left, right)


array = [78, 41, 4, 27, 3, 27, 8, 39, 19, 34, 6, 41, 13, 52, 16]

print("Исходный массив:", array)
print("Отсортированный массив:", merge_sort(array))
