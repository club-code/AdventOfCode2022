use std::fs::read_to_string;

fn main() {
    let text = read_to_string("resources/day11.txt").unwrap();
    let monkeys = parse(text);

    println!("Part1: {}", part1(&monkeys));
    println!("Part2: {}", part2(&monkeys));
}

struct Monkey {
    items: Vec<i64>,
    operation: Box<dyn Fn(i64) -> i64>,
    div: i64,
    monkey_true: usize,
    monkey_false: usize,
}

fn parse(input: String) -> Vec<Monkey> {
    input
        .split("\r\n\r\n")
        .map(|monkey_str| {
            let infos: Vec<&str> = monkey_str.lines().collect();
            let items = infos[1][18..]
                .split(',')
                .map(|n| n.trim().parse().unwrap())
                .collect();
            let operation = operation(infos[2][19..].to_string());
            let div = infos[3][21..].parse().unwrap();
            let monkey_true = infos[4][29..].parse().unwrap();
            let monkey_false = infos[5][30..].parse().unwrap();
            Monkey {
                items,
                operation: Box::new(operation),
                div,
                monkey_true,
                monkey_false,
            }
        })
        .collect()
}

fn part1(monkeys: &[Monkey]) -> usize {
    let mut monkey_inspections = vec![0; monkeys.len()];
    let mut monkeys_inventory: Vec<Vec<i64>> = monkeys.iter().map(|monkey| monkey.items.clone()).collect();
    for _ in 0..20 {
        for (index, monkey) in monkeys.iter().enumerate() {
            assert_ne!(index, monkey.monkey_true as usize);
            assert_ne!(index, monkey.monkey_false as usize);
            let (l, r) = monkeys_inventory.split_at_mut(index);
            let (inv, r) = r.split_first_mut().unwrap();

            while let Some(item) = inv.pop() {
                monkey_inspections[index] += 1;
                let new_worry_level: i64 = (monkey.operation)(item) / 3;
                if new_worry_level % monkey.div == 0 {
                    if monkey.monkey_true < index {
                        l[monkey.monkey_true].push(new_worry_level);
                    } else {
                        r[monkey.monkey_true - index - 1].push(new_worry_level);
                    }
                } else {
                    if monkey.monkey_false < index {
                        l[monkey.monkey_false].push(new_worry_level);
                    } else {
                        r[monkey.monkey_false - index - 1].push(new_worry_level);
                    }
                }
            }
        }
    }
    monkey_inspections.sort_by(|a, b| b.cmp(a)); // Sort by descending order
    monkey_inspections[0] * monkey_inspections[1]
}

fn part2(monkeys: &[Monkey]) -> usize {
    let mut monkey_inspections = vec![0; monkeys.len()];
    let mut monkeys_inventory: Vec<Vec<i64>> = monkeys.iter().map(|monkey| monkey.items.clone()).collect();
    let multiplication_divisor = monkeys.iter().map(|m| m.div).reduce( |a, b| a * b).unwrap();
    for _ in 0..10_000 {
        for (index, monkey) in monkeys.iter().enumerate() {
            assert_ne!(index, monkey.monkey_true as usize);
            assert_ne!(index, monkey.monkey_false as usize);
            let (l, r) = monkeys_inventory.split_at_mut(index);
            let (inv, r) = r.split_first_mut().unwrap();

            while let Some(item) = inv.pop() {
                monkey_inspections[index] += 1;
                let new_worry_level: i64 = (monkey.operation)(item) % multiplication_divisor;
                if new_worry_level % monkey.div == 0 {
                    if monkey.monkey_true < index {
                        l[monkey.monkey_true].push(new_worry_level);
                    } else {
                        r[monkey.monkey_true - index - 1].push(new_worry_level);
                    }
                } else {
                    if monkey.monkey_false < index {
                        l[monkey.monkey_false].push(new_worry_level);
                    } else {
                        r[monkey.monkey_false - index - 1].push(new_worry_level);
                    }
                }
            }
        }
    }
    monkey_inspections.sort_by(|a, b| b.cmp(a)); // Sort by descending order
    monkey_inspections[0] * monkey_inspections[1]
}

fn operation(operation: String) -> Box<dyn Fn(i64) -> i64> {
    let elms: Vec<String> = operation
        .split_whitespace()
        .map(|e| e.to_string())
        .collect();
    let f = move |old| {
        let a = match elms[0].as_str() {
            "old" => old,
            _ => elms[0].parse::<i64>().unwrap(),
        };
        let b = match elms[2].as_str() {
            "old" => old,
            _ => elms[2].parse::<i64>().unwrap(),
        };
        match elms[1].as_str() {
            "*" => a * b,
            "+" => a + b,
            _ => panic!("Error"),
        }
    };
    Box::new(f)
}
