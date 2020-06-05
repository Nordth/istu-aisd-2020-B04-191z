arr=[9,8,7,6,5,4,3,2,1,0,3,5,7,2,0]
n = len(arr)

print(arr)

for k in range(1,n):
    minElementIndex = k-1
    for i in range(k-1,n):
        if(arr[minElementIndex] > arr[i]):
            minElementIndex = i
        i=i+1
    t = arr[minElementIndex]
    arr[minElementIndex] = arr[k-1]
    arr[k-1] = t
    k=k+1

print(arr)
        
