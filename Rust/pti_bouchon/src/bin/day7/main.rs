mod util;

use std::collections::HashMap;
use std::path::PathBuf;
use crate::util::{AoCDirectory, AoCFile};
use pti_bouchon::parse_lines;

fn main() {
    let lines = parse_lines("resources/day7.txt");
    let directories = parse(lines);
    let root_directory_path = PathBuf::from("/");
    let mut directories_size = HashMap::new();
    let root_directory_size = set_directory_size(&root_directory_path, &directories, &mut directories_size);

    println!("Part1: {}", part1(&directories_size));
    println!("Part2: {}", part2(root_directory_size, &directories_size));
}

fn parse(input: Vec<String>) -> HashMap<PathBuf, AoCDirectory> {
    let mut line_index = 1;
    let mut path = PathBuf::from("/");
    let mut directories = HashMap::new();
    while line_index < input.len() {
        match input[line_index].as_str() {
            "$ ls" => {
                line_index += 1;
                let mut ls_files = vec![];
                let mut ls_directories = vec![];
                while line_index < input.len() {
                    match input[line_index].as_str() {
                        line if &line[0..1] == "$" => break,
                        directory if &directory[..3] == "dir" => {
                            let directory_name = directory.split_whitespace().last().unwrap();
                            ls_directories.push(directory_name.to_string());
                        }
                        file => {
                            let file_info: Vec<&str> = file.split_whitespace().collect();
                            ls_files.push(AoCFile {
                                size: file_info[0].parse().unwrap(),
                                name: file_info[1].to_string()
                            })
                        }
                    }
                    line_index += 1;
                }
                let name = path.components().last().unwrap().as_os_str().to_str().unwrap().to_string();
                directories.insert(path.clone(), AoCDirectory {
                    name,
                    files: ls_files,
                    childrens_directory: ls_directories,
                });
            }
            cmd if &cmd[..4] == "$ cd" => {
                if cmd.len() > 6 && &cmd[5..7] == ".." {
                    path = path.parent().unwrap().to_path_buf();
                }
                else {
                    path.push(&cmd[5..]);
                }
                line_index += 1;
            },
            err => panic!("Error: {}", err),
        }
    }

    directories
}

fn part1(directories_size: &HashMap<PathBuf, usize>) -> usize {
    const MAX_SIZE: usize = 100_000;
        directories_size.values().filter_map(|&dir_size| {
        if dir_size <= MAX_SIZE {
            Some(dir_size)
        }
        else {
            None
        }
    }).sum()
}

fn part2(root_dir_size: usize, directories_size: &HashMap<PathBuf, usize>) -> usize {
    const DISK_SPACE: usize = 70_000_000;
    const UPDATE_SPACE: usize = 30_000_000;
    let unused_space = DISK_SPACE - root_dir_size;
    directories_size.values()
        .filter_map(|&dir_size| {
            if dir_size >= UPDATE_SPACE - unused_space {
                Some(dir_size)
            }
            else {
                None
            }
        })
        .min()
        .unwrap()
}

fn set_directory_size(path: &PathBuf, directories: &HashMap<PathBuf, AoCDirectory>, directories_size: &mut HashMap<PathBuf, usize>) -> usize {
    let dir = directories.get(path).unwrap();
    let mut size: usize = dir.files.iter().map(|f| f.size).sum();
    for directory_name in dir.childrens_directory.iter() {
        let mut path_buf = path.clone();
        path_buf.push(directory_name);
        size += set_directory_size(&path_buf, directories, directories_size);
    }
    directories_size.insert(path.clone(), size);
    size
}
