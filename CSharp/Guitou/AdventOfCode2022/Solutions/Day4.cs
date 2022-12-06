string inputsPath = "C:\\Users\\guill\\Desktop\\AdventOfCode2022\\CSharp\\Guitou\\AdventOfCode2022\\Inputs\\"; //change to your own

string input = File.ReadAllText(inputsPath + "Input4.txt");

#region Part one
string[] rucksacks = input.Split(Environment.NewLine);

int result = rucksacks.Select(line =>
{
    string[] pair = line.Split(',');
    IEnumerable<string[]> numberPairs = pair.Select(s => s.Split('-'));
    int[] numbers = numberPairs.SelectMany(s => s.Select(i => int.Parse(i))).ToArray();
    if ((numbers[0] >= numbers[2] && numbers[1] <= numbers[3]) || (numbers[2] >= numbers[0] && numbers[3] <= numbers[1]))
        return 1;
    return 0;
}).Sum();

Console.WriteLine(result);
#endregion

#region Part Two

result = rucksacks.Select(line =>
{
    string[] pair = line.Split(',');
    IEnumerable<string[]> numberPairs = pair.Select(s => s.Split('-'));
    int[] numbers = numberPairs.SelectMany(s => s.Select(i => int.Parse(i))).ToArray();
    if (Math.Max(numbers[0], numbers[2]) <= Math.Min(numbers[1],numbers[3]))
        return 1;
    return 0;
}).Sum();
Console.WriteLine(result);
#endregion
