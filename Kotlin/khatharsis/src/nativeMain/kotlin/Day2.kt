import Day2.Jakenpon.Companion.fromString

class Day2 : DaySolver(2, "Rock Paper Scissors") {
    private val newData = data.dropLast(1)
        .map { it.split(' ') }

    override fun firstPart(): String {
        return newData.map { it.map { s -> fromString(s) } }
            .sumOf { it[1].battle(it[0]) }.toString()
    }

    override fun secondPart(): String {
        return newData.map {
            val first = fromString(it[0])
            when (it[1]) {
                "X" -> first to first.loseTo()
                "Y" -> first to first
                "Z" -> first to first.winTo()
                else -> throw Exception("This shouldn't happen, unknown value: $${it[1]}")
            }
        }
            .sumOf { it.second.battle(it.first) }.toString()
    }

    enum class Jakenpon(val score: Int) {
        ROCK(1), PAPER(2), SCISSOR(3);

        companion object {
            fun fromString(s: String) = when (s) {
                "A", "X" -> Jakenpon.ROCK
                "B", "Y" -> Jakenpon.PAPER
                "C", "Z" -> Jakenpon.SCISSOR
                else -> throw Exception("This shouldn't happen, unknown value: $s")
            }
        }

        fun battle(other: Jakenpon): Int = score + when {
            (other == this) -> 3
            (other == ROCK && this == PAPER) || (other == PAPER && this == SCISSOR) || (other == SCISSOR && this == ROCK) -> 6
            else -> 0
        }

        fun loseTo() = when (this) {
            ROCK -> SCISSOR
            SCISSOR -> PAPER
            PAPER -> ROCK
        }

        fun winTo() = when (this) {
            ROCK -> PAPER
            SCISSOR -> ROCK
            PAPER -> SCISSOR
        }
    }
}

class Day2Alternative : DaySolver(2, "Rock Paper Scissors - Alternative Version") {
    val newData = data.dropLast(1).map { it.split(' ') }
    val stringToInt = mapOf(
        "A" to 0,
        "B" to 1,
        "C" to 2,
        "X" to 0,
        "Y" to 1,
        "Z" to 2
    )

    override fun firstPart(): String =
        newData.map { it.map { s -> stringToInt[s]!! } }
            .sumOf {
                (when ((it[1] - it[0]).modulo(3)) {
                    0 -> 3
                    1 -> 6
                    else -> 0
                } + (it[1] + 1))
            }.toString()

    override fun secondPart(): String = newData.sumOf {
        stringToInt[it[0]]!!.let { first ->
            when (it[1]) {
                "X" -> 0 + (first - 1).modulo(3) + 1 // We Lose
                "Y" -> 3 + first + 1 // We tie
                "Z" -> 6 + (first + 1).modulo(3) + 1// We win
                else -> throw Exception("This shouldn't happen, unknown value: $${it[1]}")
            }
        }
    }.toString()
}