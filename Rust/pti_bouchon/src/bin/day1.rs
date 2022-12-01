use pti_bouchon::{print_solutions, Solver};

fn main() {
    print_solutions(Day1, "resources/day1.txt")
}

struct Day1;

impl Solver for Day1 {
    type ParsedInput = Vec<Vec<usize>>;
    type Output = usize;

    fn parse(input: Vec<String>) -> Self::ParsedInput {
        input.split(|line| line.is_empty()).map(|elf_bag| elf_bag.iter().map(|calorie| calorie.parse().unwrap()).collect()).collect()
    }

    fn part1(parsed_input: &Self::ParsedInput) -> Self::Output {
        parsed_input.iter().map(|calories| calories.iter().sum()).max().unwrap()
    }

     fn part2(parsed_input: &Self::ParsedInput) -> Self::Output {
         let elf_calories: Vec<usize> = parsed_input.iter().map(|calories| calories.iter().sum()).collect();
         let mut max_calories: [usize; 3] = [elf_calories[0], elf_calories[1], elf_calories[2]];
         for calories in elf_calories {
            if calories > max_calories[0] {
                max_calories[2] = max_calories[1];
                max_calories[1] = max_calories[0];
                max_calories[0] = calories;
            }
         }
         max_calories.into_iter().sum()
     }
}
