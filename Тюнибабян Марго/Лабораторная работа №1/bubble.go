package main

import "fmt"

func main() {
	ar := []int{76, 3, 0, -21, 21, 5, 90}
	BubbleSort(ar)
	fmt.Println(ar)
}

func BubbleSort(ar []int) {
	for i := 0; i < len(ar); i++ {
		for j := i; j < len(ar); j++ {
			if ar[i] > ar[j] {
				swap(ar, i, j)
			}
		}
	}
}

func swap(ar []int, i, j int) {
	tmp := ar[i]
	ar[i] = ar[j]
	ar[j] = tmp
}
