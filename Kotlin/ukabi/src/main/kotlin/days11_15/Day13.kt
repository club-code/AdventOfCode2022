package days11_15

import inputs.input13

fun String.parse(): List<Any> =
    Tree.parse(this).unfold()

fun Pair<Any, Any>.compare(): Int =
    when (this.first) {
        is Int -> when (this.second) {
            is Int -> (this.first as Int).compareTo(this.second as Int)
            is List<*> -> Pair(listOf(this.first), this.second).compare()
            else -> 0
        }
        is List<*> -> when (this.second) {
            is Int -> Pair(this.first, listOf(this.second)).compare()
            is List<*> -> {
                val f = this.first as List<*>
                val s = this.second as List<*>

                if (f.size < s.size) {
                    if (Pair(f, s.subList(0, f.size)).compare() == 0) -1 else 1
                } else if (f.size > s.size) {
                    if (Pair(f.subList(0, s.size), s).compare() == 0) 1 else -1
                } else {
                    f.zip(s)
                        .map { Pair(it.first!!, it.second!!).compare() }
                        .dropWhile { it == 0 }
                        .firstOrNull() ?: 0
                }
            }

            else -> 0
        }

        else -> 0
    }

class Tree(private val root: Tree?, private var values: MutableList<Any> = mutableListOf()) {

    fun addChild() = Tree(this).also { this.values.add(it) }

    fun addValue(value: String) { this.values.add(value.toInt()) }

    fun unfold(): List<Any> =
        this.values.map {
            when (it) {
                is Tree -> it.unfold()
                is Int -> it
                else -> throw Error()
            }
        }

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
                .compare()
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