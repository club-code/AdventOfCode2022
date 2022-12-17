package days1_5

import inputs.input5
import transpose

fun day5(input: String): Pair<List<MutableList<String>>, List<List<Int>>> =
    input
        .split("\n\n")
        .let { group ->
            Pair(
                transpose(
                    group[0]
                        .split("\n")
                        .asReversed()
                        .drop(1)
                        .map { it.split("") }
                )
                    .filterNot { "[ ]".contains(it[0]) }
                    .map { stack -> stack.dropLastWhile { it == " " }.toMutableList() },

                group[1]
                    .split("\n")
                    .map { line ->
                        line
                            .split(" ")
                            .filter { it.matches(Regex("""\d+""")) }
                            .map { it.toInt() }
                    }
            )
        }

fun day5a(input: String): String =
    day5(input)
        .run {
            this.second
                .forEach {
                    val n = it[0]
                    val from = it[1] - 1
                    val to = it[2] - 1

                    for (i in 1..n) {
                        val toTransfer = this.first[from].removeLast()
                        this.first[to].add(toTransfer)
                    }
                }

            return@run this.first.joinToString(""){ it.last() }
        }

fun day5b(input: String): String =
    day5(input)
        .run {
            this.second
                .forEach {
                    val n = it[0]
                    val from = it[1] - 1
                    val to = it[2] - 1
                    for (i in 1..n) {
                        val toTransfer = this.first[from].run { this.removeAt(this.size - n + i - 1) }
                        this.first[to].add(toTransfer)
                    }
                }

            return@run this.first.joinToString(""){ it.last() }
        }

fun main(args: Array<String>) {
    println(day5a(input5))
    println(day5b(input5))
}