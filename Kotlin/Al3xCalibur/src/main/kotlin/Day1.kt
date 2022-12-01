class Day1 : DaySolver(1, "Calorie Counting") {
    private val aggregatedData = data.splitToSequence("\n\n")
        .map {
            it.lineSequence().sumOf { calorie -> calorie.toLong() }
        }
        .toList()

    override fun firstPart(): String {
        return aggregatedData.max()
            .toString()
    }

    override fun secondPart(): String {
        return aggregatedData.sortedDescending().take(3).sum()
            .toString()
    }
}
