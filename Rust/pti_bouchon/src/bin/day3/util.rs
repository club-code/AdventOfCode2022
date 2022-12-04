use std::collections::HashSet;

fn priority(c: char) -> u8 {
    if c.is_ascii_lowercase() {
        c as u8 - b'a' + 1
    } else {
        c as u8 - b'A' + 27
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
    pub fn reunion(&self) -> HashSet<u8> {
        self.compartment1.union(&self.compartment2).copied().collect()
    }

    pub fn intersection(rucksacks: &[Rucksack]) -> usize {
        let mut intersection = rucksacks[0].reunion();
        for elms in rucksacks.iter().skip(1).map(|rucksack| rucksack.reunion()) {
            intersection = intersection.intersection(&elms).copied().collect();
        }
        intersection.into_iter().map(|e| e as usize).sum()
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
