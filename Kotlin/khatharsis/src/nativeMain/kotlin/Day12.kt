class Day12 : DaySolver(12, "Hill Climbing Algorithm") {
    private val newData = data.map { it.toCharArray().toMutableList() }
    private fun Vector.getValue(): Char {
        return newData[this.first][this.second]
    }

    // Le point d'arrivé, on récupère surtout ses coordonées
    private val arrivalPosition = newData
        .indexOfFirst { it.contains('E') }
        .let { it to newData[it].indexOf('E') }
        .also {newData[it.first][it.second] = 'z' }

    // Map des points accessibles et de leur distance à l'arrivée
    private val accessiblePoints = mutableMapOf<Vector, Int>()

    override fun firstPart(): String {
        // Même chose que pour arrivalPoint
        val startingPosition = newData
            .indexOfFirst { it.contains('S') }
            .let { it to newData[it].indexOf('S') }
            .also {newData[it.first][it.second] = 'a' }

        val queue = mutableMapOf(arrivalPosition to 0)

        // On fait un Dijsktra inversé en prévoyant la partie 2
        while (queue.isNotEmpty()) {
            // Etonnement pas si gourmand que ça en perf
            val (curPosition, cost) = queue.minBy { it.value }
            queue.remove(curPosition)
            accessiblePoints[curPosition] = cost
            curPosition.getNeighbours(newData)
                .filter { !accessiblePoints.contains(it) } // Pas encore visité
                .filter { curPosition.getValue() - it.getValue() <= 1 } // Accessible
                .filter { !queue.containsKey(it) || queue[it]!! > cost + 1 }
                // Qui n'ont pas encore été vu
                // ou qui ont un moins bon chemin
                .forEach { queue[it] = cost + 1 }
        }
        return accessiblePoints[startingPosition]!!.toString()
    }

    override fun secondPart() =
        newData.mapIndexed { index: Int, chars: List<Char> ->
            chars.mapIndexed { index2: Int, c: Char ->
                (index to index2) to c
            }.filter { it.second == 'a' }.mapNotNull { accessiblePoints[it.first] }
        }.flatten() // This is a list of the possible starting points score distance to the E.
            .min().toString()

}