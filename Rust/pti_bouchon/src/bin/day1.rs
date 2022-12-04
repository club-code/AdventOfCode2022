use pti_bouchon::parse_lines;

fn main() {
    let lines = parse_lines("resources/day1.txt");
    let parsed_input = parse(lines);
    println!("Part1: {}", part1(&parsed_input));
    println!("Part1: {}", part2(&parsed_input));
}

fn parse(input: Vec<String>) -> Vec<Vec<usize>> {
    input
        .split(|line| line.is_empty())
        .map(|elf_bag| {
            elf_bag
                .iter()
                .map(|calorie| calorie.parse().unwrap())
                .collect()
        })
        .collect()
}

fn part1(parsed_input: &[Vec<usize>]) -> usize {
    parsed_input
        .iter()
        .map(|calories| calories.iter().sum())
        .max()
        .unwrap()
}

fn part2(parsed_input: &[Vec<usize>]) -> usize {
    let mut elf_calories: Vec<usize> = parsed_input
        .iter()
        .map(|calories| calories.iter().sum())
        .collect();

    elf_calories.sort_by(|a, b| b.cmp(a)); // Sort by descending order
    elf_calories.into_iter().take(3).sum()
}
