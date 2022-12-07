string inputsPath = "C:\\Users\\guill\\Desktop\\AdventOfCode2022\\CSharp\\Guitou\\AdventOfCode2022\\Inputs\\"; //change to your own

string input = File.ReadAllText(inputsPath + "Input3.txt");

#region Part one
string[] rucksacks = input.Split(Environment.NewLine);

int result = rucksacks.Select(line =>
{
    var first = line.Take(line.Length / 2);
    var second = line.Skip(line.Length / 2);
    char uniqueChar = 'A';
    foreach (char c in first)
    {
        if (second.Contains(c))
        {
            uniqueChar = c;
            break;
        }
    }
    return uniqueChar.ToString().ToUpper() == uniqueChar.ToString() ? uniqueChar - 'A' + 27 : uniqueChar - 'a' + 1;
}).Sum();

Console.WriteLine(result);
#endregion

#region Part Two

result = 0;
int i = 0;
string first = string.Empty;
string second = string.Empty;

foreach (string ruck in rucksacks)
{
    switch (i)
    {
        case 0:
            first = ruck;
            i++;
            break;
        case 1:
            second = ruck;
            i++;
            break;
        case 2:
            char uniqueChar = 'A';
            foreach (char c in ruck)
            {
                if (first.Contains(c) && second.Contains(c))
                {
                    uniqueChar = c;
                    break;
                }
            }
            result += uniqueChar.ToString().ToUpper() == uniqueChar.ToString() ? uniqueChar - 'A' + 27 : uniqueChar - 'a' + 1;
            i = 0;
            break;
    }
}

Console.WriteLine(result);
#endregion
