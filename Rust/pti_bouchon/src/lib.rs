use std::fs::File;
use std::io::{BufRead, BufReader};
use std::path::Path;

pub fn parse_lines(path: impl AsRef<Path>) -> Vec<String> {
    BufReader::new(File::open(path).unwrap())
        .lines()
        .map(|l| l.unwrap())
        .collect()
}
