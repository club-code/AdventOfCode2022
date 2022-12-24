class Day19 : DaySolver(19, "Not Enough Minerals") {
    val testData =
        ("Blueprint 1: Each ore robot costs 4 ore." +
                " Each clay robot costs 2 ore." +
                " Each obsidian robot costs 3 ore and 14 clay." +
                " Each geode robot costs 2 ore and 7 obsidian.\n" +
                "Blueprint 2: Each ore robot costs 2 ore." +
                " Each clay robot costs 3 ore." +
                " Each obsidian robot costs 3 ore and 8 clay." +
                " Each geode robot costs 3 ore and 12 obsidian.").split("\n")
    val robotRegex =
        Regex("Blueprint (\\d+): Each ore robot costs (\\d+) ore. Each clay robot costs (\\d+) ore. Each obsidian robot costs (\\d+) ore and (\\d+) clay. Each geode robot costs (\\d+) ore and (\\d+) obsidian.")
    val newData = testData.map { robotRegex.matchEntire(it)!!.groupValues.drop(1).map { s -> s.toInt() } }
        .map { Blueprint(it[0], it[1], it[2], it[3] to it[4], it[5] to it[6]) }

    data class Blueprint(
        val id: Int,
        val oreRobotCost: Int,
        val clayRobotCost: Int,
        val obsidianRobotCost: Pair<Int, Int>,
        val geodeRobotCost: Pair<Int, Int>
    ) {
        fun getMaxQuantity(maxTime: Int): Int {
            val resources = MutableList(4) { 0 }
            // Ore, clay, obsidian, geode
            val robots = mutableListOf(1, 0, 0, 0)
            (1..maxTime).forEach { curMinute ->
                val oldRobots = robots.toList()
                println("-- Minute $curMinute --")
                if (resources[0] >= geodeRobotCost.first && resources[2] >= geodeRobotCost.second) {
                    resources[0] -= geodeRobotCost.first
                    resources[2] -= geodeRobotCost.second
                    robots[3] += 1
                }
                if (resources[0] >= obsidianRobotCost.first && resources[1] >= obsidianRobotCost.second) {
                    resources[0] -= obsidianRobotCost.first
                    resources[1] -= obsidianRobotCost.second
                    robots[2] += 1
                }
                if (resources[0] >= clayRobotCost) {
                    resources[0] -= clayRobotCost
                    robots[1]++
                }
                if (resources[0] >= oreRobotCost) {
                    resources[0]--
                    robots[0]++
                }
                oldRobots.forEachIndexed { index, n -> resources[index] += n }
                println("$oldRobots -> $resources")
                // Check if you can build any robots
            }
            return resources.last()
        }
    }

    override fun firstPart(): String {
        println(newData)
        newData.forEach { println(it.getMaxQuantity(24)) }
        return super.firstPart()
    }
}