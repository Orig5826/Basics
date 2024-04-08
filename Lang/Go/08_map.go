
package main

import (
    "fmt"
)

func main() {
    countryMap := map[string] string{"India":"New Delhi", "France":"Paris", "Japan":"Tokyo", "Italy":"Rome"}
    for key, value := range countryMap {
        fmt.Println(key, ":", value)
    }
    delete(countryMap, "Japan")
    fmt.Println("----- After deleting Japan -----")
    for k := range countryMap {
        fmt.Println(k, " : ",countryMap[k])
    }
}
