package days6_10

import input10

fun day10(input: String): List<Int> =
    mutableListOf(1)
        .apply {
            input
                .split("\n")
                .forEach { line ->
                    line.split(" ").let {
                        when (it[0]) {
                            "noop" -> this.add(this.last())
                            "addx" -> {
                                this.add(this.last())
                                this.add(this.last() + it[1].toInt())
                            }
                        }
                    }
                }
        }

fun List<Int>.sliceAndStrength(intRange: Iterable<Int>): List<Int> =
    this.slice(intRange.map { it - 1 }).zip(intRange).map { it.first * it.second }

fun day10a(input: String): Int = day10(input).sliceAndStrength(listOf(20, 60, 100, 140, 180, 220)).sum()

fun day10b(input: String): String =
    mutableListOf<Char>()
        .apply {
            day10(input)
                .let {
                    for (n in it.indices) {
                        if (n % 40 in (it[n] - 1)..(it[n] + 1)) {
                            this.add('#')
                        } else {
                            this.add(' ')
                        }
                    }
                }
        }
        .dropLast(1)
        .joinToString("")
        .chunked(40)
        .joinToString("\n")

fun main(args: Array<String>) {
    println(day10a(input10))
    println(day10b(input10))
}