use std::fmt;
use std::fs::File;
use std::io::{BufRead, BufReader};
use std::path::Path;
use eyre::{Result, Report};

pub fn parse_stdin() -> Vec<String> {
    std::io::stdin().lines().map(|l| l.unwrap()).collect()
}

#[derive(Debug)]
struct UnImplemented;

impl fmt::Display for UnImplemented {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Not Implemented !")
    }
}

impl std::error::Error for UnImplemented {}

pub trait Solver {
    type ParsedInput;
    type Output: fmt::Debug;

    fn parse(input: impl Iterator<Item = String>) -> Self::ParsedInput;
    fn part1(&self, parsed_input: &Self::ParsedInput) -> Result<Self::Output>;
    fn part2(&self, _parsed_input: &Self::ParsedInput) -> Result<Self::Output> { Err(Report::new(UnImplemented)) }
}

pub fn print_solutions<S: Solver>(solver: S, path: impl AsRef<Path>) {
    let input = BufReader::new(File::open(path).unwrap()).lines().map(|l| l.unwrap());
    let parsed_input = S::parse(input);
    println!("Part1: {:?}", solver.part1(&parsed_input).unwrap());
    let solution_part2 = solver.part2(&parsed_input);
    match solution_part2 {
        Err(err) if err.is::<UnImplemented>()  => (),
        _ => println!("Part2: {:?}", solution_part2.unwrap()),
    }
}
