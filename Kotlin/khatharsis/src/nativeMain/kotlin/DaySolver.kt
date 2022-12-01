import kotlinx.cinterop.*
import platform.posix.*
import kotlin.time.ExperimentalTime
import kotlin.time.measureTime

open class DaySolver(val day: Int, val name: String) {
    open fun firstPart(): String = "First part isn't done yet."
    open fun secondPart(): String = "Second part isn't done yet."

    @OptIn(ExperimentalTime::class)
    fun solve() {
        val time = measureTime {
            println("Solving for day $day: $name")
            println("   Part 1: ${firstPart()}")
            println("   Part 2: ${secondPart()}")
        }
        println("   Time taken: $time")
    }
    val data: List<String> = run {
        val command = "curl https://adventofcode.com/2022/day/$day/input " +
                "-H \"Cookie:session=$cookie\""
        println(command)
        val fp = popen(command, "r")

        val stdout = buildString {
            val buffer = ByteArray(4096)
            while (true) {
                val input = fgets(buffer.refTo(0), buffer.size, fp) ?: break
                append(input.toKString())
            }
        }

        val status = pclose(fp)
        if (status != 0) {
            error("Failed to get input from server: status $status")
        }
        stdout.split('\n')
    }
}

val cookie: String = run {
    val returnBuffer = StringBuilder()
    val file = fopen("cookie", "r") ?: throw IllegalArgumentException("Could not open cookie file")
    try {
        memScoped {
            val readBufferLength = 64 * 1024
            val buffer = allocArray<ByteVar>(readBufferLength)
            var line = fgets(buffer, readBufferLength, file)?.toKString()
            while (line != null) {
                returnBuffer.append(line)
                line = fgets(buffer, readBufferLength, file)?.toKString()
            }
        }
    } finally {
        fclose(file)
    }
    returnBuffer.toString()
}
