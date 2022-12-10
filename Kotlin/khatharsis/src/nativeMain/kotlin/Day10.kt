import platform.posix.abs

class Day10 : DaySolver(10, "Cathode-Ray Tube") {
    private var x = 1
    private fun executeCycle(instruction: String, lambda: (Int) -> Unit) {
        lambda(x)
        if (instruction != "noop") {
            lambda(x)
            x += instruction.split(" ").last().toInt()
        }
    }

    override fun firstPart(): String {
        x = 1
        var cycleNumber = 0
        var sumOfSignalStrength = 0
        data.forEach { instruction ->
            executeCycle(instruction) {x->
                cycleNumber++
                if ((cycleNumber - 20) % 40 == 0) {
                    sumOfSignalStrength += cycleNumber * x
                }
            }
        }
        return sumOfSignalStrength.toString()
    }

    override fun secondPart(): String {
        x = 1
        val screen = List(6) { CharArray(40) { ' ' } }
        var cycleNumber = 0
        data.forEach { instruction ->
            executeCycle(instruction) { _ ->
                cycleNumber++
                if (abs(cycleNumber % 40 - (x+1)) <= 1)
                    screen[cycleNumber / 40][cycleNumber % 40] = '#'
            }
        }
        return screen.fold("") { acc, chars -> acc + "\n" + chars.concatToString() }
    }
}