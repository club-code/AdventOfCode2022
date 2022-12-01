use std::fmt;
use std::fs::File;
use std::io::{BufRead, BufReader};
use std::path::Path;
pub trait Solver {
//    type ParsedInput;
    type Output: fmt::Debug;

    fn parse(input: Vec<String>) -> Self;
    fn part1(&self) -> Self::Output;
    fn part2(&self) -> Self::Output;
}

pub fn print_solutions<S: Solver>(path: impl AsRef<Path>) {
    let input = BufReader::new(File::open(path).unwrap()).lines().map(|l| l.unwrap()).collect();
    let day_solver = S::parse(input);
    println!("Part1: {:?}", day_solver.part1());
    println!("Part2: {:?}", day_solver.part2());
}
