using System.Collections.Generic;
using System.Text;

string inputsPath = "C:\\Users\\guill\\Desktop\\AdventOfCode2022\\CSharp\\Guitou\\AdventOfCode2022\\Inputs\\"; //change to your own

string input = File.ReadAllText(inputsPath + "Input9.txt");

#region Part one

string[] lines = input.Split(Environment.NewLine);
(int, int) headPosition = (0,0);
(int,int) tailPosition = (0,0);
HashSet<(int,int)> grid = new();

foreach(var line in lines)
{
    string[] split = line.Split(' ');
    switch (split[0])
    {
        case "U":
            for(int i = 0; i < int.Parse(split[1]);i++)
            {
                headPosition.Item2 += 1;
                TailFollow(headPosition, ref tailPosition);
                grid.Add(tailPosition);
            }
            break;
        case "D":
            for (int i = 0; i < int.Parse(split[1]); i++)
            {
                headPosition.Item2 -= 1;
                TailFollow(headPosition, ref tailPosition);
                grid.Add(tailPosition);
            }
            break;
        case "R":
            for (int i = 0; i < int.Parse(split[1]); i++)
            {
                headPosition.Item1 += 1;
                TailFollow(headPosition, ref tailPosition);
                grid.Add(tailPosition);
            }
            break;
        case "L":
            for (int i = 0; i < int.Parse(split[1]); i++)
            {
                headPosition.Item1 -= 1;
                TailFollow(headPosition, ref tailPosition);
                grid.Add(tailPosition);
            }
            break;
    }
}

Console.WriteLine(grid.Count);

void TailFollow((int,int) head, ref (int,int) tail)
{
    if(Math.Abs(head.Item1 - tail.Item1) > 1)
    {
        tail.Item1 += 1*Math.Sign(head.Item1 - tail.Item1);
        if(head.Item2 != tail.Item2)
        {
            tail.Item2 += 1 * Math.Sign(head.Item2 - tail.Item2);
        }
    }
    if (Math.Abs(head.Item2 - tail.Item2) > 1)
    {
        tail.Item2 += 1 * Math.Sign(head.Item2 - tail.Item2);
        if (head.Item1 != tail.Item1)
        {
            tail.Item1 += 1 * Math.Sign(head.Item1 - tail.Item1);
        }
    }
}
#endregion
#region Part Two

(int, int)[] ropePosition = new (int, int)[10];
Array.Fill(ropePosition, (0, 0));
HashSet<(int, int)> gridPartTwo = new();

foreach (var line in lines)
{
    string[] split = line.Split(' ');
    switch (split[0])
    {
        case "U":
            for (int i = 0; i < int.Parse(split[1]); i++)
            {
                ropePosition[0].Item2 += 1;
                for(int knot = 0; knot < ropePosition.Length-1;knot++)
                    TailFollow(ropePosition[knot], ref ropePosition[knot+1]);
                gridPartTwo.Add(ropePosition[9]);
            }
            break;
        case "D":
            for (int i = 0; i < int.Parse(split[1]); i++)
            {
                ropePosition[0].Item2 -= 1;
                for(int knot = 0; knot < ropePosition.Length - 1; knot++)
                    TailFollow(ropePosition[knot], ref ropePosition[knot + 1]);
                gridPartTwo.Add(ropePosition[9]);
            }
            break;
        case "R":
            for (int i = 0; i < int.Parse(split[1]); i++)
            {
                ropePosition[0].Item1 += 1;
                for(int knot = 0; knot < ropePosition.Length - 1; knot++)
                    TailFollow(ropePosition[knot], ref ropePosition[knot + 1]);
                gridPartTwo.Add(ropePosition[9]);
            }
            break;
        case "L":
            for (int i = 0; i < int.Parse(split[1]); i++)
            {
                ropePosition[0].Item1 -= 1;
                for (int knot = 0; knot < ropePosition.Length - 1; knot++)
                    TailFollow(ropePosition[knot], ref ropePosition[knot + 1]);
                gridPartTwo.Add(ropePosition[9]);
            }
            break;
    }
}

Console.WriteLine(gridPartTwo.Count);

#endregion
