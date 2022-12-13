package days6_10

import inputs.input6

fun count(string: String): MutableCollection<Int> {
    val counter = hashMapOf<Char, Int>()
    string.forEach { counter[it] = counter.getOrDefault(it, 0) + 1 }
    return counter.values
}

fun day6(input: String): Pair<Int, String> =
    input
        .run {
            var n = 0
            do {
                val toTest = count(this.substring(n until n + 4))
                n += 1
            } while (toTest.any { it > 1 })

            return@run Pair(n + 3, this.substring(n + 3))
        }

fun day6a(input: String): Int = day6(input).first
fun day6b(input: String): Int =
    day6(input)
        .run {
            var m = 0
            do {
                val toTest = count(this.second.substring(m until m + 14))
                m += 1
            } while (toTest.any { it > 1 })

            return@run this.first + m + 13
        }

fun main(args: Array<String>) {
    println(day6a(input6))
    println(day6b(input6))
}