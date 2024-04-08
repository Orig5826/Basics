
package main

import (
    "fmt"
    "math"
)

type Shape interface {
    area() float64
}

type Circle struct {
    radius float64
}

type Rectangle struct {
    width, height float64
}

func (circle Circle) area() float64 {
    return math.Pi * circle.radius * circle.radius
}

func (rect Rectangle) area() float64 {
    return rect.width * rect.height
}

func getArea(shape Shape) float64 {
    return shape.area()
}


func main() {
    circle := Circle{10}
    rectangle := Rectangle{4, 5}
    fmt.Println("Circle area is", getArea(circle))
    fmt.Println("Rectangle area is", getArea(rectangle))
}

