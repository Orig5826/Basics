package main

import (
   "fmt" 
)

// 测试
func main() {
    var cnt = 10
    for cnt > 0 {
        fmt.Printf("%d ", cnt)
        cnt--
    }
    fmt.Println()

    for i := 0; i < 10; i++ {
        fmt.Printf("%d ", i)
    }
    fmt.Println()

    for i, v := range "hello" {
        fmt.Printf("%d %c\n", i, v)

        if i == 3 {
            goto done
        }
    }
    fmt.Println()

done:
    cnt = 0
    for cnt < 20 {
        cnt++
        if cnt % 3 == 0{
            continue
        }

        fmt.Printf("%d ", cnt)
        if cnt >= 10{
            break
        }
    }
    fmt.Println()

    // 测试switch
    for i := 0; i < 10; i++ {
        // [与C区别] 默认带break
        // 如果不需要，则使用fallthrough
        switch i {
            case 2:
                fmt.Println("[i is 2] ")
            case 3:
                fmt.Println("[i is 3] ")
            case 6:
                fmt.Println("<i is 6> ")
                fallthrough
            case 5:
                fmt.Println("-> 555")
            default:
                fmt.Printf("%d ", i)
        }
    }
}
