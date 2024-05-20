class Day17 : DaySolver(17, "Pyroclastic Flow") {
    enum class Shape(val width: Int, val height: UInt) {
        MINUS(4, 1u),
        PLUS(3, 3u),
        L(3, 3u),
        I(1, 4u),
        SQUARE(2, 2u);
    }

    inner class Rock(val x: Int, val y: ULong, val shape: Shape) {
        val body: Set<Pair<Int, ULong>> =
            when (shape) {
                Shape.MINUS -> setOf(
                    x to y,
                    x + 1 to y,
                    x + 2 to y,
                    x + 3 to y
                )

                Shape.PLUS -> setOf(
                    x + 1 to y,
                    x to y - 1u,
//                    x + 1 to y - 1u, This one is useless !
                    x + 2 to y - 1u,
                    x + 1 to y - 2u
                )

                Shape.L -> setOf(
                    x + 2 to y,
                    x + 2 to y - 1u,
                    x to y - 2u,
                    x + 1 to y - 2u,
                    x + 2 to y - 2u
                )

                Shape.I -> setOf(
                    x to y,
                    x to y - 1u,
                    x to y - 2u,
                    x to y - 3u
                )

                Shape.SQUARE -> setOf(
                    x to y,
                    x + 1 to y,
                    x + 1 to y - 1u,
                    x to y - 1u
                )
            }

        inline fun takeIfSpaceAvailable() = takeIf { nextRock ->
            rockSet
                .filter { it.second >= nextRock.y - shape.height + 1u }
                .none { it in nextRock.body }
        }

        inline fun fall() = Rock(x, y - 1u, shape).takeIfSpaceAvailable() ?: this

        fun push(direction: Char, chamberWidth: Int) =
            when {
                (direction == '>' && x + shape.width < chamberWidth) -> Rock(x + 1, y, shape).takeIfSpaceAvailable()
                (direction == '<' && x > 0) -> Rock(x - 1, y, shape).takeIfSpaceAvailable()
                else -> null
            } ?: this

        override fun toString() = "Rock(x=$x, y=$y, shape=$shape, body=$body"
    }

    val rockSet = mutableSetOf<Pair<Int, ULong>>()
    private val line = data.first()//">>><<><>><<<>><>>><<<>>><<<><<<>><>><<>>"
    var count = 0

    fun magicFunction(maxRange: Long): ULong {
        (0 until maxRange).forEach { rockNumber ->
            val shape = Shape.values()[(rockNumber % 5).toInt()]
            var curRock = Rock(2, rockSet.maxOf { it.second } + 3u + shape.height, shape)
//            println("Spawning $curRock")
            while (true) {
//                print("   Pushing it to ${line[(count) % line.length]}: ")
                curRock = curRock.push(line[(count++) % line.length], 7)
//                println(curRock)
                val newRock = curRock.fall()
                if (newRock == curRock) {
//                    println("   Couldn't fall anymore, rock is rested at (${curRock.x}, ${curRock.y})")
                    rockSet.addAll(curRock.body)
                    val possibleLine = rockSet.filter { it.second >= curRock.y - curRock.shape.height }
                        .groupBy { it.second }
                        .filter { it.value.size == 7 }
                        .keys.firstOrNull()
                    if (possibleLine != null) {
                        println("Full line at $possibleLine out of $maxRange, ie ${(possibleLine * 100u) / maxRange.toUInt()}% done !")
                        rockSet.removeAll { it.second < possibleLine }
                    }
                    break
                }
                curRock = newRock
            }
        }
        return (rockSet.maxOf { it.second })
    }

    override fun firstPart(): String {
        // Add ground to rockSet
        rockSet.addAll(List(7) { it to 0UL })
        return magicFunction(2022).toString()
    }

    override fun secondPart() = magicFunction(1_000_000_000_000).toString()
}