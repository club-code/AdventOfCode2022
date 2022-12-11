use std::collections::HashSet;
use pti_bouchon::parse_lines;

fn main() {
    let lines = parse_lines("resources/day9.txt");
    let parsed_input = parse(lines);

    println!("Part1: {}", part1(&parsed_input));
    println!("Part2: {}", part2(&parsed_input));
}

enum Direction {
    Up(u32),
    Down(u32),
    Left(u32),
    Right(u32),
}

fn parse(input: Vec<String>) -> Vec<Direction> {
    input.into_iter()
        .map(|line| {
            let split: Vec<&str> = line.split_whitespace().collect();
            let n = split[1].parse().unwrap();
            match split[0] {
                "U" => Direction::Up(n),
                "D" => Direction::Down(n),
                "L" => Direction::Left(n),
                "R" => Direction::Right(n),
                _ => panic!("ERROR")
            }
        })
        .collect()
}

fn part1(directions: &[Direction]) -> usize {
    let mut tail_positions = HashSet::new();
    let mut head_pos = (0, 0); // (x,y)
    let mut tail_pos = (0, 0); // (x,y)
    tail_positions.insert(tail_pos);
    for dir in directions {
        match *dir {
            Direction::Up(n) => {
                for _ in 0..n {
                    head_pos.1 += 1;
                    tail_pos = add(&tail_pos, &follow(&head_pos, &tail_pos));
                    tail_positions.insert(tail_pos);
                }
            }
            Direction::Down(n) => {
                for _ in 0..n {
                    head_pos.1 -= 1;
                    tail_pos = add(&tail_pos, &follow(&head_pos, &tail_pos));
                    tail_positions.insert(tail_pos);
                }
            }
            Direction::Left(n) => {
                for _ in 0..n {
                    head_pos.0 -= 1;
                    tail_pos = add(&tail_pos, &follow(&head_pos, &tail_pos));
                    tail_positions.insert(tail_pos);
                }
            }
            Direction::Right(n) => {
                for _ in 0..n {
                    head_pos.0 += 1;
                    tail_pos = add(&tail_pos, &follow(&head_pos, &tail_pos));
                    tail_positions.insert(tail_pos);
                }
            }
        }
    }
    tail_positions.len()
}

fn part2(directions: &[Direction]) -> usize {
    let mut tail_positions = HashSet::new();
    let mut head_pos = (0, 0); // (x,y)
    let mut tail_pos = [(0, 0); 9]; // (x,y)
    tail_positions.insert(tail_pos[8]);
    for dir in directions {
        match *dir {
            Direction::Up(n) => {
                for _ in 0..n {
                    head_pos.1 += 1;
                    tail_pos[0] = add(&tail_pos[0], &follow(&head_pos, &tail_pos[0]));
                    for i in 1..9 {
                        tail_pos[i] = add(&tail_pos[i], &follow(&tail_pos[i-1], &tail_pos[i]));
                    }
                    tail_positions.insert(tail_pos[8]);
                }
            }
            Direction::Down(n) => {
                for _ in 0..n {
                    head_pos.1 -= 1;
                    tail_pos[0] = add(&tail_pos[0], &follow(&head_pos, &tail_pos[0]));
                    for i in 1..9 {
                        tail_pos[i] = add(&tail_pos[i], &follow(&tail_pos[i-1], &tail_pos[i]));
                    }
                    tail_positions.insert(tail_pos[8]);
                }
            }
            Direction::Left(n) => {
                for _ in 0..n {
                    head_pos.0 -= 1;
                    tail_pos[0] = add(&tail_pos[0], &follow(&head_pos, &tail_pos[0]));
                    for i in 1..9 {
                        tail_pos[i] = add(&tail_pos[i], &follow(&tail_pos[i-1], &tail_pos[i]));
                    }
                    tail_positions.insert(tail_pos[8]);
                }
            }
            Direction::Right(n) => {
                for _ in 0..n {
                    head_pos.0 += 1;
                    tail_pos[0] = add(&tail_pos[0], &follow(&head_pos, &tail_pos[0]));
                    for i in 1..9 {
                        tail_pos[i] = add(&tail_pos[i], &follow(&tail_pos[i-1], &tail_pos[i]));
                    }
                    tail_positions.insert(tail_pos[8]);
                }
            }
        }
    }
    tail_positions.len()
}

fn follow(head_pos: &(i32, i32), tail_pos: &(i32, i32)) -> (i32, i32) {
    let mut res = (0, 0);
    let mut min_dist = i32::MAX;
    for x in -1..=1 {
        for y in -1..=1 {
            let neighbour_pos = add(tail_pos, &(x, y));
            if *head_pos == neighbour_pos {
                return (0, 0)
            }
            let dist = square_distance(&neighbour_pos, head_pos);
            if dist <= 2 && dist < min_dist {
                min_dist = dist;
                res = (x, y);
            }
        }
    }
    res
}

fn square_distance(pos1: &(i32, i32), pos2: &(i32, i32)) -> i32 {
    (pos1.0 - pos2.0).pow(2) + (pos1.1 - pos2.1).pow(2)
}

fn add(pos1: &(i32, i32), pos2: &(i32, i32)) -> (i32, i32) {
    (pos1.0 + pos2.0, pos1.1 + pos2.1)
}
