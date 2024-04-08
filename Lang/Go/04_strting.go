package main

import (
    "fmt"
    "strings"
)

func swap(a, b string) (string, string) {
    return b, a
}

func main() {
    // ----- strings 字符串操作 -----
    // 拼接
    var str = []string{"Hello", "World"}
    fmt.Println(strings.Join(str, " @ "))

    // 分割
    fmt.Println(strings.Split("Hello World! This is the first step on your programming journey!", " "))

    // 替换
    fmt.Println(strings.Replace("Hello World", "World", "Go", -1))

    // 去除字符串首尾空格
    fmt.Println(strings.Trim("  Hello World ", " "))

    // 比较
    fmt.Println(strings.Compare("Hello", "World"))

    // 大小写转换
    fmt.Println(strings.ToUpper("Hello"), strings.ToLower("World"))

    // 字符串判断（首、尾）
    fmt.Println(strings.HasPrefix("Hello", "He"), strings.HasSuffix("World", "ld"))
    
    // 索引
    fmt.Println(strings.LastIndex("Hello", "l"), strings.Index("World", "r"))

    // 重复
    fmt.Println(strings.Repeat("Hello ", 3))
}
