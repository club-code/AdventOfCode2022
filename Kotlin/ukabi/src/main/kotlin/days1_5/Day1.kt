package days1_5

import inputs.input1

fun day1(input: String, n: Int): Int =
    input
        .split("\n\n")
        .map { sup -> sup.split("\n").sumOf { it.toInt() } }
        .sortedByDescending { it }
        .subList(0, n)
        .sum()

fun main(args: Array<String>) {
    println(day1(input1, 1))
    println(day1(input1, 3))
}