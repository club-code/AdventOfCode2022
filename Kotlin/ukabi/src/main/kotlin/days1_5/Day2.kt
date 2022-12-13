package days1_5

import input2

fun playScore(play: String): Int = when(play) {
    "A" -> 1
    "B" -> 2
    "C" -> 3
    else -> 0
}

fun roundScore(round: Pair<String, String>): Int = playScore(round.second) + when (round.first) {
    round.second -> 3
    "A" -> if (round.second == "B") 6 else 0
    "B" -> if (round.second == "C") 6 else 0
    "C" -> if (round.second == "A") 6 else 0
    else -> 0
}

fun roundChoice(round: Pair<String, String>): Int = when (round.second) {
    "A" -> roundScore(
        Pair(
            round.first,
            when (round.first) {
                "A" -> "C"
                "B" -> "A"
                "C" -> "B"
                else -> ""
            }
        )
    )
    "B" -> roundScore(Pair(round.first, round.first))
    "C" -> roundScore(
        Pair(
            round.first,
            when (round.first) {
                "A" -> "B"
                "B" -> "C"
                "C" -> "A"
                else -> ""
            }
        )
    )
    else -> 0
}

fun day2(input: String): List<Pair<String, String>> {
    return input
        .replace("X", "A")
        .replace("Y", "B")
        .replace("Z", "C")
        .split("\n")
        .map { line -> line.split(" ").let { Pair(it[0], it[1]) } }
}

fun day2a(input: String): Int = day2(input).sumOf { roundScore(it) }
fun day2b(input: String): Int = day2(input).sumOf { roundChoice(it) }

fun main(args: Array<String>) {
    println(day2a(input2))
    println(day2b(input2))
}