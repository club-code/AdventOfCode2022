class Day3 : DaySolver(3, "Rucksack Reorganization") {
    override fun firstPart() =
        data.map {
            // On coupe la string en 2
            it.chunked(it.length / 2)
        }.map {
            // On ne garde que les char qui sont présents dans les deux Strings
            it[0].filter { c -> it[1].contains(c) }.toSet()
        }.sumOf { it.sumOf { c -> c.priority() } }.toString()
    // Et on somme

    override fun secondPart() = data.chunked(3) // On fait les groupes de trois
        .map { group ->
            // Puis on trouve le char présent dans tous les groups
        group[0].filter { c -> group[1].contains(c) && group[2].contains(c) }.first()
    }.sumOf {
        it.priority()
    }.toString()

    // On pourrait utiliser des sets et des .intersect mais c'et beaucoup plus long (environ 20 fois plus)


    private fun Char.priority() = when {
        (this.isLowerCase()) -> this.toInt() - 97 + 1
        else -> this.toInt() - 65 + 27
    }
}