string inputsPath = "C:\\Users\\guill\\Desktop\\AdventOfCode2022\\CSharp\\Guitou\\AdventOfCode2022\\Inputs\\"; //change to your own

string input = File.ReadAllText(inputsPath + "Input2.txt");

int Fight(int opponent, int player)
{
    if(opponent == player) { return 3; }
    if((opponent+1)%3 == (player)) { return 6; }
    return 0;
}

int Opponent(char x)
{
    switch (x)
    {
        case 'A': return 0;
        case 'B': return 1;
        case 'C': return 2;
    }

    return -1;
}

int Player(char x)
{
    switch (x)
    {
        case 'X': return 0;
        case 'Y': return 1;
        case 'Z': return 2;
    }
    return -1;
}

int Strategy(char x, int opponent)
{
    switch (x) 
    {
        case 'X': return (opponent+2)%3;
        case 'Y': return opponent;
        case 'Z': return (opponent+1)%3;
    }
    return -1;
}

#region Part one
string[] fights = input.Split(Environment.NewLine);

int result = fights.Select(line =>
{
    int player = Player(line[2]);
    return (Fight(Opponent(line[0]), player) + player + 1);
}).Sum();

Console.WriteLine(result);
#endregion

#region Part Two
result = fights.Select(line =>
    {
        int opponent = Opponent(line[0]);
        int player = Strategy(line[2], opponent);
        return (Fight(opponent, player) + player + 1);
    })
    .Sum();

Console.WriteLine(result);
#endregion
