package days11_15

import inputs.input13

sealed class Value {

    class ValInt(val data: Int) : Value() {
        override fun compareTo(other: ValInt): Int = if (this.data.compareTo(other.data) == 0) -1 else 1
        override fun compareTo(other: ValList): Int = ValList(listOf(this)).compareTo(other)
        fun unfold() = this.data
    }

    class ValList(val data: List<Value>) : Value() {
        override fun compareTo(other: ValInt): Int = this.compareTo(ValList(listOf(other)))

        override fun compareTo(other: ValList): Int =
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

        fun unfold(): List<Any> = this.data.map {
            when (it) {
                is ValInt -> it.unfold()
                is ValList -> it.unfold()
            }
        }
    }

    override fun toString(): String =
        when (this) {
            is ValInt -> this.data.toString()
            is ValList -> this.data.joinToString(",", "[", "]") { it.toString() }
        }

    fun compareTo(other: Value): Int =
        when (this) {
            is ValInt, is ValList -> when (other) {
                is ValInt -> this.compareTo(other)
                is ValList -> this.compareTo(other)
            }
        }

    abstract fun compareTo(other: ValList): Int
    abstract fun compareTo(other: ValInt): Int
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
        .map { block ->
            block
                .split("\n")
                .let { it[0].parse() to it[1].parse() }
                .let { it.first.compareTo(it.second) }
        }
        .let { result -> result.indices.zip(result) }
        .filter { it.second == -1 }
        .sumOf { it.first + 1 }

fun day13a(input: String) =
    day13(input)

fun day13b(input: String) =
    day13(input)

fun main(args: Array<String>) {
    println(day13a(input13))
    println(day13b(input13))
}