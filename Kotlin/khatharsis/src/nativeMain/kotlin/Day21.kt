class Day21 : DaySolver(21, "Monkey Math") {
    private val monkeyNumberRegex = Regex("(\\w+): (\\d+)")
    private val monkeyOperationRegex = Regex("(\\w+): (\\w+) ([+*/-]) (\\w+)")


    private val monkeyNumberMap = data.mapNotNull { monkeyNumberRegex.matchEntire(it) }
        .map { it.groupValues.drop(1) }
        .associate { it[0] to it[1].toULong() }

    private val monkeyOperationMap = data.mapNotNull { monkeyOperationRegex.matchEntire(it) }
        .map { it.groupValues.drop(1) }
        .associate { it[0] to Triple(it[1], it[2], it[3]) }

    override fun firstPart() =
        calculate(monkeyNumberMap.toMutableMap(), monkeyOperationMap.toMutableMap(), "root")!!.toString()

    override fun secondPart(): String {
        val monkeyOperationMap = monkeyOperationMap.toMutableMap()
        val monkeyNumberMap = monkeyNumberMap.toMutableMap()
        val dependant = mutableSetOf("humn")
        calculate(monkeyNumberMap, monkeyOperationMap, "root") { curOp, curOpArgs, stack ->
            if (curOpArgs.first in dependant || curOpArgs.third in dependant) {
                stack.remove(curOp)
                dependant.add(curOp)
                true
            } else false
        }
        // NB: We're gonna do a dichotomy
        // But we could also juste traceback from the root.
        var curTry = 0UL
        val valueToMatch =
            monkeyNumberMap[monkeyOperationMap["root"]!!.first] ?: monkeyNumberMap[monkeyOperationMap["root"]!!.third]!!
        val valueToCompute = monkeyOperationMap["root"]!!.first.takeIf { it in monkeyOperationMap }
            ?: monkeyOperationMap["root"]!!.second
        val baseValue = calculate(
            monkeyNumberMap.toMutableMap(),
            monkeyOperationMap.toMutableMap(),
            valueToCompute,
            curTry
        )!! compareTo valueToMatch
        var step = 1000_000_000_000U
        while (true) {
            curTry += step
            val result =
                calculate(monkeyNumberMap.toMutableMap(), monkeyOperationMap.toMutableMap(), valueToCompute, curTry)!!
            if (result == valueToMatch) return curTry.toString()
            if (baseValue * (result compareTo valueToMatch) < 0) {
                curTry -= step
                step /= 10u
            }
        }
    }

    private fun calculate(
        numberMap: MutableMap<String, ULong>,
        operationMap: MutableMap<String, Triple<String, String, String>>,
        startingValue: String,
        humnValue: ULong = monkeyNumberMap["humn"]!!,
        lambda: (String, Triple<String, String, String>, MutableSet<String>) -> (Boolean) = { _, _, _ -> false }
    ): ULong? {
        numberMap["humn"] = humnValue
        val stack = mutableSetOf(startingValue)
        while (stack.isNotEmpty()) {
            val curOp = stack.last()
            val curOpArgs = operationMap[curOp]!!
            if (lambda(curOp, curOpArgs, stack)) continue
            // Three choices
            if (numberMap.containsKey(curOpArgs.first) && numberMap.containsKey(curOpArgs.third)) {
                stack.remove(curOp)
                operationMap.remove(curOp)
                numberMap[curOp] = when (curOpArgs.second) {
                    "+" -> numberMap[curOpArgs.first]!! + numberMap[curOpArgs.third]!!
                    "-" -> numberMap[curOpArgs.first]!! - numberMap[curOpArgs.third]!!
                    "/" -> numberMap[curOpArgs.first]!! / numberMap[curOpArgs.third]!!
                    "*" -> numberMap[curOpArgs.first]!! * numberMap[curOpArgs.third]!!
                    else -> throw IllegalArgumentException("Wrong operand: ${curOpArgs.second}")
                }
                continue
            }
            if (operationMap.containsKey(curOpArgs.first)) {
                stack.add(curOpArgs.first)
            }
            if (operationMap.containsKey(curOpArgs.third)) {
                stack.add(curOpArgs.third)
            }
        }
        return numberMap[startingValue]
    }
}