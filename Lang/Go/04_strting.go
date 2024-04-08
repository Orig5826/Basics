package main

import (
    "fmt"
    "strings"
)

func main() {
    // 字符串拼接
    var str = []string{"Hello", "World"}
    fmt.Println(strings.Join(str, " @ "))
}
