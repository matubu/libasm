#!/bin/sh
//usr/bin/env go run $0; exit

package main

import (
	"fmt"
	"time"
)

const LEN = 10000

func main() {
	start := time.Now()

	for j := 0; j < 100; j++ {
		var arr [LEN]int
		for i := range arr {
			arr[i] = i * 2
		}

		fmt.Printf("[0]=%d\n", arr[0])
		fmt.Printf("[1]=%d\n", arr[1])
		fmt.Printf("[%d]=%d\n", LEN-1, arr[LEN-1])
	}

	elapsed := time.Since(start)
	fmt.Printf("Array: %s", elapsed)
}
