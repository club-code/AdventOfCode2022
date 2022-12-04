class Day4 : DaySolver(4, "Camp Cleanup") {
    private val newData = data.map { s ->
        s.split(',').map { it.split('-') }.flatten().map { it.toInt() }
    }

    override fun firstPart() =
        newData.count {
            // The first contains the second
            (it[0] <= it[2] && it[1] >= it[3]) || (it[2] <= it[0] && it[3] >= it[1])
        }.toString()

    override fun secondPart() =
        newData.count {
            (it[0] <= it[2] && it[2] <= it[1]) || (it[0] <= it[3] && it[3] <= it[1]) ||
                    (it[2] <= it[0] && it[0] <= it[3]) || (it[2] <= it[1] && it[1] <= it[3])
        }.toString()
}