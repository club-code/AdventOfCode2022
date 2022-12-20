import kotlin.math.max

class Day16 : DaySolver(16, "Proboscidea Volcanium") {
    private val exampleData = """Valve AA has flow rate=0; tunnels lead to valves DD, II, BB
Valve BB has flow rate=13; tunnels lead to valves CC, AA
Valve CC has flow rate=2; tunnels lead to valves DD, BB
Valve DD has flow rate=20; tunnels lead to valves CC, AA, EE
Valve EE has flow rate=3; tunnels lead to valves FF, DD
Valve FF has flow rate=0; tunnels lead to valves EE, GG
Valve GG has flow rate=0; tunnels lead to valves FF, HH
Valve HH has flow rate=22; tunnel leads to valve GG
Valve II has flow rate=0; tunnels lead to valves AA, JJ
Valve JJ has flow rate=21; tunnel leads to valve II""".split("\n")
    private val lineRegex = Regex("Valve (\\w+) has flow rate=(\\d+); tunnels? leads? to valves? (.+)")

    private val valveMap = data.map { lineRegex.matchEntire(it)!!.groupValues.drop(1) }
        .associate { it[0] to Valve(it[0], it[1].toInt(), it[2].split(", ")) }

    data class Valve(
        val id: String,
        val flowRate: Int,
        val neighbours: List<String>,
    )

    private fun Valve.getNeighbours() = neighbours.mapNotNull { valveMap[it] }

    // Map des distances entre les Valves.
    private val distanceMap = valveMap.map { it.key to mutableMapOf<String, Int>() }.toMap()

    // Vérifie si la valeur est dans la map sinon la compute et la met dans la map
    private fun Valve.distanceTo(other: Valve): Int =
        distanceMap[this.id]!![other.id] ?: (run {
            val visited = mutableSetOf<Valve>()
            val toVisit = mutableListOf(this to 0)
            while (toVisit.isNotEmpty()) {
                val curNode = toVisit.minBy { it.second }
                toVisit.remove(curNode)
                if (curNode.first == other) return@run curNode.second
                visited.add(curNode.first)
                curNode.first.getNeighbours()
                    .filter { !visited.contains(it) }
                    .forEach { toVisit.add(it to curNode.second + 1) }
            }
            0
        }.also { distanceMap[this.id]!![other.id] = it; distanceMap[other.id]!![this.id] = it })

    private val usefulValves = valveMap.values.filter { it.flowRate > 0 }

    // Anciennement utilisé dans Path.potential, mais la méthode a été améliorée depuis
    private val maxFlowRate = usefulValves.sumOf { it.flowRate }

    // Une classe représentant un Path, à une minute donnée
    // On part du principe que c'est un path partant de AA et prenant toujours le plus cours chemin entre
    // Le node où il est est le node suivant qu'il à ouvert (ie les nodes dans openedValves)
    // Le node sur lequel il est actuellement est curValve
    class Path(
        val curMinute: Int,
        val steamReleased: Int,
        val curValve: Valve,
        val openedValve: List<Valve>
    ) {
        val flowRate = openedValve.sumOf { it.flowRate }
        override fun toString() = "Path(curMinute=$curMinute, " +
                "steamReleased=$steamReleased @ $flowRate/min, " +
                "curValve=${curValve.id}, " +
                "openedValves=${openedValve.filter { it.flowRate > 0 }.joinToString(",", "[", "]") { it.id }})"
    }

    // Renvoie la liste des paths disponibles depuis celui ci
    private fun Path.getNextPaths(maxTime: Int) = usefulValves
        .filterNot { it in openedValve }
        .filter { it.distanceTo(curValve) + curMinute <= maxTime }
        .map {
            Path(
                curMinute + it.distanceTo(curValve) + 1, // Takes one minute to open it
                steamReleased + (it.distanceTo(curValve) + 1) * flowRate,
                it,
                openedValve + it

            )
        } // S'il n'y a aucune valve qui reste accessible, alors on n'a qu'à attendre.
        .takeUnless { it.isEmpty() } ?: listOf(
        Path(
            30,
            steamReleased + (flowRate * (30 - curMinute)),
            curValve,
            openedValve
        )
    )

    // Potentiel = Borne sup de la quantité de vapeur relachée
    // La formule potential = steamRelease + (maxTime - curMinute) * maxFlowrate est également vrai,
    // Mais donne une born sup plus haute.
    private fun Path.potential(maxTime: Int) = steamReleased +
            (maxTime - curMinute) * flowRate +
            usefulValves.filterNot { it in openedValve }
                .sumOf { max(0, (maxTime - curMinute - curValve.distanceTo(it))) * flowRate }


    override fun firstPart(): String {
        val maxTime = 30
        var maxPath: Path? = null
        val startingPoint = valveMap["AA"]!!
        val pathSet = mutableListOf(
            Path(
                0,
                0,
                startingPoint,
                valveMap.values.filter { it.flowRate == 0 },
            )
        )
        while (pathSet.isNotEmpty()) {
            val curPath = pathSet.maxBy { it.curMinute }
            pathSet.remove(curPath)
            if (curPath.curMinute > maxTime) continue
            if (maxPath == null || maxPath.steamReleased < curPath.steamReleased) {
                maxPath = curPath
                println("New max: $maxPath")
                if (maxPath.curMinute == maxTime)
                    pathSet.removeAll { it.potential(maxTime) < maxPath.steamReleased }
            }
            if (curPath.curMinute < maxTime) pathSet.addAll(
                if (maxPath.curMinute == maxTime)
                    curPath.getNextPaths(maxTime).filter {
                        it.potential(maxTime) >= maxPath.steamReleased
                    } else curPath.getNextPaths(maxTime)
            )
        }
        return maxPath?.steamReleased.toString()
    }
}