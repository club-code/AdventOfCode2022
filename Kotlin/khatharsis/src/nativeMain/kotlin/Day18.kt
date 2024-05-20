class Day18 : DaySolver(18, "Boiling Boulders") {
    private val pointSet = data
        .map { it.split(',').map { s -> s.toInt() } }
        .map { Coordinates3D(it[0], it[1], it[2]) }

    override fun firstPart() = pointSet.sumOf {
        it.getNeighbours().filterNot { it in pointSet }.size
    }.toString()

    override fun secondPart(): String {
//        val airNeighbourSet = pointSet.map { it.getNeighbours() }.flatten().toSet()
//            .filterNot { it in pointSet }
//        val a = airNeighbourSet.filter { pointSet.containsAll(it.getNeighbours()) }
//        return (firstPart - a.size*6).toString()
        // Bonne idée, mais ne fonctionne que pour les poches d'air de taille 1 !
        // A la place on va faire un floodfill
        val xBounds = pointSet.minOf { it.first } - 1..pointSet.maxOf { it.first } + 1
        val yBounds = pointSet.minOf { it.second } - 1..pointSet.maxOf { it.second } + 1
        val zBounds = pointSet.minOf { it.third } - 1..pointSet.maxOf { it.third } + 1
        // On met les +1 pour être sûr d'atteindre tous les recoins
        val visited = mutableSetOf<Coordinates3D>()
        val toVisit = mutableSetOf(Coordinates3D(xBounds.first, yBounds.first, zBounds.first))
        while (toVisit.isNotEmpty()) {
            val curCube = toVisit.random()
            toVisit.remove(curCube)
            visited.add(curCube)
            toVisit.addAll(
                curCube.getNeighbours()
                    .filterNot { it in pointSet || it in visited }
                    .filter { it.first in xBounds && it.second in yBounds && it.third in zBounds }
            )
        }
        return pointSet.sumOf { p -> p.getNeighbours().count { it !in pointSet && it in visited } }.toString()
    }
}