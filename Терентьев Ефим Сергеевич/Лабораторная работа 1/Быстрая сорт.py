def quicksort(nums, fst, lst):
   if fst >= lst: return
 
   i, j = fst, lst
   pivot = nums[round((lst - fst) / 2 + fst)]
 
   while i <= j:
       while nums[i] < pivot: i += 1
       while nums[j] > pivot: j -= 1
       if i <= j:
           nums[i], nums[j] = nums[j], nums[i]
           i, j = i + 1, j - 1
   quicksort(nums, fst, j)
   quicksort(nums, i, lst)
   print (nums)
read_arr = input("Введите массив: ")
arr= read_arr.split()
print (arr)
new_arr = quicksort(arr,0,len(arr)-1)
