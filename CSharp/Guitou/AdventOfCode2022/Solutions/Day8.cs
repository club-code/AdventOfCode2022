using System.Collections.Generic;
using System.Text;

string inputsPath = "C:\\Users\\guill\\Desktop\\AdventOfCode2022\\CSharp\\Guitou\\AdventOfCode2022\\Inputs\\"; //change to your own

string input = File.ReadAllText(inputsPath + "Input8.txt");

#region Part one

string[] lines = input.Split(Environment.NewLine);
int width = lines[0].Length;
int height = lines.Length;
int result = width*2 + (height-2)*2 ;

for (int line=1; line < height - 1; line++)
{
    for(int column = 1; column < width - 1; column++)
    {
        int current = int.Parse(lines[line][column].ToString());
        bool northBlocked = false;
        bool southBlocked = false;
        bool eastBlocked = false;
        bool westBlocked = false;
        for (int i = 0; i < line; i++)
        {
            if (int.Parse(lines[i][column].ToString()) >= current)
                northBlocked = true;
        }
        for (int i = line+1; i < height; i++)
        {
            if (int.Parse(lines[i][column].ToString()) >= current)
                southBlocked = true;
        }
        for (int i = 0; i < column; i++)
        {
            if (int.Parse(lines[line][i].ToString()) >= current)
                eastBlocked = true;
        }
        for (int i = column+1; i < width; i++)
        {
            if (int.Parse(lines[line][i].ToString()) >= current)
                westBlocked = true;
        }
        if (!(northBlocked && southBlocked && eastBlocked && westBlocked))
            result += 1;
    }
}  

Console.WriteLine(result);
#endregion
#region Part Two

int maxScore = 0;
for (int line = 1; line < height - 1; line++)
{
    for (int column = 1; column < width - 1; column++)
    {
        int current = int.Parse(lines[line][column].ToString());
        int score = 1;
        for (int i = line-1; i >= 0; i--)
        {
            if (int.Parse(lines[i][column].ToString()) >= current || i==0)
            {
                score *= line - i;
                break;
            }
        }
        for (int i = line + 1; i < height; i++)
        {
            if (int.Parse(lines[i][column].ToString()) >= current || i == height - 1)
            {
                score *= i - line;
                break;
            }
        }
        for (int i = column-1; i >= 0; i--)
        {
            if (int.Parse(lines[line][i].ToString()) >= current || i == 0)
            {
                score *= column - i;
                break;
            }
        }
        for (int i = column + 1; i < width; i++)
        {
            if (int.Parse(lines[line][i].ToString()) >= current || i == width - 1)
            {
                score *= i - column;
                break;
            }
        }
        if (score > maxScore)
            maxScore = score;
        
    }
}

Console.WriteLine(maxScore);
#endregion
