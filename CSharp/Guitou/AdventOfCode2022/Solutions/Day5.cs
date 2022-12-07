using System.Collections.Generic;

string inputsPath = "C:\\Users\\guill\\Desktop\\AdventOfCode2022\\CSharp\\Guitou\\AdventOfCode2022\\Inputs\\"; //change to your own

string input = File.ReadAllText(inputsPath + "Input5.txt");

#region Part one
string[] lines = input.Split(Environment.NewLine);

int nbCrates = (lines[0].Length+1) / 4;
Stack<char>[] revStacks = new Stack<char>[nbCrates];
for(int i =0; i < revStacks.Length; i++)
{
    revStacks[i] = new Stack<char>();
}
Stack<char>[] stacks = new Stack<char>[nbCrates];
foreach (string line in lines)
{
    if(string.IsNullOrEmpty(line))
        continue;
    if (line[1] != 1 && !line.Contains("move"))
    {
        for (int i = 0; i < nbCrates; i++)
        {
            if (line[i * 4] == '[')
            {
                revStacks[i].Push(line[i*4 + 1]);
            }
        }
    }
    if (line[1] == '1')
    {
        stacks = revStacks.Select(revStack =>
        {
            Stack<char> stack = new();
            while (revStack.Count > 0)
                stack.Push(revStack.Pop());
            return stack;
        }).ToArray();
    }

    if (line.Contains("move"))
    {
        string[] mov = line.Split(' ');
        for (int i = 0; i < int.Parse(mov[1]); i++)
        {
            stacks[int.Parse(mov[5])-1].Push(stacks[int.Parse(mov[3])-1].Pop());
        }
    }
}

stacks.ToList().ForEach(stack => Console.Write(stack.Pop()));
#endregion
Console.WriteLine();
#region Part Two
Stack<char>[] revStacks2 = new Stack<char>[nbCrates];
for (int i = 0; i < revStacks.Length; i++)
{
    revStacks[i] = new Stack<char>();
}
Stack<char>[] stacks2 = new Stack<char>[nbCrates];
foreach (string line in lines)
{
    if (string.IsNullOrEmpty(line))
        continue;
    if (line[1] != 1 && !line.Contains("move"))
    {
        for (int i = 0; i < nbCrates; i++)
        {
            if (line[i * 4] == '[')
            {
                revStacks[i].Push(line[i * 4 + 1]);
            }
        }
    }
    if (line[1] == '1')
    {
        stacks = revStacks.Select(revStack =>
        {
            Stack<char> stack = new();
            while (revStack.Count > 0)
                stack.Push(revStack.Pop());
            return stack;
        }).ToArray();
    }

    if (line.Contains("move"))
    {
        string[] mov = line.Split(' ');
        Stack<char> stack = new();
        for (int i = 0; i < int.Parse(mov[1]); i++)
        {
            stack.Push(stacks[int.Parse(mov[3]) - 1].Pop());
        }
        while (stack.Count > 0)
            stacks[int.Parse(mov[5]) - 1].Push(stack.Pop());
    }
}

stacks.ToList().ForEach(stack => Console.Write(stack.Pop()));
#endregion
