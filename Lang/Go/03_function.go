/**
# 闭包
## 理解
闭包是指有权访问另一个函数作用域中变量的函数，创建闭包的最常见的方式就是在一个函数内创建另一个函数，创建的函数可以访问到当前函数的局部变量。

## 优缺点
优点：可以读取其他函数内部的变量，并将其一直保存在内存中
缺点：可能会造成内存泄漏或溢出。

## 用途
1. 【封装】使我们在函数外部能够访问到函数内部的变量。可使用这种方法来创建私有变量。
2. 【缓存】闭包的另一个用途是使已经运行结束的函数上下文中的变量对象继续留在内存中，因为闭包函数保留了这个变量对象的引用，所以这个变量对象不会被回收。
*/
package main

import "fmt"

// 闭包
func get_seq() func() int {
    i := 0

    return func() int {
        i += 1

        return i
    }
}

func main() {
    next_number := get_seq()
    fmt.Println(next_number())
    fmt.Println(next_number())
    fmt.Println(next_number())

    next_number2 := get_seq()
    fmt.Println(next_number2())
    fmt.Println(next_number2())
}
