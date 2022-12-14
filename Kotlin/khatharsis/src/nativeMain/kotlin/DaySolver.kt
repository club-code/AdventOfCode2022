import kotlinx.cinterop.*
import platform.linux.exec
import platform.posix.*
import kotlin.time.ExperimentalTime
import kotlin.time.measureTime

open class DaySolver(val day: Int, val name: String, val year: Int = 2022) {
    open fun firstPart(): String = "First part isn't done yet."
    open fun secondPart(): String = "Second part isn't done yet."

    @OptIn(ExperimentalTime::class)
    fun solve() {
        val time = measureTime {
            println("Solving for day $day of $year: $name")
            println("   Part 1: ${firstPart()}")
            println("   Part 2: ${secondPart()}")
        }
        println("   Time taken: $time")
    }
    val data: List<String> = run {
        system("mkdir -p inputs")
        val command = "if [ ! -f \"inputs/day$day.txt\" ]; then curl -s https://adventofcode.com/$year/day/$day/input " +
                "-H \"Cookie:session=$cookie\" -o inputs/day$day.txt; fi"
        system(command)
        val fp = popen("cat inputs/day$day.txt", "r")

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
        stdout.split('\n').dropLast(1)
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
