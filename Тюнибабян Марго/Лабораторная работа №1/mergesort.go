package main

import "fmt"

func merge(left []int,right []int) []int{
	//объединения списков
	lst:=make([]int,0)
	for len(left) > 0 && len(right) > 0{
		if left[0] < right[0]{
			lst = append(lst,left[0])
			left = left[1:]
		}else{
			lst = append(lst,right[0])
			right = right[1:]
		}
	}
	if len(left) > 0{
		lst = append(lst,left...)
	}
	if  len(right) > 0{
		lst = append(lst,right...)
	}

	return lst
}

func mergesort(lst []int) []int{
	//сортировка списка
	length:=len(lst)
	if length >= 2{
		mid := length/2
		lst = merge(mergesort(lst[:mid]),mergesort(lst[mid:]))
	}
	return lst
}

func main(){

	lst := []int{60,-9,32,2,1,876,9,4,11}
	lst = mergesort(lst)
	fmt.Println(lst)
}