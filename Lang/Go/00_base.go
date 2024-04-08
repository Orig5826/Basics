
package main

import "fmt"

func main() {
    // 变量
    var a int = 10
    fmt.Println(a)

    b := 10
    fmt.Println(b)

    x,y := 128, "back to home"
    fmt.Println(x, y)

    // 常量
    const length int = 10
    fmt.Println(length * 5)

    // 类型转换
    var a1 float32 = 10.5
    var a2 int = int(a1)
    fmt.Println(a2)

    // 类型推断
    var a3 = 10
    fmt.Println(a3)

    // 运算符
    // 算术运算符
    var b1, b2 = 3,4
    fmt.Println(b1 + b2)
    fmt.Println(b1 - b2)
    fmt.Println(b1 * b2)
    fmt.Println(b1 / b2)
    fmt.Println(b1 % b2)

    // 关系运算符
    if b1 > b2 {
        fmt.Println("b1 > b2")
    } else if b1 < b2 {
        fmt.Println("b1 < b2")
    } else {
        fmt.Println("b1 == b2")
    }

    // 逻辑运算符
    var d = true
    var e = false
    if d && e {
        fmt.Println("d && e == true")
    } else {
        fmt.Println("d && e == false")
    }
    
    if !e {
        fmt.Println("!e")
    }

    // 位运算符
    var f = 10
    var g = 12
    fmt.Println(f & g)
    fmt.Println(f | g)
    fmt.Println(f ^ g)
    fmt.Println(f << 2)
    fmt.Println(f >> 2)

    // 赋值运算符

    // 指针
    var ptr *int = &a3
    fmt.Println(*ptr)
}
