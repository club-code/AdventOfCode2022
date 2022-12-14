package days11_15

import indexesOf
import inputs.input12
import toArray
import toMutableArray

class Cell(val value: Char) {
    private lateinit var neighbors: Set<Cell>
    private lateinit var seen: MutableList<Int>

    fun setNeighbors(neighbors: Set<Cell>) { this.neighbors = neighbors }

    fun setSeen(size: Int) { this.seen = MutableList(size) { Int.MAX_VALUE } }

    fun explore(index: Int): Int? {
        val toTreat = mutableListOf(Pair(this, 1))
        this.seen[index] = 1

        while (toTreat.isNotEmpty()) {
            val (cur, count) = toTreat.removeAt(0)

            if (cur.value == 'z') {
                return count
            }

            for (n in cur.neighbors.filterNot { it.seen[index] < Int.MAX_VALUE }) {
                n.seen[index] = count
                toTreat.add(Pair(n, count + 1))
            }
        }
        return null
    }

}

fun List<List<Char>>.asBoard(size: Int): List<List<Cell>> =
    this.indices.map { i ->
        this[i].indices.map { j ->
            Cell(this[i][j])
        }
    }.apply {
        this.indices.map { i ->
            this[i].indices.map { j ->
                setOf(Pair(i - 1, j), Pair(i + 1, j), Pair(i, j - 1), Pair(i, j + 1))
                    .filter { it.first in this.indices && it.second in this[i].indices }
                    .map { this[it.first][it.second] }
                    .filter { it.value <= this[i][j].value + 1 }
                    .also {
                        this[i][j].setNeighbors(it.toSet())
                        this[i][j].setSeen(size)
                    }
            }
        }
    }

fun day12(input: String, startPoints: List<Pair<Int, Int>>) =
    input
        .toMutableArray<Char>()
        .apply {
            this.indexesOf('E').forEach { this[it.first][it.second] = 'z' }
            startPoints.forEach { this[it.first][it.second] = 'a' }
        }
        .asBoard(startPoints.size)
        .run {
            startPoints.indices.zip(startPoints)
                .mapNotNull { this[it.second.first][it.second.second].explore(it.first) }
        }
        .min()

fun day12a(input: String) =
    input.run { day12(this, this.toArray<Char>().indexesOf('S')) }

fun day12b(input: String) = day12a(input.replace('a', 'S'))

fun main(args: Array<String>) {
    println(day12a(input12))
    println(day12b(input12))
}