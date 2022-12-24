import kotlinx.cinterop.refTo
import kotlinx.cinterop.toKString
import platform.posix.*

fun execAndStdOut(command: String): String {
    val fp = popen(command, "r")
    val stdout = buildString {
        val buffer = ByteArray(4096)
        while (true) {
            val input = fgets(buffer.refTo(0), buffer.size, fp) ?: break
            append(input.toKString())
        }
    }
    val status = pclose(fp)
    if (status != 0) {
        error("Failed to get input from server: status $status")
    }
    return stdout
}

fun List<String>.groupBySeparatorBlank() = this.fold(mutableListOf(mutableListOf<String>())) { acc, it ->
    if (it.isBlank()) {
        acc.add(mutableListOf<String>())
        return@fold acc
    } else {
        acc.last().add(it)
        return@fold acc
    }
}

fun <E> List<List<E>>.rotate(): List<List<E>> =
    this[0].indices.map { i ->
        (this.indices).map { j ->
            this[j][i]
        }
    }
typealias Coordinates = Pair<Int, Int>
typealias Coordinates3D = Triple<Int, Int, Int>

inline fun Coordinates.getNeighbours() = listOf(
    this.first + 1 to this.second,
    this.first - 1 to this.second,
    this.first to this.second + 1,
    this.first to this.second - 1
)

inline fun Coordinates3D.getNeighbours() = listOf(
    Triple(first, second, third + 1),
    Triple(first, second, third - 1),
    Triple(first, second + 1, third),
    Triple(first, second - 1, third),
    Triple(first + 1, second, third),
    Triple(first - 1, second, third)
)

inline fun IntRange.size() = last - first + 1

inline fun <T> Coordinates.getNeighbours(grid: List<List<T>>) = getNeighbours()
    .filter { it.first >= 0 && it.second >= 0 && it.first < grid.size && it.second < grid[0].size }

inline operator fun Coordinates.plus(other: Coordinates) = this.first + other.first to this.second to other.second
inline operator fun <T> Coordinates.get(grid: List<List<T>>) = grid[this.first][this.second]

inline fun Coordinates.manhattan(other: Coordinates) = abs(this.first - other.first) + abs(this.second - other.second)