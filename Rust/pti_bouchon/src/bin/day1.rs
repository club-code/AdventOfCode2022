use pti_bouchon::{print_solutions, Solver};
use eyre::Result;

fn main() {
    print_solutions(Day1, "resources/test.txt")
}

struct Day1;

impl Solver for Day1 {
    type ParsedInput = Vec<usize>;
    type Output = usize;

    fn parse(input: impl Iterator<Item = String>) -> Self::ParsedInput {
        input.map(|s| s.parse().unwrap()).collect()
    }

    fn part1(&self, parsed_input: &Self::ParsedInput) -> Result<Self::Output> {
        Ok(parsed_input.capacity())
    }

     fn part2(&self, parsed_input: &Self::ParsedInput) -> Result<Self::Output> {
         self.part1(parsed_input)
     }
}
