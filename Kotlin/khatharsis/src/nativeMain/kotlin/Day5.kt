import platform.posix.isnan

class Day5() : DaySolver(5, "Supply Stacks") {
    private val columnSize = 4
    private val delimitation = data.indexOf(data.first { it.isBlank() })

    private val instructions = data.subList(delimitation+1, data.size)
        .map {it.split(" ").filterIndexed {i, _ -> i%2==1}.map {it.toInt()}}

    private val columns = data.subList(0, delimitation) // Grab everything before the instructions
        .dropLast(1) // Don't need to grab the line numbers
        .map { line -> line.chunked(columnSize).map { s -> s[1] } } // We divide them by column and we grab the char
        .rotate()
        .map {it.filter {c-> !c.isWhitespace()}}
        .map {it.reversed()}

    override fun firstPart(): String = magicFunction(columns, true)
    override fun secondPart(): String = magicFunction(columns, false)

    private fun magicFunction(columns: List<List<Char>>, isReversed: Boolean): String {
        val columnsMutable = columns.map {it.toMutableList()}
        instructions.forEach { instruction ->
            val n = instruction.first()
            val from = instruction[1]-1
            val to = instruction.last()-1
            val craneIntake = columnsMutable[from].takeLast(n).let {if (isReversed) it.reversed() else it}
            (1..n).forEach { _ ->
                columnsMutable[from].removeLast()
            }
            columnsMutable[to].addAll(craneIntake)
        }
        return columnsMutable.fold("") {acc, chars -> acc + chars.last()}
    }
}