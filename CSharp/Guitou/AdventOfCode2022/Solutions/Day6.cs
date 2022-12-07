using System.Collections.Generic;

string inputsPath = "C:\\Users\\guill\\Desktop\\AdventOfCode2022\\CSharp\\Guitou\\AdventOfCode2022\\Inputs\\"; //change to your own

string input = File.ReadAllText(inputsPath + "Input6.txt");

#region Part one
int result = 0;
for (int i = 0; i < input.Length; i++)
{
    bool isMarker = true;
    string sequence = input.Substring(i, 4);
    foreach (char c in sequence) {
        if (sequence.IndexOf(c) != sequence.LastIndexOf(c))
            isMarker = false;
    }
    if(isMarker)
    {
        result = i + 4;
        break; 
    }
}
Console.WriteLine(result);
#endregion
#region Part Two
result = 0;
for (int i = 0; i < input.Length; i++)
{
    bool isMarker = true;
    string sequence = input.Substring(i, 14);
    foreach (char c in sequence)
    {
        if (sequence.IndexOf(c) != sequence.LastIndexOf(c))
            isMarker = false;
    }
    if (isMarker)
    {
        result = i + 14;
        break;
    }
}
Console.WriteLine(result);
#endregion
