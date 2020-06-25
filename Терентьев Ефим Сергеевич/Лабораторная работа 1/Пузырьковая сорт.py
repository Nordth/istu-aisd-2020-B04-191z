def bSort(array):
    length = len(array)
    for i in range(length):
        for j in range(0, length-i-1):
            if array[j] > array[j+1]:
                temp = array[j]
                array[j] = array[j+1]
                array[j+1] = temp
    return array
read_arr = input("Введите массив: ")
arr= read_arr.split()
print (arr)
new_arr = bSort(arr)
print (new_arr) 