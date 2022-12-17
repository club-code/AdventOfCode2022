package days11_15

import inputs.input14

fun String.getPoint(): Pair<Int, Int> =
    this
        .split(",")
        .let { it[0].toInt() to it[1].toInt() }

fun String.getPoints(): List<Pair<Int, Int>> =
    this
        .split("->")
        .map { it.getPoint() }

fun String.getWalls(): List<List<Pair<Int, Int>>> =
    this
        .replace(" ", "")
        .split("\n")
        .map { it.getPoints() }

fun MutableMap<Int, MutableMap<Int, Boolean>>.get(i: Int, j: Int) = this[i]?.get(j) ?: false

fun MutableMap<Int, MutableMap<Int, Boolean>>.set(i: Int, j: Int, v: Boolean) {
    this[i] = this
        .getOrDefault(i, mutableMapOf())
        .apply { this[j] = v }
}

class Grid(private val grid: MutableMap<Int, MutableMap<Int, Boolean>>,
           private val xMin: Int, private val xMax: Int, private val yMax: Int) {

    private val startSand = Pair(500, 0)
    private var x: Int = this.startSand.first
    private var y: Int = this.startSand.second
    private var sandCount = 0

    fun void() = this.placeSands({ z, h -> z in xMin..xMax && h < yMax }, { false })
    fun floor() = this.placeSands({ _, _ -> true }, { it + 1 == yMax })

    private fun placeSand(cond: Boolean): Boolean {
        if (this.grid.get(x, y + 1) || cond) {
            if (this.grid.get(x - 1, y + 1) || cond) {
                if (this.grid.get(x + 1, y + 1) || cond) {
                    if (this.grid.get(x, y)) {
                        return false  // pile obstructed
                    }

                    this.grid.set(x, y, true)

                    this.sandCount++
                    x = this.startSand.first
                    y = this.startSand.second
                } else { x++; y++ }
            } else { x--; y++ }
        } else { y++ }

        return true
    }

    private fun placeSands(latCond: (Int, Int) -> Boolean, heightCond: (Int) -> Boolean): Int {
        while (latCond(x, y) && this.placeSand(heightCond(y))) { continue }
        return sandCount
    }

    companion object {
        private fun of(walls: List<List<Pair<Int, Int>>>): Grid {
            var xMin = 500
            var xMax = 500
            var yMax = 0

            val ret = mutableMapOf<Int, MutableMap<Int, Boolean>>().apply {
                for (wall in walls) {
                    val first = wall.subList(0, wall.size - 1)
                    val second = wall.subList(1, wall.size)

                    for (line in first.zip(second)) {
                        var (x1, y1) = line.first
                        var (x2, y2) = line.second

                        // ordering integers
                        if (x2 < x1) { x1 = x2.also { x2 = x1 } }
                        if (y2 < y1) { y1 = y2.also { y2 = y1 } }

                        // computing frontiers of grid
                        if (x1 < xMin) { xMin = x1 }
                        if (x2 > xMax) { xMax = x2 }
                        if (y2 > yMax) { yMax = y2 }

                        for (i in x1..x2) { this.set(i, y1, true) }
                        for (j in y1..y2) { this.set(x1, j, true) }
                    }
                }
            }

            return Grid(ret, xMin, xMax, yMax + 2)
        }

        fun of(input: String): Grid = this.of(input.getWalls())
    }

}

fun day14(input: String) = Grid.of(input)
fun day14a(input: String) = day14(input).void()
fun day14b(input: String) = day14(input).floor()

fun main(args: Array<String>) {
    println(day14a(input14))
    println(day14b(input14))
}