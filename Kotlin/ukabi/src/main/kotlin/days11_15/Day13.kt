package days11_15

import inputs.input13

sealed class Value {
    abstract val data: Any

    class ValInt(override val data: Int) : Value() {
        override operator fun compareTo(other: ValInt): Int = this.data.compareTo(other.data)
        override operator fun compareTo(other: ValList): Int = ValList(listOf(this)).compareTo(other)
        override fun unfold() = this.data
        override fun toString(): String = this.data.toString()
    }

    class ValList(override val data: List<Value>) : Value() {
        override operator fun compareTo(other: ValInt): Int = this.compareTo(ValList(listOf(other)))

        override operator fun compareTo(other: ValList): Int =
            if (this.data.size < other.data.size) {
                val o = ValList(other.data.subList(0, this.data.size))
                if (this.compareTo(o) == 0) -1 else 1   // length condition

            } else if (this.data.size > other.data.size) {
                val f = ValList(this.data.subList(0, other.data.size))
                if (f.compareTo(other) == 0) 1 else -1  // length condition

            } else {
                this.data.zip(other.data)
                    .map { it.first.compareTo(it.second) }
                    .dropWhile { it == 0 }
                    .firstOrNull() ?: 0
            }

        override fun unfold(): List<Any> = this.data.map { it.unfold() }

        override fun toString(): String = this.data.joinToString(",", "[", "]") { it.toString() }

    }

    fun compareTo(other: Value): Int = when (other) {
            is ValInt -> this.compareTo(other)
            is ValList -> this.compareTo(other)
        }

    abstract operator fun compareTo(other: ValList): Int
    abstract operator fun compareTo(other: ValInt): Int
    abstract fun unfold(): Any
}

fun String.parse(): Value.ValList = Tree.parse(this).unfold()

class Tree(private val root: Tree?, private var values: MutableList<Any> = mutableListOf()) {

    fun addChild() = Tree(this).also { this.values.add(it) }

    fun addValue(value: String) { this.values.add(value.toInt()) }

    fun unfold(): Value.ValList = Value.ValList(
        this.values.map {
            when (it) {
                is Tree -> it.unfold()
                is Int -> Value.ValInt(it)
                else -> throw Error()
            }
        }
    )

    override fun toString(): String =
        this.values.joinToString(",", "[", "]") {
            when (it) {
                is Tree -> it.toString()
                is Int -> it.toString()
                else -> throw Error()
            }
        }

    companion object {
        fun parse(string: String): Tree {
            var cur = Tree(null)

            var acc = ""
            for (c in string) {
                when (c) {
                    '[' -> cur = cur.addChild()
                    ']' -> {
                        if (acc.isNotEmpty()) {
                            cur.addValue(acc)
                            acc = ""
                        }
                        cur = cur.root!!
                    }
                    ',' -> {
                        if (acc.isNotEmpty()){
                            cur.addValue(acc)
                            acc = ""
                        }
                    }
                    else -> acc += c
                }
            }

            return cur.values.first() as Tree
        }
    }
}
fun day13(input: String) =
    input
        .split("\n\n")
        .map { block -> block.split("\n").let { it[0].parse() to it[1].parse() }}
        .mapIndexed {i, couple -> i to couple}
        .filter { it.second.first <= it.second.second }
        .sumOf { it.first }

fun day13a(input: String) =
    day13(input)

fun day13b(input: String) =
    day13(input)

fun main(args: Array<String>) {
    println(day13a(input13))
    println(day13b(input13))
}