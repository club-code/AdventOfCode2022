package days11_15

import inputs.input15
import kotlin.math.absoluteValue

typealias Vector<T> = Pair<T, T>
typealias InfoData = Triple<Vector<Int>, Vector<Int>, Int>

class Interval(var start: Int, var end: Int) {
    fun toPair(): Pair<Int, Int> = Pair(this.start, this.end)
    companion object {
        fun of(pair: Pair<Int, Int>): Interval = Interval(pair.first, pair.second)
    }
}
class Plane(private val infoData: List<InfoData>,
            private val xMin: Int, private val xMax: Int, private val maxVal: Int) {

    fun inspectHeight(value: Int): Int {
        val noBeacon = (this.xMin..this.xMax)
            .map { Pair(it, value).inDisks() }
            .filter { it }.size

        val beacons = this.infoData
            .map { it.second }.toSet()
            .filter { it.second == value }.size

        return noBeacon - beacons
    }

    fun findSpot(): Int? {
        val xMin = this.xMin.let { if (it < 0) 0 else it }
        val xMax = this.xMax.let { if (it > this.maxVal) this.maxVal else it }

        val temp = this.infoData.sortedBy { it.first.second }
        val yMin = temp.first()
            .let { it.first.second - it.third }
            .let { if (it < 0) 0 else it }
        val yMax = temp.last()
            .let { it.first.second + it.third }
            .let { if (it > this.maxVal) this.maxVal else it }

        for (y in yMin..yMax) {
            val union = this.infoData.mapNotNull { it.segmentOfHeight(y, xMin, xMax) }.union()!!.toList().union()!!.also { println("$y - $it") }

            if (union.size > 1) {
                val stop = union.toList().minBy { it.second }.second

                return Pair((stop + 1), y).tuneFrequency()
            }
        }

        return null
    }

    private fun Vector<Int>.inDisks(): Boolean = this@Plane.infoData.any { this.inDisk(it) }

    companion object {
        private fun List<Pair<Int, Int>>.union(): Set<Pair<Int, Int>>? {
            if (this.isEmpty()) { return null }

            val ret = mutableSetOf(this.first())
            for (i in this.subList(1, this.size)) {
                val top = ret.last()
                if (top.second < i.first) {
                    ret.add(i)
                } else if (top.second <= i.second) {
                    val temp = Interval.of(top)

                    temp.end = i.second
                    if (top.second == i.second) { temp.start -= 1 }

                    ret.remove(top)
                    ret.add(temp.toPair())
                }
            }

            return ret
        }

        private fun InfoData.segmentOfHeight(y: Int, xMin: Int, xMax: Int): Pair<Int, Int>? {
            val (x0, y0) = this.first
            val r = this.third

            val d = when (y) {
                in y0 - r..y0 -> (y0 - r - y).absoluteValue
                in y0 + 1..y0 + r -> (y0 + r - y).absoluteValue
                else -> return null
            }

            val inf = (x0 - d).let { if (it < xMin) xMin else it }
            val sup = (x0 + d).let { if (it > xMax) xMax else it }

            return Pair(inf, sup)
        }

        private fun Vector<Int>.inDisk(d: InfoData): Boolean = this.manhattanDistance(d.first) <= d.third
        private fun Vector<Int>.tuneFrequency(): Int = this.first * 4000000 + this.second

        private fun Vector<Int>.manhattanDistance(other: Vector<Int>) =
            (this.first - other.first).absoluteValue + (this.second - other.second).absoluteValue

        private fun List<String>.parsePair(): Vector<Int> = this.let { it[0].toInt() to it[1].toInt() }

        private fun String.parsePairs(): Pair<Vector<Int>, Vector<Int>> =
            this
                .split(",")
                .let { it.subList(0, 2).parsePair() to it.subList(2, 4).parsePair() }

        private fun String.parseAll(): List<InfoData> =
            this
                .split("\n")
                .map { line -> Regex("""-?\d+""").findAll(line).map { it.value } }
                .map { it.joinToString(",") }
                .map { pair -> pair.parsePairs().let { Triple(it.first, it.second, it.first.manhattanDistance(it.second)) } }

        fun of(input: String, maxVal: Int): Plane {
            var xMin: Int
            var xMax: Int

            val ret = input.parseAll()
                .sortedBy { it.second.first }
                .also { pair ->
                    xMin = pair.first().let { it.first.first - it.third }
                    xMax = pair.last().let { it.first.first + it.third }
                }

            return Plane(ret, xMin, xMax, maxVal)
        }
    }

}

fun main(args: Array<String>) {
    Plane.of(input15, 4000000).apply {
        println(this.inspectHeight(2000000))
        println(this.findSpot())
    }
}