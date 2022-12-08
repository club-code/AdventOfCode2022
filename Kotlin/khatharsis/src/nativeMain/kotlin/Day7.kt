class Day7 : DaySolver(7, "No Space Left On Device") {
    sealed interface SystemFile {
        val name: String
        val size: Long

        class File(override val name: String, override val size: Long) : SystemFile

        class Directory(override val name: String, val parent: Directory?) : SystemFile {
            // All the subdirs and files
            val content = mutableListOf<SystemFile>()

            // Cur file, only calculated once
            override val size: Long by lazy { content.sumOf { it.size } }

            // Cur depth, only calculated once
            private val depth: Int by lazy { if (name == "/") 0 else (parent!!.depth + 1) }

            // Simple toString fun for debugging
            override fun toString(): String {
                return " ".repeat(depth) + "- $name: \n" + content.fold("") { acc, line ->
                    acc + when (line) {
                        is Directory -> line.toString()
                        is File -> " ".repeat(depth + 1) + "- ${line.name}\n"
                    }
                }
            }
        }
    }

    private val baseDir = SystemFile.Directory("/", null)
    private val dirList = mutableListOf(baseDir)

    private fun execCommand(
        commandLine: List<String>,
        stdout: List<String>,
        curDir: SystemFile.Directory
    ): SystemFile.Directory {
        if (commandLine.first() == "cd") {
            return when (commandLine.last()) {
                "/" -> baseDir
                ".." -> curDir.parent!!
                else -> curDir.content.filterIsInstance<SystemFile.Directory>()
                    .first { it.name == commandLine.last() }
            }
        } else {
            // We're using "ls"
            // So we need to create the files and dirs
            stdout.forEach { s ->
                s.split(" ").let {
                    curDir.content.add(
                        if (it.first() == "dir") {
                            SystemFile.Directory(it.last(), curDir).also { newDir -> dirList.add(newDir) }
                        } else SystemFile.File(it.last(), it.first().toLong())
                    )
                }

            }
            return curDir
        }
    }

    // Parsing is a bit complex, but essentialy we're just mapping the commands to their outputs
    private val commands = run {
        val line2commands = data.mapIndexed { i, line -> i to line }
            .filter { it.second.first() == '$' }
            .map { it.first to it.second.drop(2).split(" ") }
        val stdouts = line2commands.zipWithNext().map { (curCom, nextCom) ->
            data.subList(curCom.first + 1, nextCom.first)
        } + listOf(data.subList(line2commands.last().first + 1, data.size))
        return@run line2commands.map { it.second }.zip(stdouts)
    }

    override fun firstPart(): String {
        var curDir = baseDir
        commands.forEach { (command, stdout) ->
            curDir = execCommand(command, stdout, curDir)
        }
        val maxSize = 100000
        return dirList.filter { it.size <= maxSize }.sumOf { it.size }.toString()
    }


    override fun secondPart(): String {
        val totalDiskSpace = 70000000
        val neededUnusedSpace = 30000000
        val curUnusedSpace = totalDiskSpace - baseDir.size
        val needFreeSpace = neededUnusedSpace - curUnusedSpace
        return dirList.filter { it.size >= needFreeSpace }.minByOrNull { it.size }!!.size.toString()
    }
}