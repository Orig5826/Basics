
# Go

## 基础

### Hello world
main.go文件内容如下：
```go
// ------------------------------
// 示例1
package main

import "fmt"

// { 不能单独一行，否则报错
func main(){
   fmt.Println("Hello, World!")
}

// ------------------------------
// 示例2
package main

import (
   . "fmt"
)

// { 不能单独一行，否则报错
func main(){
   Println("Hello" + " World!")
}

```

```bash
# 执行代码
go run ./main.go

# 如有需要可编译成二进制文件
go build ./main.go
```

### 包管理
引入相对路径的包
```bash
module_test
   └─main.go
   └─go.mod
   └─mypackage
      └─mypackage.go
```

go.mod文件内容如下：
```go
module module_test
```

mypackage.go文件内容如下：
```go
package mypackage

func Add(a, b int) int {
	return a + b
}
```

main.go文件内容如下：
```go
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
```