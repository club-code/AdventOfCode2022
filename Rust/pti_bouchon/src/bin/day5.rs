use pti_bouchon::parse_lines;

fn main() {
    let lines_part1 = parse_lines("resources/day5-part1.txt");
    let stacks = parse_stacks(lines_part1);

    let lines_part2 = parse_lines("resources/day5-part2.txt");

    println!("Part1: {}", part1(stacks.clone(), &lines_part2));
    println!("Part2: {}", part2(stacks, &lines_part2));
}

fn parse_stacks(mut input: Vec<String>) -> Vec<Vec<char>> {
    let n_stacks: usize = input
        .last()
        .unwrap()
        .split_whitespace()
        .map(|n| n.parse::<usize>().unwrap())
        .max()
        .unwrap();
    input.reverse();
    let mut stacks: Vec<Vec<char>> = vec![Vec::with_capacity(n_stacks); n_stacks];
    for line in input.into_iter().skip(1) {
        for (index, chunk) in line.chars().collect::<Vec<char>>().chunks(4).enumerate() {
            if !chunk[1].is_whitespace() {
                stacks[index].push(chunk[1]);
            }
        }
    }
    stacks
}

fn part1(mut stacks: Vec<Vec<char>>, commands: &Vec<String>) -> String {
    for line in commands {
        let numbers: Vec<usize> = line
            .split_whitespace()
            .filter_map(|s| s.parse::<usize>().ok())
            .collect();
        let (n, stack1, stack2) = (numbers[0], numbers[1] - 1, numbers[2] - 1);
        for _ in 0..n {
            let elm = stacks[stack1].pop().unwrap();
            stacks[stack2].push(elm);
        }
    }
    stacks
        .into_iter()
        .map(|stack| *stack.last().unwrap())
        .collect()
}

fn part2(mut stacks: Vec<Vec<char>>, commands: &Vec<String>) -> String {
    for line in commands {
        let numbers: Vec<usize> = line
            .split_whitespace()
            .filter_map(|s| s.parse::<usize>().ok())
            .collect();
        let (n, stack1, stack2) = (numbers[0], numbers[1] - 1, numbers[2] - 1);
        let length_stack1 = stacks[stack1].len();
        let mut thing = stacks[stack1].split_off(length_stack1 - n);
        stacks[stack2].append(&mut thing);
    }
    stacks
        .into_iter()
        .map(|stack| *stack.last().unwrap())
        .collect()
}
