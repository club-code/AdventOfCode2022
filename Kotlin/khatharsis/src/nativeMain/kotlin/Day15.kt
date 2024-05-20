import kotlinx.atomicfu.locks.reentrantLock
import kotlinx.atomicfu.locks.withLock
import platform.posix.abs

class Day15 : DaySolver(15, "Beacon Exclusion Zone") {
    private val lineRegex = Regex("Sensor at x=(-?\\d+), y=(-?\\d+): closest beacon is at x=(-?\\d+), y=(-?\\d+)")
    private val sensorMap =
        data.map { line -> lineRegex.matchEntire(line)!!.groupValues.takeLast(4).map { it.toInt() } }
            .associate { (it[0] to it[1]) to (it[2] to it[3]) }

    /**
     * For the sensor corresponding to these coordinates, returns a Pair corresponding to the lower and higher
     * x value in the given line that are sure to be empty.
     */
    private fun Coordinates.coverAt(lineNumber: Int): Pair<Int, Int>? {
        val distToClosestBeacon = this.manhattan(sensorMap[this]!!)
        val distToLine = abs(this.second - lineNumber)
        return if (distToLine <= distToClosestBeacon)
            (this.first - (distToClosestBeacon - distToLine)) to (this.first + (distToClosestBeacon - distToLine))
        else null
    }

    /**
     * Counts the number of values in the Pair.
     */
    private inline fun Pair<Int, Int>.count() = this.second - this.first + 1

    private enum class Status {
        INTERSECT, CONTAINS, CONTAINED, DISJOINT, EQUALS;
    }

    /**
     * Gives the status of a pair compared to another.
     * We know that this.first <= other.first and if (this.first == other.first) then this.second <= other.second
     */
    private fun Pair<Int, Int>.status(other: Pair<Int, Int>): Status = when {
        (this == other) -> Status.EQUALS
        (this.first == other.first) -> Status.CONTAINED
        (other.second <= this.second) -> Status.CONTAINS
        (other.first <= this.second) -> Status.INTERSECT
        (this.second < other.first) -> Status.DISJOINT
        else -> throw Exception("$this $other")
    }

    /**
     * Returns the coverage of a given line.
     * MinMax specifies whether the subcoverage should be trimed.
     */
    private inline fun coverage(lineNumber: Int, minMax: Pair<Int, Int>? = null): List<Pair<Int, Int>> {
        val temp: MutableList<Pair<Int, Int>?> = sensorMap.keys.mapNotNull { sensor ->
            sensor.coverAt(lineNumber)
        }.let {
            if (minMax != null) it.mapNotNull { sensorCoverage ->
                when (sensorCoverage.status(minMax)) {
                    Status.CONTAINED -> sensorCoverage
                    Status.DISJOINT -> null
                    Status.CONTAINS, Status.EQUALS -> minMax
                    Status.INTERSECT -> if (sensorCoverage.first < minMax.first) minMax.first to sensorCoverage.second
                    else sensorCoverage.first to minMax.second
                }
            } else it
        }.sortedBy{it.second}.sortedBy {it.first }.toMutableList()

        return temp.indices.mapNotNull { i ->
            var tempPair: Pair<Int, Int>? = temp[i]
            for ((j, newPair) in temp.drop(i + 1).withIndex()) {
                if (tempPair == null) break
                if (newPair != null)
                    when (tempPair.status(newPair)) {
                        Status.CONTAINED -> tempPair = null
                        Status.EQUALS, Status.CONTAINS -> temp[i + j + 1] = null
                        Status.DISJOINT -> {}
                        Status.INTERSECT -> { temp[i + j + 1] = null
                            tempPair = tempPair.first to newPair.second
                            temp[i] = tempPair
                        }
                    }
            }
            tempPair
        }
        // This code is more readable but less efficient
    }

    override fun firstPart(): String {
        val lineNumber = 2000000
        return (coverage(lineNumber).fold(0) { acc, pair -> acc + pair.count() } - sensorMap.values.toSet()
            .count { it.second == lineNumber }).toString()
    }

    override fun secondPart(): String {
        val max = 4_000_000
        val minMax = 0 to max
        val step = max/(NUM_CORES)
        return executeParallel { threadNumber ->
            for (line in (threadNumber*step) .. (threadNumber+1)*step) {
                val coverage = coverage(line, minMax).sortedBy { it.first }
                if (coverage.fold(0) { acc, pair -> acc + pair.count() } == max) {
                    val x = coverage.zipWithNext().first { (cur, next) -> cur.second != next.first - 1 }.first.second + 1
                    return@executeParallel (4_000_000L * x + line).toString()
                }
            }
            null
        }.first()
    }
}