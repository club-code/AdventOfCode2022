import java.lang.IllegalStateException

inline fun <reified T> transpose(matrix: List<List<T>>): List<List<T>> {
    val cols = matrix[0].size
    val rows = matrix.size
    return List(cols) { j ->
        List(rows) { i ->
            matrix[i][j]
        }
    }
}

inline fun <reified T> String.convertTo(): T =
    when (T::class) {
        Int::class -> this.toInt()
        Char::class -> this.first()
        else -> throw IllegalStateException("Unknown")
    } as T

inline fun <reified T> String.toArray(): List<List<T>> =
    this
        .split("\n")
        .map { line ->
            line
                .toList()
                .map { it.toString().convertTo() }
        }

inline fun <reified T> String.toMutableArray(): MutableList<MutableList<T>> =
    this
        .toArray<T>()
        .map { it.toMutableList() }
        .toMutableList()

inline fun <reified T> List<List<T>>.indexesOf(t: T): List<Pair<Int, Int>> =
    this.indices
        .mapNotNull { i ->
            this[i].indices.mapNotNull { j ->
                if (this[i][j] == t) Pair(i, j) else null
            }
        }
        .flatten()