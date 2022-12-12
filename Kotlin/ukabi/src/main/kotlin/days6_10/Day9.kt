package days6_10

import input9

class Tail(private val head: Head) {
    var x: Int = 0
    var y: Int = 0
    val visited: MutableSet<Pair<Int, Int>> = mutableSetOf()

    private fun updateDiagForXMove(yDiff: Int) {
        when (yDiff) {
            1 -> this.y += 1
            -1 -> this.y -= 1
        }
    }

    private fun updateDiagForYMove(xDiff: Int) {
        when (xDiff) {
            1 -> this.x += 1
            -1 -> this.x -= 1
        }
    }

    fun update() {
        val xDiff = head.x - this.x
        val yDiff = head.y - this.y

        when (xDiff) {
            2  -> {
                this.x += 1
                this.updateDiagForXMove(yDiff)
            }
            -2 -> {
                this.x -= 1
                this.updateDiagForXMove(yDiff)
            }
        }
        when (yDiff) {
            2  -> {
                this.y += 1
                this.updateDiagForYMove(xDiff)
            }
            -2 -> {
                this.y -= 1
                this.updateDiagForYMove(xDiff)
            }
        }

        this.visited.add(Pair(this.x, this.y))
        this.head.sub?.moveTo(this)
    }

}

class Head(private val size: Int) {
    var x: Int = 0
    var y: Int = 0
    val sub: Head? = this.size.takeIf { it > 2 }?.let { Head(this.size - 1) }
    val tail = Tail(this)

    fun moveTo(tail: Tail) { this.x = tail.x; this.y = tail.y; this.tail.update() }

    private fun moveUp() { this.y += 1; this.tail.update() }
    private fun moveDown() { this.y -= 1; this.tail.update() }
    private fun moveLeft() { this.x -= 1; this.tail.update() }
    private fun moveRight() { this.x += 1; this.tail.update() }

    private fun moveUp(n: Int) = repeat(n) { _ -> this.moveUp() }
    private fun moveDown(n: Int) = repeat(n) { _ -> this.moveDown() }
    private fun moveLeft(n: Int) = repeat(n) { _ -> this.moveLeft() }
    private fun moveRight(n: Int) = repeat(n) { _ -> this.moveRight() }

    fun move(direction: String, count: Int) {
        when (direction) {
            "U" -> this.moveUp(count)
            "D" -> this.moveDown(count)
            "L" -> this.moveLeft(count)
            "R" -> this.moveRight(count)
        }
    }
}

fun day9(input: String, size: Int): Head =
    Head(size).apply {
        input
            .split("\n")
            .forEach { line ->
                line
                    .split(" ")
                    .let { this.move(it[0], it[1].toInt()) }
            }
    }

fun day9a(input: String): Int = day9(input, 1).tail.visited.size
fun day9b(input: String): Int = day9(input, 10).sub!!.sub!!.sub!!.sub!!.sub!!.sub!!.sub!!.sub!!.tail.visited.size

fun main(args: Array<String>) {
    println(day9a(input9))
    println(day9b(input9))
}