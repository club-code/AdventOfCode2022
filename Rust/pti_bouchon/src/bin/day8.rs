extern crate core;

use pti_bouchon::parse_lines;

fn main() {
    let lines = parse_lines("resources/day8.txt");
    let parsed_input = parse(lines);

    println!("Part1: {}", part1(&parsed_input));
    println!("Part2: {}", part2(&parsed_input));
}

fn parse(input: Vec<String>) -> Vec<Vec<u8>> {
    input
        .into_iter()
        .map(|line| {
            line.chars()
                .map(|c| c.to_digit(10).unwrap() as u8)
                .collect()
        })
        .collect()
}

fn part1(trees_height: &[Vec<u8>]) -> usize {
    let n = trees_height.len();
    let mut visible_trees = vec![vec![false; n]; n];
    for i in 0..n {
        for (index, _) in count_visible_tree(trees_height[i].iter())
            .into_iter()
            .enumerate()
            .filter(|(_, visible)| *visible)
        {
            visible_trees[i][index] = true;
        }
        for (index, _) in count_visible_tree(trees_height[i].iter().rev())
            .into_iter()
            .enumerate()
            .filter(|(_, visible)| *visible)
        {
            visible_trees[i][n - index - 1] = true;
        }
        for (index, _) in count_visible_tree(trees_height.iter().map(|l| &l[i]))
            .into_iter()
            .enumerate()
            .filter(|(_, visible)| *visible)
        {
            visible_trees[index][i] = true;
        }
        for (index, _) in count_visible_tree(trees_height.iter().map(|l| &l[i]).rev())
            .into_iter()
            .enumerate()
            .filter(|(_, visible)| *visible)
        {
            visible_trees[n - index - 1][i] = true;
        }
    }

    visible_trees
        .into_iter()
        .map(|l| l.into_iter().filter(|&e| e).count())
        .sum()
}

fn part2(trees_height: &[Vec<u8>]) -> usize {
    let mut max_scenic_score = 0;
    let n = trees_height.len();
    for i in 0..n {
        for j in 0..n {
            let (left, right, down, up) = (
                count_visible_tree_from(trees_height[i][(j + 1)..].iter(), trees_height[i][j])
                    .into_iter()
                    .filter(|e| *e)
                    .count(),
                count_visible_tree_from(trees_height[i][..j].iter().rev(), trees_height[i][j])
                    .into_iter()
                    .filter(|e| *e)
                    .count(),
                count_visible_tree_from(trees_height[(i + 1)..].iter().map(|l| &l[j]), trees_height[i][j])
                    .into_iter()
                    .filter(|e| *e)
                    .count(),
                count_visible_tree_from(trees_height[..i].iter().map(|l| &l[j]).rev(), trees_height[i][j])
                    .into_iter()
                    .filter(|e| *e)
                    .count(),
            );
            let scenic_score = right * left * up * down;
            if scenic_score > max_scenic_score {
                max_scenic_score = scenic_score
            }
        }
    }
    max_scenic_score
}

fn count_visible_tree<'a>(mut tree_line: impl Iterator<Item = &'a u8>) -> Vec<bool> {
    let max_tree_height_opt = tree_line.next().cloned();
    match max_tree_height_opt {
        Some(mut max_tree_height) => {
            let mut visible_trees = vec![true];
            for &tree_height in tree_line {
                if tree_height > max_tree_height {
                    visible_trees.push(true);
                    max_tree_height = tree_height;
                } else {
                    visible_trees.push(false);
                }
            }
            visible_trees
        },
        None => vec![]
    }
}

fn count_visible_tree_from<'a>(mut tree_line: impl Iterator<Item = &'a u8>, pov_tree_height: u8) -> Vec<bool> {
    let max_tree_height_opt = tree_line.next().cloned();
    match max_tree_height_opt {
        Some(mut max_tree_height) => {
            let mut visible_trees = vec![true];
            for &tree_height in tree_line {
                if tree_height > max_tree_height {
                    visible_trees.push(true);
                    if tree_height >= pov_tree_height {
                        break;
                    }
                    max_tree_height = tree_height;
                } else if tree_height < pov_tree_height && max_tree_height < pov_tree_height {
                    visible_trees.push(true);
                } else {
                    visible_trees.push(false);
                }
            }
            visible_trees
        },
        None => vec![]
    }
}
