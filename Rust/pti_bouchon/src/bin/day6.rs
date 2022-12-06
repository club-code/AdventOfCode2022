use pti_bouchon::parse_lines;

fn main() {
    let characters: Vec<char> = parse_lines("resources/day6.txt")[0].chars().collect();
    println!("Part1: {}", part(&characters, 4));
    println!("Part2: {}", part(&characters, 14));
}

fn part(characters: &[char], window: usize) -> usize {
    for (idx, character_slice) in characters.windows(window).enumerate() {
        if !character_slice
            .iter()
            .enumerate()
            .any(|(i, c)| character_slice[(i + 1)..].contains(c))
        {
            return idx + window;
        }
    }
    panic!("Impossible")
}
