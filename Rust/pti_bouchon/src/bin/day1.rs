use anyhow::Result;
use pti_bouchon::parse_stdin;

fn main() -> Result<()> {
   let input = parse_stdin();
    println!("Part1: {:?}", part1(&input)?);
    println!("Part2: {:?}", part2(&input)?);

    Ok(())
}

fn part1(input: &Vec<String>) -> Result<String> {

    Ok(format!("{input:?}"))
}

fn part2(input: &Vec<String>) -> Result<String> {
    Ok(format!("{input:?}"))
}
