fun List<String>.groupBySeparatorBlank() = this.fold(mutableListOf(mutableListOf<String>())) { acc, it ->
    if (it.isBlank()) {
        acc.add(mutableListOf<String>())
        return@fold acc
    } else {
        acc.last().add(it)
        return@fold acc
    }
}