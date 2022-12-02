string inputsPath = "C:\\Users\\guill\\Desktop\\AdventOfCode2022\\CSharp\\Guitou\\AdventOfCode2022\\Inputs\\"; //change to your own

string input = File.ReadAllText(inputsPath + "Input1.txt");

#region Part one
string[] elves = input.Split(Environment.NewLine + Environment.NewLine);
int result = elves.Select(elf =>
{
    string[] calories = elf.Split(Environment.NewLine);
    return calories.Select(x => int.Parse(x)).Sum();
}).Max();

Console.WriteLine(result);
#endregion

#region Part Two
result = elves.Select(elf =>
    { 
        string[] calories = elf.Split(Environment.NewLine); 
        return calories.Select(x => int.Parse(x)).Sum(); 
    })
    .OrderByDescending(x => x)
    .Take(3)
    .Sum();

Console.WriteLine(result);
#endregion
