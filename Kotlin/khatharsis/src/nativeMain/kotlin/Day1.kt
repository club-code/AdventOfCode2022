class Day1 : DaySolver(1, "Calorie Counting") {
    private val newData = data.groupBySeparatorBlank().map { it.sumOf { nb->nb.toLong() } }

    override fun firstPart(): String {
        return newData.max().toString()
    }

    override fun secondPart(): String {
        return newData.sortedDescending().take(3).sum().toString()
    }
}