#[derive(Debug, Copy, Clone)]
pub enum RockPaperScissor {
    Rock = 1,
    Paper = 2,
    Scissor = 3
}

#[derive(Debug)]
pub enum MatchScore {
    Win = 6,
    Equality = 3,
    Loose = 0
}

impl RockPaperScissor {
    pub fn fight(&self, other: &Self) -> MatchScore {
        match self {
            Self::Rock => {
                match other {
                    RockPaperScissor::Rock => MatchScore::Equality,
                    RockPaperScissor::Paper => MatchScore::Loose,
                    RockPaperScissor::Scissor => MatchScore::Win,
                }
            },
            Self::Paper => {
                match other {
                    RockPaperScissor::Rock => MatchScore::Win,
                    RockPaperScissor::Paper => MatchScore::Equality,
                    RockPaperScissor::Scissor => MatchScore::Loose,
                }
            },
            Self::Scissor => {
                match other {
                    RockPaperScissor::Rock => MatchScore::Loose,
                    RockPaperScissor::Paper => MatchScore::Win,
                    RockPaperScissor::Scissor => MatchScore::Equality,
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
            "C" | "Z" => Self::Scissor,
            _ => panic!("Error: {}", value)
        }
    }
}

impl RockPaperScissor {
    pub fn winner(&self) -> Self {
        match self {
            RockPaperScissor::Rock => RockPaperScissor::Paper,
            RockPaperScissor::Paper => RockPaperScissor::Scissor,
            RockPaperScissor::Scissor => RockPaperScissor::Rock
        }
    }

    pub fn loser(&self) -> Self {
        match self {
            RockPaperScissor::Rock => RockPaperScissor::Scissor,
            RockPaperScissor::Paper => RockPaperScissor::Rock,
            RockPaperScissor::Scissor => RockPaperScissor::Paper
        }
    }
}
