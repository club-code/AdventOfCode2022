class Day13 : DaySolver(13, "Distress Signal") {
    private val newData = data.groupBySeparatorBlank()
        .map { group -> group.map { it.toPacket() } }

    override fun firstPart(): String {
        return newData
            .mapIndexed { i, value -> i to value }
            .map { (index, couple) -> index + 1 to (couple[0] <= couple[1]) }
            .filter { it.second }
            .sumOf { it.first }
            .toString()
    }

    override fun secondPart(): String {
        val dividers = listOf("[[2]]", "[[6]]")
        val temp = (newData.flatten() + dividers.map { it.toPacket() }).sorted()
            .map { it.toString() }//.also { it.forEach { println(it) } }
        return dividers.fold(1) { acc, s -> acc * (temp.indexOf(s) + 1) }.toString()
    }


    sealed interface Packet : Comparable<Packet>

    class DataInteger(val value: Int) : Packet {
        override fun compareTo(other: Packet): Int = when (other) {
            is DataInteger -> this.value.compareTo(other.value)
            is DataList -> if (other.size < 1) 1
            else when (this.compareTo(other[0])) {
                -1 -> -1
                0 -> if (other.size == 1) 0 else -1
                else -> 1
            }
        }

        override fun toString() = value.toString()
    }

    class DataList(list: List<Packet>) : Packet, List<Packet> by list {
        override fun compareTo(other: Packet): Int {
            return when (other) {
                is DataInteger -> -other.compareTo(this)
                is DataList -> {
                    if (other.size == this.size &&
                        this.zip(other).all { it.first.compareTo(it.second) == 0 }
                    ) return 0 // They're equal
                    if (other.size > this.size) {
                        // This will run out first
                        for (i in this.indices) {
                            val temp = this[i].compareTo(other[i])
                            if (temp != 0) return temp
                        }
                        // All indices are equal
                        // The smallest is thus the shortest
                        return -1
                    } else {
                        // Other will run out first
                        for (i in other.indices) {
                            val temp = this[i].compareTo(other[i])
                            if (temp != 0) return temp
                        }
                        // All indices are equal so far
                        // The smallest is thus the shortest
                        return 1
                    }
                }
            }
        }

        override fun toString() = joinToString(", ", "[", "]")
    }

    private fun String.toPacket(): Packet {
        val listOfList = mutableListOf<MutableList<Packet>>()
        val regex = Regex("(?<=(\\[|,|\\]))|(?=(\\[|,|\\]))")
        // Drop 1 because we start with a [, and a such the first element is a nullString
        this.split(regex).drop(1).forEach { s ->
            when (s) {
                "[" -> listOfList.add(mutableListOf())
                "]" -> listOfList.removeLast().also {
                    if (listOfList.isNotEmpty())
                        listOfList.last().add(DataList(it))
                    else return DataList(it)
                }

                "," -> {/*Do Nothing*/
                }

                else -> listOfList.last().add(DataInteger(s.toInt()))
            }
        }
        throw Exception("Error while parsing I guess.")
    }
}
