fun List<String>.groupBySeparatorBlank() = this.fold(mutableListOf(mutableListOf<String>())) { acc, it ->
    if (it.isBlank()) {
        acc.add(mutableListOf<String>())
        return@fold acc
    } else {
        acc.last().add(it)
        return@fold acc
    }
}

fun<E> List<List<E>>.rotate(): List<List<E>> =
    (0 until this[0].size).map {i->
        (this.indices).map { j->
            this[j][i]
        }
    }