using System.Collections.Generic;
using System.Text;

string inputsPath = "C:\\Users\\guill\\Desktop\\AdventOfCode2022\\CSharp\\Guitou\\AdventOfCode2022\\Inputs\\"; //change to your own

string input = File.ReadAllText(inputsPath + "Input10.txt");

#region Part one

string[] lines = input.Split(Environment.NewLine);
int result = 0;
int currentCycle = 0;
int X = 1;
foreach (var line in lines)
{
    string[] split = line.Split(' ');
    switch (split[0])
    {
        case "addx":
            currentCycle++;
            CheckX();
            currentCycle++;
            CheckX();
            X += int.Parse(split[1]);
            break;
        case "noop":
            currentCycle++;
            CheckX();
            break;

    }
}

void CheckX()
{
    if ((currentCycle - 20) % 40 == 0)
        result += X * currentCycle;
}

Console.WriteLine(result);

#endregion
#region Part Two

currentCycle = 0;
X = 1;
foreach (var line in lines)
{
    string[] split = line.Split(' ');
    switch (split[0])
    {
        case "addx":
            currentCycle++;
            DrawPixel();
            currentCycle++;
            DrawPixel();
            X += int.Parse(split[1]);
            break;
        case "noop":
            currentCycle++; 
            DrawPixel();
            break;
    }
}

void DrawPixel()
{
    if ((currentCycle - 1) % 40 == 0)
        Console.Write(Environment.NewLine);

    if (Math.Abs(X - ((currentCycle - 1) % 40)) <= 1)
        Console.Write('#');
    else
        Console.Write('.');
}
#endregion
