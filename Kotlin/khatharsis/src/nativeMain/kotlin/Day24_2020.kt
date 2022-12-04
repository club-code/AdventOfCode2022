class Day24_2020 : DaySolver(24, "Lobby Layout", 2020) {

    private val exampleData = """sesenwnenenewseeswwswswwnenewsewsw
        neeenesenwnwwswnenewnwwsewnenwseswesw
        seswneswswsenwwnwse
        nwnwneseeswswnenewneswwnewseswneseene
        swweswneswnenwsewnwneneseenw
        eesenwseswswnenwswnwnwsewwnwsene
        sewnenenenesenwsewnenwwwse
        wenwwweseeeweswwwnwwe
        wsweesenenewnwwnwsenewsenwwsesesenwne
        neeswseenwwswnwswswnw
        nenwswwsewswnenenewsenwsenwnesesenew
        enewnwewneswsewnwswenweswnenwsenwsw
        sweneswneswneneenwnewenewwneswswnese
        swwesenesewenwneswnwwneseswwne
        enesenwswwswneneswsenwnewswseenwsese
        wnwnesenesenenwwnenwsewesewsesesew
        nenewswnwewswnenesenwnesewesw
        eneswnwswnwsenenwnwnwwseeswneewsenese
        neswnwewnwnwseenwseesewsenwsweewe
        wseweeenwnesenwwwswnew"""
        .trim().split("\n")

    private val regex = Regex("se|sw|nw|ne|e|w")
    private val newData = data.map { s ->
        regex.findAll(s).map { it.value }.map {
            when (it) {
                "se" -> Direction.SOUTHEAST
                "sw" -> Direction.SOUTHWEST
                "e" -> Direction.EAST
                "w" -> Direction.WEST
                "nw" -> Direction.NORTHWEST
                "ne" -> Direction.NORTHEAST
                else -> throw Exception("Could not correctly parse input")
            }
        }.toList()
    }

    enum class Direction(val q: Int, val r: Int, val s: Int) {
        EAST(1, 0, -1),
        SOUTHEAST(0, 1, -1),
        SOUTHWEST(-1, 1, 0),
        WEST(-1, 0, 1),
        NORTHWEST(0, -1, 1),
        NORTHEAST(1, -1, 0);
    }

    private val hexagonMap = mutableMapOf(Triple(0, 0, 0) to Hexagon(0, 0, 0))
    // The starting Hexagon

    data class Hexagon(val q: Int, val r: Int, val s: Int, var color: Boolean = true) {
        fun getNeighbourOrCreate(
            direction: Direction,
            hexagonMap: MutableMap<Triple<Int, Int, Int>, Hexagon>
        ): Hexagon {
            val key = Triple(q + direction.q, r + direction.r, s + direction.s)
            if (!hexagonMap.containsKey(key)) {
                hexagonMap[key] = Hexagon(
                    q + direction.q,
                    r + direction.r,
                    s + direction.s
                )
            }
            return hexagonMap[key]!!
        }
        fun listNeighbours(hexagonMap: MutableMap<Triple<Int, Int, Int>, Hexagon>) = Direction.values().mapNotNull { direction ->
            hexagonMap[Triple(q + direction.q, r + direction.r, s + direction.s)]
        }
    }

    override fun firstPart(): String {
        newData.forEach { directions ->
            var curHexagon = hexagonMap[Triple(0, 0, 0)]!!
            directions.forEach { direction ->
                curHexagon = curHexagon.getNeighbourOrCreate(direction, hexagonMap)
            }
            curHexagon.color = !curHexagon.color
        }
        return hexagonMap.count { !it.value.color }.toString()
    }

    override fun secondPart(): String {
        val numberOfDays = 100
        var dayHexagonMap = hexagonMap
        (1..numberOfDays).forEach { day ->
            // Copy the dayHexagonMap, but only the black ones
            // since they're the only one (and their neighbours) that can change
            val bufferMap = mutableMapOf<Triple<Int, Int, Int>, Hexagon>()
            dayHexagonMap.filterValues { !it.color }.also { map ->
                // Copy values to the bufferMap
                map.mapValuesTo(bufferMap) {it.value.copy()}
            }.forEach {
                // Create neighbour if needed
                Direction.values().forEach { direction ->
                    it.value.getNeighbourOrCreate(direction, bufferMap)
                }
            }

            // Alternate the buffermap
            bufferMap.forEach { (_, value) ->
                val numBlackNeighbours = value.listNeighbours(dayHexagonMap).count { !it.color }
                // If tile is black (Nested if for protection)
                if (!value.color) {
                    if (numBlackNeighbours == 0 || numBlackNeighbours > 2) {
                        value.color = true
                    }
                }
                // If tile is white
                else if (value.color && numBlackNeighbours == 2) {
                    value.color = false
                }
            }

            // Change the dayHexagonMap
            dayHexagonMap = bufferMap
        }
        return dayHexagonMap.count {!it.value.color}.toString()
    }
}
