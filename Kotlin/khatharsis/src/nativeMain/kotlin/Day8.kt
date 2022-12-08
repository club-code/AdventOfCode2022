class Day8 : DaySolver(8, "Treetop Tree House") {
    private val newData = data.map { line -> line.map {c -> c.digitToInt() } }

    private fun Pair<Int, Int>.isVisible(value: Int): Boolean =
        (0 until this.first).all { newData[it][this.second] < value } // Visible from the top
                || (this.first + 1 until newData.size).all { newData[it][this.second] < value } // Visible from the bottom
                || (0 until this.second).all { newData[this.first][it] < value } // Visible from the left
                || (this.second + 1 until newData[0].size).all { newData[this.first][it] < value } // Visible from the right

    override fun firstPart() = newData.mapIndexed { lineNumber, line ->
        line.mapIndexed { colNumber, value ->
            (lineNumber to colNumber).isVisible(value)
        }.count { it }
    }.sum().toString()


    private fun Pair<Int, Int>.scenicScore(value: Int) =
        (0 until this.first).reversed().takeWhile { newData[it][this.second] < value }.count()
            .let { if (it < this.first) it + 1 else it } * // Scenic from the top
                (0 until this.second).reversed().takeWhile { newData[this.first][it] < value }.count()
                    .let { if (it < this.second) it + 1 else it } * // Scenic from the left
                (this.second + 1 until newData[0].size).takeWhile { newData[this.first][it] < value }.count()
                    .let { if (it < newData[0].size - this.second - 1) it + 1 else it } * // Scenic from the right
                (this.first + 1 until newData.size).takeWhile { newData[it][this.second] < value }.count()
                    .let { if (it < newData.size - this.first - 1) it + 1 else it } // Scenic from the bottom


    override fun secondPart(): String = newData.mapIndexed { lineNumber, line ->
        line.mapIndexed { colNumber, value ->
            (lineNumber to colNumber).scenicScore(value)
        }
    }.flatten().max().toString()
}