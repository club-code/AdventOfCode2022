use std::cmp::Ordering;
use std::str::FromStr;

#[derive(Debug, Copy, Clone, Eq, PartialEq)]
pub enum RockPaperScissor {
    Rock = 1,
    Paper = 2,
    Scissors = 3,
}

#[derive(Debug)]
pub enum MatchScore {
    Win = 6,
    Equality = 3,
    Lose = 0,
}

impl Ord for RockPaperScissor {
    fn cmp(&self, other: &Self) -> Ordering {
        match self {
            Self::Rock => match other {
                RockPaperScissor::Rock => Ordering::Equal,
                RockPaperScissor::Paper => Ordering::Less,
                RockPaperScissor::Scissors => Ordering::Greater,
            },
            Self::Paper => match other {
                RockPaperScissor::Rock => Ordering::Greater,
                RockPaperScissor::Paper => Ordering::Equal,
                RockPaperScissor::Scissors => Ordering::Less,
            },
            Self::Scissors => match other {
                RockPaperScissor::Rock => Ordering::Less,
                RockPaperScissor::Paper => Ordering::Greater,
                RockPaperScissor::Scissors => Ordering::Equal,
            },
        }
    }
}

impl PartialOrd for RockPaperScissor {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl RockPaperScissor {
    pub fn fight(&self, other: &Self) -> MatchScore {
        match self.cmp(other) {
            Ordering::Less => MatchScore::Lose,
            Ordering::Equal => MatchScore::Equality,
            Ordering::Greater => MatchScore::Win,
        }
    }
}

impl FromStr for RockPaperScissor {
    type Err = String;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        match s.trim() {
            "A" | "X" => Ok(Self::Rock),
            "B" | "Y" => Ok(Self::Paper),
            "C" | "Z" => Ok(Self::Scissors),
            _ => Err(format!("{} can't be converted", s)),
        }
    }
}

impl RockPaperScissor {
    pub fn winner(&self) -> Self {
        match self {
            RockPaperScissor::Rock => RockPaperScissor::Paper,
            RockPaperScissor::Paper => RockPaperScissor::Scissors,
            RockPaperScissor::Scissors => RockPaperScissor::Rock,
        }
    }

    pub fn loser(&self) -> Self {
        match self {
            RockPaperScissor::Rock => RockPaperScissor::Scissors,
            RockPaperScissor::Paper => RockPaperScissor::Rock,
            RockPaperScissor::Scissors => RockPaperScissor::Paper,
        }
    }
}
