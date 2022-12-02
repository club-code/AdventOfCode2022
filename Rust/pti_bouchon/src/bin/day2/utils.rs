#[derive(Debug, Copy, Clone)]
pub enum RockPaperScissor {
    Rock = 1,
    Paper = 2,
    Scissors = 3
}

#[derive(Debug)]
pub enum MatchScore {
    Win = 6,
    Equality = 3,
    Lose = 0
}

impl RockPaperScissor {
    pub fn fight(&self, other: &Self) -> MatchScore {
        match self {
            Self::Rock => {
                match other {
                    RockPaperScissor::Rock => MatchScore::Equality,
                    RockPaperScissor::Paper => MatchScore::Lose,
                    RockPaperScissor::Scissors => MatchScore::Win,
                }
            },
            Self::Paper => {
                match other {
                    RockPaperScissor::Rock => MatchScore::Win,
                    RockPaperScissor::Paper => MatchScore::Equality,
                    RockPaperScissor::Scissors => MatchScore::Lose,
                }
            },
            Self::Scissors => {
                match other {
                    RockPaperScissor::Rock => MatchScore::Lose,
                    RockPaperScissor::Paper => MatchScore::Win,
                    RockPaperScissor::Scissors => MatchScore::Equality,
                }
            },
        }
    }
}

impl From<&str> for RockPaperScissor {
    fn from(value: &str) -> Self {
        match value.trim() {
            "A" | "X" => Self::Rock,
            "B" | "Y" => Self::Paper,
            "C" | "Z" => Self::Scissors,
            _ => panic!("Error: {}", value)
        }
    }
}

impl RockPaperScissor {
    pub fn winner(&self) -> Self {
        match self {
            RockPaperScissor::Rock => RockPaperScissor::Paper,
            RockPaperScissor::Paper => RockPaperScissor::Scissors,
            RockPaperScissor::Scissors => RockPaperScissor::Rock
        }
    }

    pub fn loser(&self) -> Self {
        match self {
            RockPaperScissor::Rock => RockPaperScissor::Scissors,
            RockPaperScissor::Paper => RockPaperScissor::Rock,
            RockPaperScissor::Scissors => RockPaperScissor::Paper
        }
    }
}
