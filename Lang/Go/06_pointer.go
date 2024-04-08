
package main

import (
    "fmt"
)


func main() {
    var p *int
    fmt.Println(p)	// 空指针 nil

    var data int = 20
    fmt.Println(&data)	// 地址

    p = &data
    fmt.Println(p)
    fmt.Println(*p)

    a := 3
    b := 4
    fmt.Println(a, b)
    swap(&a, &b)
    fmt.Println(a, b)
}

func swap(x *int, y *int) {
    *x, *y = *y, *x
}