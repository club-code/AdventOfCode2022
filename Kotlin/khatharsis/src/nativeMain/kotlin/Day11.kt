class Day11 : DaySolver(11, "Monkey in the Middle") {
    class Monkey(
        val number: Int,
        startingItems: List<Long>,
        val operation: (Long) -> Long,
        val divisor: Int,
        val trueMonkey: Int,
        val falseMonkey: Int
    ) {
        private val items = startingItems.toMutableList()
        var numberOfItems = 0UL
        override fun toString(): String {
            return "Monkey $number: inspectedItems = $numberOfItems, items = $items"
        }

        fun inspect() {
            (0 until items.size).forEach { i ->
                items[i] = operation(items[i])
                numberOfItems++
            }
        }

        fun simplify(operation: (Long) -> Long) {
            (0 until items.size).forEach { i ->
                items[i] = operation(items[i])
            }
        }

        fun sendItems(monkeyList: List<Monkey>) {
            items.forEach { item ->
                monkeyList[if (item % divisor == 0L) trueMonkey else falseMonkey].addItem(item)
            }
            items.clear() // No monkey sends to itself
        }

        private fun addItem(item: Long) = items.add(item)
    }

    // Make the Monkey
    private val headRegex = Regex("Monkey (\\d+):")
    private fun getMonkeyList(): List<Monkey> = data.groupBySeparatorBlank()
        .map { group ->
            Monkey(
                number = headRegex.matchEntire(group[0])!!.groupValues.last().toInt(),
                startingItems = group[1]
                    .substringAfter(": ")
                    .replace(",", "") // We don't want the commas
                    .split(" ")
                    .map { it.toLong() },
                operation = group[2]
                    .substringAfter("old ") // Starts after the first "old"
                    .split(" ") // Separate the operator and the argument
                    .let {
                        if (it.last() == "old")
                            if (it.first() == "+") { old -> 2 * old }
                            else { old -> old * old }
                        else {
                            val other = it.last().toInt()
                            if (it.first() == "+") { old -> old + other }
                            else { old -> old * other }
                        }
                    },
                divisor = group[3].substringAfterLast(" ").toInt(),
                trueMonkey = group[4].substringAfterLast(" ").toInt(),
                falseMonkey = group[5].substringAfterLast(" ").toInt()
            )
        }

    override fun firstPart(): String {
        val monkeyList = getMonkeyList()
        (1..20).forEach { round ->
            monkeyList.forEach { monkey ->
                monkey.inspect()
                monkey.simplify { i -> i / 3 }
                monkey.sendItems(monkeyList)
            }
        }
        val (max1, max2) = monkeyList.sortedByDescending { it.numberOfItems }.take(2)
        return (max1.numberOfItems * max2.numberOfItems).toString()
    }

    override fun secondPart(): String {
        val monkeyList = getMonkeyList()
        val commonDivisor = monkeyList.fold(1) { acc, i -> acc*i.divisor}
        (1..10000).forEach { round ->
            monkeyList.forEach { monkey ->
                monkey.inspect()
                monkey.simplify {it%commonDivisor}
                monkey.sendItems(monkeyList)
            }
        }
        val (max1, max2) = monkeyList.sortedByDescending { it.numberOfItems }.take(2)
        return (max1.numberOfItems * max2.numberOfItems).toString()
    }
}