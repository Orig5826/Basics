/*
通道：
    0. ch <- data          // 向ch中发送数据
    1. data := <-ch        // 阻塞接收：等待ch有数据，然后取到数据赋值给data
    2. data, ok := <-ch    // 完整写法：ok为bool类型，true表示有数据，false表示无数据
    3. <-ch                // 忽略接收数据

应用：
1. 竞争选举（多通道，有满足条件的就执行。多个都满足就随机选一个执行）
2. 超时处理（保证不阻塞）
3. 阻塞判断
*/
package main

import (
    "fmt"
    "time"
)

func main() {
    demo_01()
    demo_02()
}

func demo_01() {
    fmt.Println("----- demo_01 start -----")
    ch1 := make(chan int)
    ch2 := make(chan int)

    go func() {
        var sum int = 0
        for i := 0; i < 100; i++ {
            sum += i
        }
        ch1 <- sum
    }()

    go func() {
        time.Sleep(time.Second * 2)
        ch1 <- 1
    }()

    // select 语句
    // 1. 本质上，相当于监听多个channel，当有数据到来时，就执行相应的case语句
    // 2. 随机选择一个case语句执行，如果所有的case语句都不满足条件，则执行default语句。
    // 3. 如果default语句不存在，则select语句会阻塞等待数据到来
    select {
    case v1 := <- ch1:
        fmt.Println("v1 =", v1)
        break
    case v2 := <- ch2:
        fmt.Println("v2 =", v2)
    case <- time.After(time.Second * 10):
        fmt.Println("timeout")
    default:
       fmt.Println("default")
    }

    fmt.Println("main exit.")

    // 如果需要main阻塞，则可以使用select语句
    // select {}
    // 
    // 可以对比下使用for {}的阻塞时的CPU占用情况
}


func demo_02() {
    fmt.Println("----- demo_02 start -----")
    ch3 := make(chan int, 5)

    go func() {
        time.Sleep(time.Second)
        for {
            ch3 <- 5
            time.Sleep(time.Second * 5)
        }
    }()

    // 生成者速度大于消费者速度，因此会触发default
    for {
        select {
        case ch3 <- 1:
            fmt.Println("add succeed")
            time.Sleep(time.Second)
        default:
            fmt.Println("资源不足")
            time.Sleep(time.Second)
        }
    }

    fmt.Println("main exit.")
}