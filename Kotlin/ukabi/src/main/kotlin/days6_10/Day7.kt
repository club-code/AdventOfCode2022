package days6_10

import input7

class File(val name: String, val size: Int)
class Dir(val parent: Dir? = null, private val name: String) {

    private val subDirs = mutableMapOf<String, Dir>()
    private val files = mutableMapOf<String, File>()

    fun getDir(name: String) = this.subDirs.getOrDefault(name, Dir(this, name))

    fun addSubDir(name: String) = this.subDirs.set(name, Dir(this, name))
    fun addFile(name: String, size: Int) = this.files.set(name, File(name, size))

    fun getSize(): Int  = this.subDirs.values.sumOf { it.getSize() } + this.files.values.sumOf { it.size }

    fun drawTree(offset: Int = 0) {
        println("${" ".repeat(offset)}-${this.name} ${this.getSize()}")
        this.subDirs.values.forEach { it.drawTree(offset + 1) }
        this.files.values.forEach { println("${" ".repeat(offset + 1)}${it.name} ${it.size}") }
    }

    fun exploreAbove(threshold: Int): List<Dir> {
        val toAdd = mutableListOf<Dir>()
        for (node in this.subDirs.values) {
            if (node.getSize() >= threshold) {
                toAdd.add(node)
            }
        }

        return toAdd + this.subDirs.values.map { it.exploreAbove(threshold) }.flatten()
    }

    fun exploreBellow(threshold: Int): List<Dir> {
        val toAdd = mutableListOf<Dir>()
        for (node in this.subDirs.values) {
            if (node.getSize() <= threshold) {
                toAdd.add(node)
            }
        }

        return toAdd + this.subDirs.values.map { it.exploreBellow(threshold) }.flatten()
    }

}

fun day7(input: String): Dir {
    var root: Dir? = null
    var cursor: Dir? = null
    input
        .split("\n")
        .forEach {
            if (it.startsWith("$ ")) {
                val request = it.substring(2).split(" ")
                val command = request[0]
                val target = request.getOrNull(1)

                when (command) {
                    "cd" -> when (target) {
                        "/" -> {
                            root = Dir(null, "root")
                            cursor = root
                        }
                        ".." -> cursor = cursor!!.parent
                        else -> cursor = cursor!!.getDir(target!!)
                    }
                }
            }
            else {
                val reply = it.split(" ")
                val sizeOrType = reply[0]
                val name = reply[1]

                when (sizeOrType) {
                    "dir" -> cursor!!.addSubDir(name)
                    else -> cursor!!.addFile(name, sizeOrType.toInt())
                }
            }
        }

    return root!!
}

fun day7a(input: String): Int = day7(input).exploreBellow(100000).sumOf { it.getSize() }
fun day7b(input: String): Int =
    day7(input)
        .run {
            val threshold = 30000000 - (70000000 - this.getSize())
            return@run this.exploreAbove(threshold).minWith { d1, d2 -> d1.getSize().compareTo(d2.getSize()) }
        }
        .getSize()

fun main(args: Array<String>) {
    println(day7a(input7))
    println(day7b(input7))
}