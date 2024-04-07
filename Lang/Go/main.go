package main

import (
   "fmt"
)

type Person struct {
   name string
   age int
}

// 测试
func main() {
   fmt.Println("Hello" + " World!")

   var name string = "Tom"
   fmt.Println(name)

   a := "LiLei"      // 声明并赋值，自动推断类型。等价于 var a string = "LiLei"
   fmt.Println(a)

   // var array [5]int
   // var array = [5]int{5,6,7,8,9}
   array := [5]int{5,6,7,8,9}
   // 数组元素遍历
   for i := 0; i < len(array); i++ {
      // fmt.Println(array[i])
      fmt.Printf("%d ", array[i])
   }
   fmt.Println()

   // 切片
   // slice := make([]int, 3)    // 声明切片，并初始化为3。初始值0
   slice := array[2:4]
   for i := 0; i < len(slice); i++ {
      fmt.Printf("%d ", slice[i])
   }
   fmt.Println()

   // 结构体
   var person Person
   person.name = "Tom"
   person.age = 18
   fmt.Println(person)

   // range
   for i, v := range array {
      fmt.Printf("{%d,%d}\n", i, v)
   }

   // map
   m := make(map[string]int)
   m["Tom"] = 18
   m["Jerry"] = 19
   fmt.Println(m)
   // 遍历map, 遍历key
   for key := range m {
      // fmt.Printf("key: %s, value: %d\n", key, m[key])
      fmt.Printf("key: %s\n", key)
   }
   // 遍历map, 遍历value
   for _, value := range m {
      fmt.Printf("value: %d\n", value)
   }
}
