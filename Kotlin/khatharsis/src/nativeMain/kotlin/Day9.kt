import kotlin.math.abs
import kotlin.math.max

class Day9: DaySolver(9, "Rope Bridge") {
    private inline fun Coordinates.move(direction: Char) =
        when (direction) {
            'R' -> this.first to this.second+1
            'L' -> this.first to this.second-1
            'U' -> this.first-1 to this.second
            'D' -> this.first+1 to this.second
            else -> throw Exception("Unable to parse direction: $direction")
        }
    private inline fun Coordinates.inf(other: Coordinates) = max(abs(this.first - other.first), abs(this.second - other.second))

    private fun Coordinates.snapBack(other: Coordinates) = if (other.inf(this) <= 1) this else {
        when {
            (this.first == other.first) -> this.first to this.second + (if (this.second < other.second) 1 else -1)
            (this.second == other.second) -> this.first + (if (this.first < other.first) 1 else -1) to this.second
            else -> this.first + (if (this.first < other.first) 1 else -1) to this.second + (if (this.second < other.second) 1 else -1)
        }
    }

    override fun firstPart(): String {
        var head = 0 to 0
        var tail = 0 to 0
        val visited = mutableListOf<Coordinates>()
        visited.add(tail)
        data.map { it.split(' ') }.forEach {
            (1..it.last().toInt()).forEach { _ ->
                head = head.move(it.first().first())
                tail = tail.snapBack(head)
                visited.add(tail)
            }
        }
        return visited.distinct().size.toString()
    }

    override fun secondPart(): String {
        val visited = mutableListOf<Coordinates>()
        val rope = (1..10).map {0 to 0}.toMutableList()
        data.map { it.split(' ') }.forEach { it ->
            (1..it.last().toInt()).forEach { _ ->
                rope[0] = rope[0].move(it.first().first())
                (0 until rope.lastIndex).forEach {index ->
                    rope[index+1] = rope[index+1].snapBack(rope[index])
                }
                visited.add(rope.last())
            }
        }
        return visited.distinct().size.toString()
    }
}