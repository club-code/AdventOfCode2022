class Day3 : DaySolver(3, "Rucksack Reorganization") {
    override fun firstPart() =
        data.sumOf {s->
            // On coupe la string en 2
            s.chunked(s.length / 2).let {
                // On ne prends que le char qui est contenu dans les deux Strings
                it[0].first { c -> it[1].contains(c) }
            }.priority()
        }.toString()

    override fun secondPart() = data.chunked(3) // On fait les groupes de trois
        .sumOf { group ->
            // Puis on trouve le char présent dans tous les groups
            group[0].first { c -> group[1].contains(c) && group[2].contains(c) }.priority()
        }.toString()

    // On pourrait utiliser des sets et des .intersect mais c'et beaucoup plus long (environ 20 fois plus)


    private fun Char.priority() = if (this.isLowerCase()) this - 'a' + 1
        else this - 'A' + 27
}