import platform.posix.abs

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
    this[0].indices.map {i->
        (this.indices).map { j->
            this[j][i]
        }
    }
typealias Coordinates = Pair<Int, Int>
inline fun Coordinates.getNeighbours() = listOf(
    this.first + 1 to this.second,
    this.first - 1 to this.second,
    this.first to this.second + 1,
    this.first to this.second - 1
)
inline fun <T> Coordinates.getNeighbours(grid: List<List<T>>) = getNeighbours()
    .filter { it.first >= 0 && it.second >= 0 && it.first < grid.size && it.second < grid[0].size }

inline operator fun Coordinates.plus(other: Coordinates) = this.first + other.first to this.second to other.second
inline operator fun <T> Coordinates.get(grid: List<List<T>>) = grid[this.first][this.second]

inline fun Coordinates.manhattan(other: Coordinates) = abs(this.first - other.first) + abs(this.second - other.second)