class Day6 : DaySolver(6, "Tuning Trouble") {
    fun String.findFirstMarker(length: Int): Pair<Int, String> =
        this.windowed(length)
            .let {
                it.first { s -> s.all { c1 -> s.count { c2 -> c2 == c1 } == 1 } }
                    .let { marker -> it.indexOf(marker) + length to marker }
            }

    override fun firstPart(): String = (data.first().findFirstMarker(4).first).toString()
    override fun secondPart(): String = (data.first().findFirstMarker(14).first).toString()
}