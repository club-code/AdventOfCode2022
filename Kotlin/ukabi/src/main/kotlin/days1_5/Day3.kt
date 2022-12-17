package days1_5

import inputs.input3

fun day3a(input: String): Int =
    input
        .split("\n")
        .map {
            val len = it.length / 2

            Pair(it.substring(0 until len), it.substring(len until it.length))
        }
        .map { sack -> sack.first.forEach { if (sack.second.contains(it)) return@map it } }
        .filterIsInstance<Char>()
        .sumOf { if (it.isLowerCase()) it.minus('a') + 1 else it.minus('A') + 27 }

fun day3b(input: String): Int =
    input
        .split("\n")
        .chunked(3)
        .map { group ->
            group
                .map { it.toSet() }
                .reduce { s1, s2 -> s1.intersect(s2) }
                .toList().first()
        }
        .sumOf { if (it.isLowerCase()) it.minus('a') + 1 else it.minus('A') + 27 }

fun main(args: Array<String>) {
    println(day3a(input3))
    println(day3b(input3))
}