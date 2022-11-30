pub fn parse_stdin() -> Vec<String> {
    std::io::stdin().lines().map(|l| l.unwrap()).collect()
}
