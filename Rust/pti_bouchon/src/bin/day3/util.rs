use std::collections::hash_map::RandomState;
use std::collections::hash_set::Union;
use std::collections::HashSet;

fn priority(c: char) -> u8 {
    if c.is_ascii_lowercase() {
        c as u8 - b'a' + 1
    } else {
        c as u8 - b'A' + 1
    }
}

fn convert_str_compartment(s: &str) -> HashSet<u8> {
    s.chars().map(priority).collect()
}

pub struct Rucksack {
    pub compartment1: HashSet<u8>,
    pub compartment2: HashSet<u8>,
}

impl Rucksack {
    pub fn contains(&self, value: &u8) -> bool {
        self.compartment1.contains(value) || self.compartment2.contains(value)
    }
}

impl Rucksack {
    pub fn iter_union(&self) -> Union<u8, RandomState> {
        self.compartment1.union(&self.compartment2)
    }
}

impl From<String> for Rucksack {
    fn from(value: String) -> Self {
        let (part1, part2) = value.split_at(value.len() / 2);
        Self {
            compartment1: convert_str_compartment(part1),
            compartment2: convert_str_compartment(part2),
        }
    }
}

#[cfg(test)]
mod test {
    use crate::util::priority;

    #[test]
    fn test_priority() {
        assert_eq!(priority('a'), 1);
        assert_eq!(priority('z'), 26);
        assert_eq!(priority('A'), 27);
        assert_eq!(priority('Z'), 52);
    }
}
