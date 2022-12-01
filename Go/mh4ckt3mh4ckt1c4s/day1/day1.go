// @Title
// @Description
// @Author
// @Update

package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
)

func main() {
	f, err := os.Open("input.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer f.Close()

	// int winner = -1
	scanner := bufio.NewScanner(f)

	winner := -1
	maxSum := -1
	sum := 0
	current := 1
	for scanner.Scan() {
		line := scanner.Text()
		if line == "" {
			if sum >= maxSum {
				winner = current
				maxSum = sum
			}
			current++
			sum = 0
		} else {
			var temp int64
			temp, _ = strconv.ParseInt(line, 10, 32)
			sum += int(temp)
		}
	}
	fmt.Printf("Winner is %d with %d calories", winner, maxSum)

}
