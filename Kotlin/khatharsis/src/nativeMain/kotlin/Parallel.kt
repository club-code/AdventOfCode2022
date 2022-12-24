import kotlinx.cinterop.cValue
import kotlinx.serialization.Serializable
import kotlinx.serialization.decodeFromString
import kotlinx.serialization.encodeToString
import kotlinx.serialization.json.Json
import platform.posix.*

val NUM_CORES = execAndStdOut("grep -c ^processor /proc/cpuinfo").removeSuffix("\n").toInt()

const val threadExecDir = "threadExecOutputs"

/**
 * Execute a lambda in parallel, where the lambda tkes the threadNumber as an argument.
 */
inline fun executeParallel(lambda: (Int) -> String?): List<String> {
    var threadNumber = 0
    val childrenList = mutableListOf<Int>()
    for (childrenNum in 1 until NUM_CORES) {
        val pid = fork()
        if (pid == 0) {
            threadNumber = childrenNum
            break
        } else childrenList.add(pid)
    }
    system("mkdir -p $threadExecDir")
    lambda(threadNumber)?.apply {
        system("echo \"${this}\" > $threadExecDir/$threadNumber")
    }
    if (threadNumber == 0) {
        childrenList.forEach { _ ->
            wait(cValue<__WAIT_STATUS> {})
        }
        return (0 until NUM_CORES).mapNotNull { responseThreadNumber ->
            if (system("test -f $threadExecDir/$responseThreadNumber") == 0) {
                execAndStdOut("cat $threadExecDir/$responseThreadNumber").dropLast(1)
            } else null
        }.also { system("rm -rf $threadExecDir") }
    } else {
        exit(0)
        return listOf()
    }
    // Obligatory but useless in the fork actually
}