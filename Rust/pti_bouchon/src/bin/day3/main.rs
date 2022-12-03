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
            *(rucksack
                .compartment1
                .iter()
                .find(|elm| rucksack.compartment2.contains(elm))
                .unwrap()) as usize
        })
        .sum()
}

fn part2(parsed_input: &[Rucksack]) -> usize {
    parsed_input
        .chunks(3)
        .map(|rucksacks| {
            for elm in rucksacks[0].iter_union() {
                if rucksacks
                    .iter()
                    .skip(1)
                    .all(|rucksack| rucksack.contains(elm))
                {
                    return *elm as usize;
                }
            }
            panic!("No common element !")
        })
        .sum()
}
