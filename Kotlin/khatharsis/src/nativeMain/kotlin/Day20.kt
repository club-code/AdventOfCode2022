class Day20 : DaySolver(20, "Grove Positioning System") {
    val newData = data.map { it.toLong() }
        .mapIndexed { index, long -> LongWithIndex(long, index) }

    fun scramble(arrayList: MutableList<LongWithIndex>, order: List<LongWithIndex> = arrayList.toList()) =
        order.forEach { intIndexed ->
            val value = intIndexed.long
            val index = arrayList.indexOf(intIndexed)
            val newIndex = (index + value.mod(arrayList.size - 1)).mod(arrayList.size - 1)
            arrayList.remove(intIndexed)
            arrayList.add(newIndex, intIndexed.see())
        }


    override fun firstPart(): String {
        val array = ArrayList(newData)
        scramble(array)
        val zeroIndex = array.indexOf(array.first { it.long == 0L })
        return listOf(1000, 2000, 3000).sumOf { array[(it + zeroIndex).mod(array.size)].long }.toString()
    }

    private val decryptionKey = 811589153
    override fun secondPart(): String {
        val array = ArrayList(newData.map { it * decryptionKey })
        val order = array.toList()
        (1..10).forEach {_->
            scramble(array, order)
            array.forEach { it.unsee() }
        }
        val zeroIndex = array.indexOf(array.first { it.long == 0L })
        return listOf(1000, 2000, 3000).sumOf { array[(it + zeroIndex).mod(array.size)].long }.toString()
    }

    inner class LongWithIndex(val long: Long, private val index: Int, var seen: Boolean = false) {
        override fun toString() = long.toString()
        override fun equals(other: Any?) = if (other is LongWithIndex) long == other.long && index == other.index && seen == other.seen else false

        fun see() = LongWithIndex(long, index, true)
        fun unsee() { seen = false }

        operator fun times(factor: Int) = LongWithIndex(long * factor, index, seen)
        override fun hashCode(): Int  = (long.hashCode() * 31 + index.hashCode()) * 31 + seen.hashCode()
    }
}