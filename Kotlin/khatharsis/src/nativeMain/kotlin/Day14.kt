class Day14 : DaySolver(14, "Regolith Reservoir") {
    private sealed interface Block {
        object Sand : Block
        object Rock : Block
    }

    private val world: MutableMap<Vector, Block> = data
        .map { line ->
            line
                .split(" -> ")
                .map { couple ->
                    couple.split(",")
                        .let { it[0].toInt() to it[1].toInt() }
                }
                .zipWithNext()
        }
        .map { line ->
            line.map { (origin, destination) ->
                (if (origin.first == destination.first) {
                    ((origin.second..destination.second) + (destination.second..origin.second)).map { origin.first to it }
                } else ((origin.first..destination.first) + (destination.first..origin.first)).map { it to origin.second })
                    .map { it to Block.Rock }
            }.flatten()
        }.flatten().toMap().toMutableMap()

    private val pouringPoint = 500 to 0
    private val abyssAbscissa = world.filterValues { it is Block.Rock }.keys.maxOf { it.second }
    // Any block of sand falling below that shall be lost to the abyss

    private fun sandGoesDownward(curPosition: Vector): Vector {
        if (curPosition.second == abyssAbscissa + 1) return curPosition
        for (delta in listOf(0, -1, 1)) {
            // Check for rock floor
            val tryNewPosition = curPosition.first + delta to curPosition.second + 1
            if (!world.containsKey(tryNewPosition)) {
                return tryNewPosition
            }
        }
        return curPosition
    }

    private fun placeSand(maxFloor: Int): Vector {
        var curPosition = pouringPoint
        while (curPosition != sandGoesDownward(curPosition).also {
                curPosition = it
            } && curPosition.second < maxFloor) {
            /*Do Nothing*/
        }
        if (curPosition.second < maxFloor) world[curPosition] = Block.Sand
        return curPosition
    }


    override fun firstPart(): String {
        while (placeSand(abyssAbscissa).second < abyssAbscissa) {/*Do Nothing*/ }
        return world.count { it.value is Block.Sand }.toString()
    }

    override fun secondPart(): String {
        while (placeSand(abyssAbscissa+2) != pouringPoint) {/*Do Nothing*/}
        return world.count { it.value is Block.Sand }.toString()
    }
}