/**
在Go语言中，数组是一个长度固定的数据类型，而切片则是一个长度可变的数据类型。

// Array 数组是具有特定固定大小的数据类型，必须在定义时指定大小。
var array[10] int

// Slice 切片则是一个长度可变的数据类型，可以根据需要动态增减。
var array = []int{0,1,2,3,4,5,6,7,8,9}

数组和切片的主要区别在于：
1. 数组的长度是固定的，而切片的长度是可变的。
2. 数组可以通过索引直接访问元素，而切片则需要通过下标访问。
3. 数组不能扩展，而切片可以通过 append() 方法进行扩展。

注意：
在Go语言中，数组是值类型，而切片则是引用类型。
这意味着当您将一个数组赋值给另一个变量时，实际上是复制了整个数组，
而当您将一个切片赋值给另一个变量时，只是复制了引用（地址）。
*/
package main

import (
    "fmt"
)

// 在 Go 语言中，数组的大小是类型的一部分，因此不同大小的数组是不兼容的
// 因此传递数组给函数时，需要指定数组的大小
func average(array [10]int, size int) float64 {
    var sum int = 0
    for _, v := range array {
        sum += v
    }
    return float64(sum)/float64(size)
}

func main() {
    var array[10] int
    // var array = []int{0,1,2,3,4,5,6,7,8,9}

    for i := 0; i < len(array); i++ {
        array[i] = i
    }
    fmt.Printf("average = %f\n", average(array, len(array)))

    var sum int = 0
    for _, v := range array {
        sum += v
    }
    fmt.Printf("sum = %d\n", sum)

    // 二维数组
    var m = [2][3]int {{0,1,2}, {3,4,5}}
    for i := 0; i < len(m); i++ {
        for j := 0; j < len(m[i]); j++ {
            fmt.Printf("a[%d][%d] = %d\n", i, j, m[i][j])
        }
    }
}
