
package main

import (
    "fmt"
)

func fibonacci(n int) int {
    if n == 0 {
        return 1
    }
    if n == 1 {
        return 1
    }
    return fibonacci(n-1) + fibonacci(n-2)
}

func main() {
    for i := 0; i < 10; i++ {
        fmt.Println(fibonacci(i))
    }
}

