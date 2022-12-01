use std::fmt;
use std::fs::File;
use std::io::{BufRead, BufReader};
use std::path::Path;
pub trait Solver {
    type ParsedInput;
    type Output: fmt::Debug;

    fn parse(input: Vec<String>) -> Self::ParsedInput;
    fn part1(_parsed_input: &Self::ParsedInput) -> Self::Output;
    fn part2(_parsed_input: &Self::ParsedInput) -> Self::Output;
}

pub fn print_solutions<S: Solver>(_: S, path: impl AsRef<Path>) {
    let input = BufReader::new(File::open(path).unwrap()).lines().map(|l| l.unwrap()).collect();
    let parsed_input = S::parse(input);
    println!("Part1: {:?}", S::part1(&parsed_input));
    println!("Part2: {:?}", S::part2(&parsed_input));
}
