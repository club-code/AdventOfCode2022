# Advent Of Code 2022 ([Pierre](https://github.com/PitiBouchon) - Rust)
Using [Rust](https://www.rust-lang.org/) version `1.67.0-nightly`

## Usage

To run the program for day 1 :
> cargo run --bin day1

## Code
I made a trait `Solver` to simplify the parsing and running phase

### *Example*

```rust
impl Solver for Day1 {
    type ParsedInput = Vec<usize>;
    type Output = usize;

    fn parse(input: impl Iterator<Item = String>) -> Self::ParsedInput {
        input.map(|s| s.parse().unwrap()).collect()
    }

    fn part1(&self, parsed_input: &Self::ParsedInput) -> Result<Self::Output> {
        Ok(parsed_input.capacity())
    }
}
```


*Contact me via Discord: `PtiBouchon#2801`*
