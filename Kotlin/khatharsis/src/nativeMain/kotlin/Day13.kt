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
        override fun compareTo(other: Packet) = when (other) {
            is DataInteger -> this.value.compareTo(other.value)
            is DataList -> DataList(listOf(this)).compareTo(other)
        }

        override fun toString() = value.toString()
    }

    class DataList(val list: List<Packet>) : Packet {
        override fun compareTo(other: Packet): Int {
            return when (other) {
                is DataInteger -> this.compareTo(DataList(kotlin.collections.listOf(other)))
                is DataList -> {
                    if (other.list.size == this.list.size &&
                        this.list.zip(other.list).all { it.first.compareTo(it.second) == 0 }
                    ) return 0 // They're equal
                    if (other.list.size > this.list.size) {
                        // This will run out first
                        for (i in this.list.indices) {
                            val temp = this.list[i].compareTo(other.list[i])
                            if (temp != 0) return temp
                        }
                        // All indices are equal so far
                        // The smallest is thus the shortest
                        return -1
                    } else {
                        // Other will run out first
                        for (i in other.list.indices) {
                            val temp = this.list[i].compareTo(other.list[i])
                            if (temp != 0) return temp
                        }
                        // All indices are equal so far
                        // The smallest is thus the shortest
                        return 1
                    }
                }
            }
        }

        override fun toString() = list.joinToString(", ", "[", "]")
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
