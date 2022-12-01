use pti_bouchon::{print_solutions, Solver};

fn main() {
    print_solutions::<Day1>("resources/day1.txt");
}

struct Day1(Vec<Vec<usize>>);

impl Solver for Day1 {
    type Output = usize;

    fn parse(input: Vec<String>) -> Self {
        Self(input.split(|line| line.is_empty()).map(|elf_bag| elf_bag.iter().map(|calorie| calorie.parse().unwrap()).collect()).collect())
    }

    fn part1(&self) -> Self::Output {
        self.0.iter().map(|calories| calories.iter().sum()).max().unwrap()
    }

     fn part2(&self) -> Self::Output {
         let mut elf_calories: Vec<usize> = self.0.iter().map(|calories| calories.iter().sum()).collect();
         elf_calories.sort_by(|a, b| b.cmp(a)); // Sort by descending order
         elf_calories.into_iter().take(3).sum()

         // Otherwise
//         let mut max_calories: [usize; 3] = [elf_calories[0], elf_calories[1], elf_calories[2]];
//         for calories in elf_calories {
//            if calories > max_calories[0] {
//                max_calories[2] = max_calories[1];
//                max_calories[1] = max_calories[0];
//                max_calories[0] = calories;
//            }
//         }
//         max_calories.into_iter().sum()
     }
}
