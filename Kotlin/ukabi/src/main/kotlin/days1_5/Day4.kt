package days1_5

import inputs.input4

fun day4(input: String): List<Pair<IntRange, IntRange>> =
    input
        .split("\n")
        .map { pair ->
            pair
                .split(",")
                .map { assignation ->
                    assignation
                        .split("-")
                        .map { it.toInt() }
                        .let { it[0]..it[1] }
                }
                .let { Pair(it[0], it[1]) }
        }

fun day4a(input: String): Int =
    day4(input)
        .filter {
            val firstDiff = it.first.first - it.second.first
            val lastDiff = it.first.last - it.second.last

            return@filter ((firstDiff <= 0) and (lastDiff >= 0)) or ((firstDiff >= 0) and (lastDiff <= 0))
        }
        .size

fun day4b(input: String): Int =
    day4(input)
        .map { (it.first.toSet()).intersect(it.second.toSet()) }
        .filter { it.isNotEmpty() }
        .size

fun main(args: Array<String>) {
    println(day4a(input4))
    println(day4b(input4))
}