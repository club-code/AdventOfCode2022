use pti_bouchon::parse_lines;

fn main() {
    let lines = parse_lines("resources/day10.txt");
    let parsed_input = parse(lines);

    println!("Part1: {}", part1(&parsed_input));
    part2(&parsed_input);
}

enum Operation {
    Noop,
    Addx(i32),
}

fn parse(input: Vec<String>) -> Vec<Operation> {
    input.into_iter()
        .map(|line| {
            match &line[0..4] {
                "addx" => Operation::Addx(line[5..].parse().unwrap()),
                "noop" => Operation::Noop,
                _ => panic!("ERROR")
            }
        })
        .collect()
}

fn part1(operations: &[Operation]) -> i32 {
    let mut register = 1;
    let mut cycle = 0;
    let mut result = 0;
    for op in operations {
        match *op {
            Operation::Noop => {
                cycle += 1;
                if (cycle + 20) % 40 == 0 {
                    result += cycle * register;
                }
            },
            Operation::Addx(n) => {
                cycle += 1;
                if (cycle + 20) % 40 == 0 {
                    result += cycle * register;
                }
                cycle += 1;
                if (cycle + 20) % 40 == 0 {
                    result += cycle * register;
                }
                register += n;
            }
        }
    }
    result
}

fn part2(operations: &[Operation]) {
    let mut register = 1;
    let mut pointer = 0;
    for op in operations {
        match *op {
            Operation::Noop => {
                if ((register-1)..=(register+1)).contains(&pointer) {
                    print!("#");
                }
                else {
                    print!(".")
                }
                pointer += 1;
                if pointer % 40 == 0 {
                    println!();
                    pointer = 0;
                }
            },
            Operation::Addx(n) => {
                if ((register-1)..=(register+1)).contains(&pointer) {
                    print!("#");
                }
                else {
                    print!(".")
                }
                pointer += 1;
                if pointer % 40 == 0 {
                    println!();
                    pointer = 0;
                }

                if ((register-1)..=(register+1)).contains(&pointer) {
                    print!("#");
                }
                else {
                    print!(".")
                }
                pointer += 1;
                if pointer % 40 == 0 {
                    println!();
                    pointer = 0;
                }

                register += n;
            }
        }
    }
}
