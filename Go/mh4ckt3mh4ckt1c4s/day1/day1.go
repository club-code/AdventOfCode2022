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
	var temp int64
	for scanner.Scan() {
		line := scanner.Text()
		if line == "" {
			if sum >= maxSum {
				winner = current
				maxSum = sum
				temp = 0
			}
			current++
			sum = 0
			temp = 0
		} else {
			temp, _ = strconv.ParseInt(line, 10, 32)
		}
	}
	fmt.Println("Winner is %i with %i calories", winner, maxSum)

}
