use pti_bouchon::parse_lines;
use std::ops::RangeInclusive;

fn main() {
    let lines = parse_lines("resources/day4.txt");
    let parsed_input = parse(lines);

    println!("Part1: {}", part1(&parsed_input));
    println!("Part2: {}", part2(&parsed_input));
}

fn parse_range(s: &str) -> RangeInclusive<usize> {
    let values: Vec<usize> = s.split('-').map(|n| n.parse().unwrap()).collect();
    values[0]..=values[1]
}

fn parse(input: Vec<String>) -> Vec<(RangeInclusive<usize>, RangeInclusive<usize>)> {
    input
        .into_iter()
        .map(|line| {
            let ranges: Vec<&str> = line.split(',').collect();
            (parse_range(ranges[0]), parse_range(ranges[1]))
        })
        .collect()
}

fn range_inclusive(range1: &RangeInclusive<usize>, range2: &RangeInclusive<usize>) -> bool {
    range1.start() >= range2.start() && range1.end() <= range2.end()
}

fn range_overlap(range1: &RangeInclusive<usize>, range2: &RangeInclusive<usize>) -> bool {
    range2.contains(range1.start()) || range2.contains(range1.end())
}

fn part1(parsed_input: &[(RangeInclusive<usize>, RangeInclusive<usize>)]) -> usize {
    parsed_input
        .iter()
        .filter(|(range1, range2)| {
            range_inclusive(range1, range2) || range_inclusive(range2, range1)
        })
        .count()
}

fn part2(parsed_input: &[(RangeInclusive<usize>, RangeInclusive<usize>)]) -> usize {
    parsed_input
        .iter()
        .filter(|(range1, range2)| range_overlap(range1, range2) || range_overlap(range2, range1))
        .count()
}
