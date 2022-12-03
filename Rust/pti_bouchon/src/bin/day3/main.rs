mod util;

use crate::util::Rucksack;
use pti_bouchon::parse_lines;

fn main() {
    let lines = parse_lines("resources/day3.txt");
    let parsed_input = parse(lines);

    println!("Part1: {}", part1(&parsed_input));
    println!("Part2: {}", part2(&parsed_input));
}

fn parse(input: Vec<String>) -> Vec<Rucksack> {
    input.into_iter().map(|line| line.into()).collect()
}

fn part1(parsed_input: &[Rucksack]) -> usize {
    parsed_input
        .iter()
        .map(|rucksack| {
            rucksack.compartment1.intersection(&rucksack.compartment2).map(|e| *e as usize).sum::<usize>()
        })
        .sum()
}

fn part2(parsed_input: &[Rucksack]) -> usize {
    parsed_input
        .chunks(3)
        .map(|rucksacks| {
            Rucksack::intersection(rucksacks)
        })
        .sum()
}
