class Day23 : DaySolver(23, "Unstable Diffusion") {
    val elfMap = data.asSequence().mapIndexed { line: Int, s: String ->
        s.mapIndexed { x: Int, c: Char -> Pair(x, line) to c }
    }.flatten().filter { it.second == '#' }.map { it.first }
        .associateWith { Elf(it.first, it.second) }
        .toMutableMap()

    inner class Elf(private var x: Int, private var y: Int) {
        private inline fun neighbours(): List<Coordinates> = listOf(
            Coordinates(x - 1, y - 1), // NW
            Coordinates(x + 1, y - 1), // NE
            Coordinates(x, y - 1), // N

            Coordinates(x - 1, y + 1), // SW
            Coordinates(x + 1, y + 1), // SE
            Coordinates(x, y + 1), // S

            Coordinates(x - 1, y), // W
            Coordinates(x + 1, y), // E
        )

        private inline fun directionalNeighbours(): List<List<Coordinates>> = neighbours().let {
            listOf(
                it.take(3),
                it.subList(3, 6),
                it.filterIndexed { index, _ -> index % 3 == 0 },
                it.filterIndexed { index, _ -> index % 3 == 1 },
            )
        }

        fun isAlone() = neighbours().none { elfMap.containsKey(it) }
        private inline fun directions(): List<Triple<() -> Boolean, Coordinates, Elf.() -> Unit>> =
            directionalNeighbours().let {
                listOf(
                    Triple({ it[0].none { elfMap.containsKey(it) } }, x to y - 1, { y-- }),
                    Triple({ it[1].none { elfMap.containsKey(it) } }, x to y + 1, { y++ }),
                    Triple({ it[2].none { elfMap.containsKey(it) } }, x - 1 to y, { x-- }),
                    Triple({ it[3].none { elfMap.containsKey(it) } }, x + 1 to y, { x++ }),
                )
            }

        var curTry = 0
        fun propose(): Pair<Coordinates, Elf.() -> Unit> {
            val directions = directions()
            // No need to invoke it 4 times
            var output: Pair<Coordinates, Elf.() -> Unit> = (x to y) to {}
            for (delta in 0 until 4) {
                val temp = directions[(curTry + delta) % 4]
                if (temp.first.invoke()) {
                    output = temp.second to temp.third
                    break
                }
            }
            curTry++
            return output
        }
    }

    private fun round(): Boolean {
        val propositionList = elfMap.filterValues { !it.isAlone() }.map { (key, value) -> key to value.propose() }
        elfMap.filterValues { it.isAlone() }.forEach { it.value.curTry++ }
        val propositionCount = propositionList
            .associate { (_, value) -> value.first to propositionList.count { it.second.first == value.first } }
        // Don't worry it makes sense.
        propositionList.forEach { (elfKey, proposition) ->
            val elf = elfMap[elfKey]!!
            if (propositionCount[proposition.first] == 1) {
                proposition.second(elf)
                elfMap.remove(elfKey)
                elfMap[proposition.first] = elf
            }
        }
        return propositionList.isNotEmpty()
    }

    override fun firstPart(): String {
        (1..10).forEach { _ -> round() }
        val edgeX = elfMap.keys.minOf { it.first } to elfMap.keys.maxOf { it.first }
        val edgeY = elfMap.keys.minOf { it.second } to elfMap.keys.maxOf { it.second }
        return ((edgeX.second - edgeX.first + 1) * (edgeY.second - edgeY.first + 1) - elfMap.size).toString()
    }

    override fun secondPart(): String {
        var curRound = 11
        while (round()) {
            curRound++
            println(curRound)
        }
        return curRound.toString()
    }
}