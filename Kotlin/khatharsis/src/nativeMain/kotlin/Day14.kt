class Day14 : DaySolver(14, "Regolith Reservoir") {
    private sealed interface Block {
        object Sand : Block
        object Rock : Block
    }

    private val world: MutableMap<Vector, Block> = data
        .map { line ->
            line.split(" -> ")
                .map { it.split(",") }
                .map { it[0].toInt() to it[1].toInt() }
                .zipWithNext()
        }.flatten() // List<Pair<Vector, Vector>>
        .map { (origin, destination) ->
            // Creates a line of Vector which shall be rocks
            (if (origin.first == destination.first) {
                (if (origin.second <= destination.second) {
                    origin.second..destination.second
                } else origin.second downTo destination.second)
                    .map { origin.first to it }
            } else
                (if (origin.first <= destination.first) {
                    origin.first..destination.first
                } else origin.first downTo destination.first)
                    .map { it to origin.second })
        }.flatten().associateWith { Block.Rock }.toMutableMap()


    private val pouringPoint = 500 to 0
    private val abyssAbscissa = world.filterValues { it is Block.Rock }.keys.maxOf { it.second }

    // Any block of sand falling below that shall be lost to the abyss
    private val path = mutableListOf<Vector>()
    // This is a way to remember the current direct path of our sand blocks

    /**
     * Given a vector (current position), returns the next position this block of sand should go.
     */
    private fun sandGoesDownward(curPosition: Vector): Vector {
        // Rocky floor
        if (curPosition.second == abyssAbscissa + 1) return curPosition
        // Go down, left or right
        for (delta in listOf(0, -1, 1)) {
            // Check for rock floor
            val tryNewPosition = curPosition.first + delta to curPosition.second + 1
            if (!world.containsKey(tryNewPosition)) {
                return tryNewPosition
            }
        }
        // If nothing worked, shouldn't move
        return curPosition
    }

    private fun placeSand(maxFloor: Int): Vector {
        // Let's start where we left off (or at the pouring Point)
        var curPosition = path.lastOrNull() ?: pouringPoint

        // While our current position isn't a stable one
        // And we're not pass the maxFloor given
        while (curPosition != sandGoesDownward(curPosition).also {
                curPosition = it
            } // This is to update the curPosition
            && curPosition.second < maxFloor) {
            // Let's add this position to the path.
            path.add(curPosition)
        }
        if (curPosition.second < maxFloor) {
            // The last position is the current one
            // But it's going to be used now, so remove it
            path.removeLastOrNull()
            world[curPosition] = Block.Sand
        }
        // Return the position where the block was placed
        // (Or, if curPosition.second >= maxFloor, if it wasn't placed !)
        return curPosition
    }


    override fun firstPart(): String {
        while (placeSand(abyssAbscissa).second < abyssAbscissa) {
            //Do Nothing
        }
        return world.count { it.value is Block.Sand }.toString()
    }

    override fun secondPart(): String {
        while (placeSand(abyssAbscissa + 2) != pouringPoint) {
            //Do Nothing
        }
        return world.count { it.value is Block.Sand }.toString()
    }
}