package days11_15

import input11
import kotlin.properties.Delegates

class Monkey(private val items: MutableList<Long>, private val operation: (Long) -> Long, private val test: Long, private val ifTrue: Int, private val ifFalse: Int) {
    private lateinit var monkeys: List<Monkey>
    private var lcm by Delegates.notNull<Long>()
    var interactions: Long = 0

    fun setMonkeysSet(monkeys: List<Monkey>) { this.monkeys = monkeys }

    fun setLcm() { this.lcm = this.monkeys.map { it.test }.reduce { acc, i -> acc * i } }

    fun inspect(divisor: Int) {
        while (items.isNotEmpty()) {
            var item = items.removeAt(0)
            item = operation(item).floorDiv(divisor) % this.lcm

            this.interactions += 1

            val toTransfer = if (item % this.test == 0L) ifTrue else ifFalse
            this.monkeys[toTransfer].items.add(item)
        }
    }

    companion object {
        fun of(group: String): Monkey =
            group
                .split("\n")
                .zip(listOf("""\d+""", """(\d+(, )?)+""", """(?<== )[\w *+\/-]+""", """\d+""", """\d+""", """\d+"""))
                .map { it.second.toRegex().find(it.first)!!.value }
                .run {
                    val items = this[1].split(", ").map { it.toLong() }.toMutableList()
                    val operation = this[2]
                        .split(" ")
                        .run {
                            val operation = when (this[1]) {
                                "+" -> { x: Long, y: Long -> x + y }
                                "*" -> { x: Long, y: Long -> x * y }
                                else -> { _: Long, _: Long -> 0L }
                            }

                            val a = when (this[0]) {
                                "old" -> { i: Long -> i }
                                else -> { _ -> this[0].toLong() }
                            }
                            val b = when (this[2]) {
                                "old" -> { i: Long -> i }
                                else -> { _ -> this[2].toLong() }
                            }

                            { v: Long -> operation(a(v), b(v)) }
                        }
                    val test = this[3].toLong()
                    val ifTrue = this[4].toInt()
                    val ifFalse = this[5].toInt()

                    Monkey(items, operation, test, ifTrue, ifFalse)
                }
    }

}

fun day11(input: String, n: Int, method: (Monkey) -> Unit) =
    input
        .split("\n\n")
        .map { Monkey.of(it) }
        .also { list -> list.map { it.setMonkeysSet(list); it.setLcm() } }
        .apply { repeat(n) { _ -> this.forEach { method(it) } } }
        .sortedByDescending { it.interactions }
        .subList(0, 2)
        .map { it.interactions }
        .reduce { first, second -> first * second }

fun main(args: Array<String>) {
    println(day11(input11, 20) { it.inspect(3) })
    println(day11(input11, 10_000) { it.inspect(1) })
}