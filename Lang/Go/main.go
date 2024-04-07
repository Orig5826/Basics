package main

import (
   "fmt"    // 导入格式化输出模块
   "module_test/mypackage"     // 导入当前目录下的模块
)

// 测试
func main() {
   // fmt.Println("Hello, World!")
   fmt.Println("Hello" + " World!")

   // 调用模块
   fmt.Println(mypackage.Add(1,2))
}
