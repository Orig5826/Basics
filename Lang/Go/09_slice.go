
package main

import (
    "fmt"
)

func main() {
    var s []int
    print_slice(s)

    s = append(s, 1)
    print_slice(s)

    s = append(s, 2,3,4,5,6)
    print_slice(s)

    print_slice(s[:0])
    print_slice(s[:4])
    print_slice(s[2:4])
}

func print_slice(x []int) {
    // 切片长度（len）和容量（cap）
    // 区别：
    // 长度：表示当前切片中已经存储的元素数量
    // 容量：表示当前切片可以容纳的最大元素数量
    // 
    // 1. len: 当前切片/数组元素的个数
    // 2. cap: 当前切片开始位到最后一个元素的个数
    fmt.Printf("len=%d cap=%d slice=%v\n", len(x), cap(x), x)
}
