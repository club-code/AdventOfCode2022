mod utils;

use pti_bouchon::parse_lines;
use std::str::FromStr;
use utils::RockPaperScissor;

fn main() {
    let lines = parse_lines("resources/day2.txt");
    let parsed_input = parse(lines);
    println!("Part1: {}", part1(&parsed_input));
    println!("Part1: {}", part2(&parsed_input));
}

fn parse(input: Vec<String>) -> Vec<(RockPaperScissor, RockPaperScissor)> {
    input
        .into_iter()
        .map(|line| {
            let choices: Vec<&str> = line.split_whitespace().collect();
            let choice1 = RockPaperScissor::from_str(choices[0]).unwrap();
            let choice2 = RockPaperScissor::from_str(choices[1]).unwrap();
            (choice1, choice2)
        })
        .collect()
}

fn part1(parsed_input: &[(RockPaperScissor, RockPaperScissor)]) -> usize {
    parsed_input
        .iter()
        .map(|(choice1, choice2)| (*choice2 as usize) + (choice2.fight(choice1) as usize))
        .sum()
}

fn part2(parsed_input: &[(RockPaperScissor, RockPaperScissor)]) -> usize {
    parsed_input
        .iter()
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
