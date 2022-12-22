class Day22 : DaySolver(22, "Monkey Map") {
    private val path = data.last()
    private val map = data.dropLast(2).mapIndexed { y, line ->
        line.mapIndexedNotNull { x, c ->
            when (c) {
                '#' -> Coordinates(x, y) to Block.WALL
                '.' -> Coordinates(x, y) to Block.PATH
                else -> null
            }
        }
    }.flatten().toMap()

    private val faceList = listOf(
        Face(1, map.keys.filter { it.first in 50 until 100 && it.second in 0 until 50 }.toSet()),
        Face(2, map.keys.filter { it.first in 100 until 150 && it.second in 0 until 50 }.toSet()),
        Face(3, map.keys.filter { it.first in 50 until 100 && it.second in 50 until 100 }.toSet()),
        Face(4, map.keys.filter { it.first in 50 until 100 && it.second in 100 until 150 }.toSet()),
        Face(5, map.keys.filter { it.first in 0 until 50 && it.second in 100 until 150 }.toSet()),
        Face(6, map.keys.filter { it.first in 0 until 50 && it.second in 150 until 200 }.toSet()),
    )

    private enum class Block { WALL, PATH; }

    // Actually useless since I could use booleans but hey.
    private enum class Facing {
        RIGHT, DOWN, LEFT, UP;

        fun rotateClockwise() = Facing.values()[(Facing.values().indexOf(this) + 1).mod(4)]
        fun rotateAntiClockwise() = Facing.values()[(Facing.values().indexOf(this) - 1).mod(4)]
    }

    private class Face(val number: Int, val points: Set<Coordinates>) {
        val startingLine = points.minOf { it.second }
        val startingColumn = points.minOf { it.first }
        val endingLine = startingLine + 50 - 1
        val endingColumn = startingColumn + 50 - 1
        fun contains(point: Coordinates) = points.contains(point)
    }

    private inline fun Coordinates.advance(facing: Facing) = when (facing) {
        Facing.UP -> this.first to this.second - 1
        Facing.DOWN -> this.first to this.second + 1
        Facing.LEFT -> this.first - 1 to this.second
        Facing.RIGHT -> this.first + 1 to this.second
    }

    private inline fun Coordinates.loopBack(facing: Facing) = when (facing) {
        Facing.UP -> map.keys.filter { it.first == this.first }.maxBy { it.second }
        Facing.DOWN -> map.keys.filter { it.first == this.first }.minBy { it.second }
        Facing.RIGHT -> map.keys.filter { it.second == this.second }.minBy { it.first }
        Facing.LEFT -> map.keys.filter { it.second == this.second }.maxBy { it.first }
    }

    private val associationMap = mapOf(
        (faceList[0] to Facing.UP) to (faceList[5] to Facing.RIGHT),
        (faceList[0] to Facing.LEFT) to (faceList[4] to Facing.RIGHT),

        (faceList[1] to Facing.UP) to (faceList[5] to Facing.UP),
        (faceList[1] to Facing.RIGHT) to (faceList[3] to Facing.LEFT),
        (faceList[1] to Facing.DOWN) to (faceList[2] to Facing.LEFT),

        (faceList[2] to Facing.RIGHT) to (faceList[1] to Facing.UP),
        (faceList[2] to Facing.LEFT) to (faceList[4] to Facing.DOWN),

        (faceList[3] to Facing.RIGHT) to (faceList[1] to Facing.LEFT),
        (faceList[3] to Facing.DOWN) to (faceList[5] to Facing.LEFT),

        (faceList[4] to Facing.LEFT) to (faceList[0] to Facing.RIGHT),
        (faceList[4] to Facing.UP) to (faceList[2] to Facing.RIGHT),

        (faceList[5] to Facing.LEFT) to (faceList[0] to Facing.DOWN),
        (faceList[5] to Facing.RIGHT) to (faceList[3] to Facing.UP),
        (faceList[5] to Facing.DOWN) to (faceList[1] to Facing.DOWN)
    )

    private fun Coordinates.cubeLoopBack(facing: Facing): Pair<Coordinates, Facing> {
        val curFace = faceList.first { it.contains(this) }
        val (newFace, newDir) = associationMap[curFace to facing]
            ?: throw IllegalArgumentException("This combination doesn't exist: $curFace $facing")
        // Ok now we need to actually get to know how this works
        val newPos = when (facing to newDir) {
            // No weird rotation
            (Facing.UP to Facing.UP) -> (first - curFace.startingColumn + newFace.startingColumn) to newFace.endingLine
            (Facing.LEFT to Facing.RIGHT) -> (newFace.startingColumn) to (newFace.endingLine - (second - curFace.startingLine))
            (Facing.RIGHT to Facing.LEFT) -> (newFace.endingColumn) to (newFace.endingLine - (second - curFace.startingLine))
            (Facing.DOWN to Facing.DOWN) -> (first - curFace.startingColumn + newFace.startingColumn) to newFace.startingLine
            // Rotation
            (Facing.UP to Facing.RIGHT) -> newFace.startingColumn to (first - curFace.startingColumn + newFace.startingLine)
            (Facing.LEFT to Facing.DOWN) -> (second - curFace.startingLine + newFace.startingColumn) to newFace.startingLine
            (Facing.RIGHT to Facing.UP) -> (second - curFace.startingLine + newFace.startingColumn) to newFace.endingLine
            (Facing.DOWN to Facing.LEFT) -> newFace.endingColumn to (first - curFace.startingColumn + newFace.startingLine)
            else -> throw IllegalArgumentException("This combination doesn't exist: $facing $newDir")
        }
        return newPos to newDir
    }

    private fun magicFunction(lambda: (Coordinates, Facing) -> Pair<Coordinates?, Facing>): Int {
        var direction = Facing.RIGHT
        var position = map.keys.filter { it.second == 0 && map[it] != Block.WALL }.minBy { it.first }
        val test = Regex("\\d+|R|L")
        test.findAll(path).map { it.groupValues.first() }
            .forEach { instruction ->
                when (instruction) {
                    "R" -> direction = direction.rotateClockwise()
                    "L" -> direction = direction.rotateAntiClockwise()
                    else -> {
                        val nStep = instruction.toInt()
                        for (curStep in 1..nStep) {
                            val (tempNewPosition, tempNewDirection) = lambda(position, direction)
                            if (tempNewPosition != null) {
                                position = tempNewPosition
                                direction = tempNewDirection
                            } else break
                        }
                    }
                }
            }
        // Leftmost open tile
        return (position.second + 1) * 1000 + (position.first + 1) * 4 + Facing.values().indexOf(direction)
    }

    override fun firstPart() = magicFunction { position, direction ->
        val tempPos = position.advance(direction).let {
            if (map.containsKey(it)) it else it.loopBack(direction)
        }
        when (map[tempPos]!!) {
            Block.PATH -> tempPos
            Block.WALL -> null
        } to direction
    }.toString()

    override fun secondPart() = magicFunction { position, direction ->
        val (tempPos, tempDir) = position.advance(direction).let {
            if (map.containsKey(it)) it to direction
            else position.cubeLoopBack(direction)
        }
        when (map[tempPos]!!) {
            Block.PATH -> tempPos
            Block.WALL -> null
        } to tempDir
    }.toString()
}
