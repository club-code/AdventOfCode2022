mod utils;

use pti_bouchon::{print_solutions, Solver};
use utils::RockPaperScissor;

fn main() {
    print_solutions::<Day2>("resources/day2.txt");
}

struct Day2(Vec<(RockPaperScissor, RockPaperScissor)>);

impl Solver for Day2 {
    type Output = usize;

    fn parse(input: Vec<String>) -> Self {
        Self(
            input.into_iter()
                .map(|line| {
                    let choices: Vec<&str> = line.split_whitespace().collect();
                    let choice1: RockPaperScissor = choices[0].into();
                    let choice2: RockPaperScissor = choices[1].into();
                    (choice1, choice2)
                })
                .collect()
        )
    }

    fn part1(&self) -> Self::Output {
        self.0.iter().map(|(choice1, choice2)| (*choice2 as usize) + (choice2.fight(choice1) as usize)).sum()
    }

    fn part2(&self) -> Self::Output {
        self.0.iter()
            .map(|(other_choice, todo)| {
                match todo {
                    // Need to Lose
                    RockPaperScissor::Rock => {
                        let my_choice = other_choice.loser();
                        (my_choice as usize) + (my_choice.fight(other_choice) as usize)
                    }
                    // Need to Draw
                        RockPaperScissor::Paper => {
                            (*other_choice as usize) + (other_choice.fight(other_choice) as usize)
                        }
                    // Need to Win
                    RockPaperScissor::Scissors => {
                        let my_choice = other_choice.winner();
                        (my_choice as usize) + (my_choice.fight(other_choice) as usize)
                    }
                }
            })
            .sum()
    }
}
