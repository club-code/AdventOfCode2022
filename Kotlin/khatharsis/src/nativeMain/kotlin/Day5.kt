class Day5() : DaySolver(5, "Supply Stacks") {
    private val columnSize = 4
    private val delimitation = data.indexOf(data.first { it.isBlank() })

    private val instructions = data.subList(delimitation + 1, data.size)
        .map { it.split(" ").filterIndexed { i, _ -> i % 2 == 1 }.map { it.toInt() } }

    private val columns = data.subList(0, delimitation) // Grab everything before the instructions
        .dropLast(1) // Don't need to grab the line numbers
        .map { line -> line.chunked(columnSize).map { s -> s[1] } } // We divide them by column and we grab the char
        .rotate() // Group it by columns
        .map { it.filter { c -> !c.isWhitespace() } } // Remove whitespaces
        .map { it.toCharArray().concatToString() } // Convert to String
        .map { it.reversed() } // Reverse them for easier stuff later

    override fun firstPart(): String = magicFunction(columns, true)
    override fun secondPart(): String = magicFunction(columns, false)

    private fun magicFunction(columns: List<String>, isReversed: Boolean): String {
        // Copy the given lists and make'em mutable
        val columnsMutable = columns.toMutableList()
        instructions.forEach { instruction ->
            // Grab the instructions
            val n = instruction.first()
            val from = instruction[1] - 1
            val to = instruction.last() - 1
            // Take the last n from the "from" column
            columnsMutable[to] += columnsMutable[from].takeLast(n).let { if (isReversed) it.reversed() else it }
            // Remove 'em
            columnsMutable[from] = columnsMutable[from].dropLast(n)
        }
        return columnsMutable.fold("") { acc, chars -> acc + chars.last() }
    }
}