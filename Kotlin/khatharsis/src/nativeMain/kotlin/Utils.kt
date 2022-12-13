fun List<String>.groupBySeparatorBlank() = this.fold(mutableListOf(mutableListOf<String>())) { acc, it ->
    if (it.isBlank()) {
        acc.add(mutableListOf<String>())
        return@fold acc
    } else {
        acc.last().add(it)
        return@fold acc
    }
}

fun<E> List<List<E>>.rotate(): List<List<E>> =
    (0 until this[0].size).map {i->
        (this.indices).map { j->
            this[j][i]
        }
    }
typealias Vector = Pair<Int, Int>
inline fun <T> List<List<T>>.indexesOf(t: T): List<Vector> =
    this.indices
        .mapNotNull { i ->
            this[i].indices.mapNotNull { j ->
                if (this[i][j] == t) i to j else null
            }
        }
        .flatten()
fun Vector.getNeighbours() = listOf(
    this.first + 1 to this.second,
    this.first - 1 to this.second,
    this.first to this.second + 1,
    this.first to this.second - 1
)
fun <T> Vector.getNeighbours(grid: List<List<T>>) = getNeighbours()
    .filter { it.first >= 0 && it.second >= 0 && it.first < grid.size && it.second < grid[0].size }