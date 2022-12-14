package days6_10

import inputs.input8
import toArray

fun List<List<Int>>.isVisible(i: Int, j: Int, lineStart: Int, colStart: Int): Boolean =
    if ((lineStart == -1) and (colStart in this.indices)) {
        if (j + 1 <= colStart) {
            (j + 1..colStart).all { this[i][it] < this[i][j] }
        } else if (j == 0) {
            true
        } else {
            (colStart until j).all { this[i][it] < this[i][j] }
        }
    } else if ((colStart == -1) and (lineStart in this.indices)) {
        if (i <= lineStart) {
            (i + 1..lineStart).all { this[it][j] < this[i][j] }
        } else if (i == 0) {
            true
        } else {
            (lineStart until i).all { this[it][j] < this[i][j] }
        }
    } else {
        false
    }

fun List<List<Int>>.isVisible(i: Int, j: Int, orientation: Char): Boolean = when (orientation) {
    'W' -> this.isVisible(i, j, -1, 0)
    'E' -> this.isVisible(i, j, -1, this.size - 1)
    'N' -> this.isVisible(i, j, 0, -1)
    'S' -> this.isVisible(i, j, this.size - 1, -1)
    else -> false
}

fun List<List<Int>>.isVisible(i: Int, j: Int): Boolean = "NSWE".any { this.isVisible(i, j, it) }
fun List<List<Int>>.sight(i: Int, j: Int, lineStart: Int, colStart: Int): Int {
    if ((i == this.size - 1) or (i == 0) or (j == this.size - 1) or (j == 0)) {
        return 0
    } else if ((lineStart == -1) and (colStart in this.indices)) {
        if (j + 1 < colStart) {
            for (n in (j + 1) .. colStart) {
                if (this[i][n] >= this[i][j]) {
                    return n - j
                }
            }
            return colStart - j
        } else {
            for (n in (j - 1) downTo colStart) {
                if (this[i][n] >= this[i][j]) {
                    return n - j
                }
            }
            return colStart - j
        }
    } else if ((colStart == -1) and (lineStart in this.indices)) {
        if (i + 1 < lineStart) {
            for (n in (i + 1) .. lineStart) {
                if (this[n][j] >= this[i][j]) {
                    return n - i
                }
            }
            return lineStart - i
        } else {
            for (n in (i - 1) downTo lineStart) {
                if (this[n][j] >= this[i][j]) {
                    return n - i
                }
            }
            return lineStart - i
        }
    } else {
        return 0
    }
}

fun List<List<Int>>.sight(i: Int, j: Int, orientation: Char): Int =
    when (orientation) {
        'W' -> this.sight(i, j, -1, 0)
        'E' -> this.sight(i, j, -1, this.size - 1)
        'N' -> this.sight(i, j, 0, -1)
        'S' -> this.sight(i, j, this.size - 1, -1)
        else -> 0
    }

fun List<List<Int>>.score(i: Int, j: Int): Int = "NSWE".map { this.sight(i, j, it) }.reduce { acc, n -> acc * n }
fun day8(input: String): List<List<Int>> = input.toArray()
fun day8a(input: String): Int =
    day8(input).run {
        this.indices.sumOf { line -> this[0].indices.sumOf { this.isVisible(line, it).compareTo(false) } }
    }

fun day8b(input: String): Int =
    day8(input).run {
        this.indices.map { line -> this[0].indices.map { this.score(line, it) } }.flatten().max()
    }

fun main(args: Array<String>) {
    println(day8a(input8))
    println(day8b(input8))
}