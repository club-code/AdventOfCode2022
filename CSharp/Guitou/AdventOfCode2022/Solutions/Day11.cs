using System.Collections.Generic;
using System.Numerics;
using System.Text;

string inputsPath = "C:\\Users\\guill\\Desktop\\AdventOfCode2022\\CSharp\\Guitou\\AdventOfCode2022\\Inputs\\"; //change to your own

string input = File.ReadAllText(inputsPath + "Input11.txt");

#region Part one

string[] lines = input.Split(Environment.NewLine);
string[] items = null;
string[] inspect = null;
int yeet = 0;
(int, int) targets = (0, 0);
Queue<(int, int)> targetMonkeys = new();
List<Monkey> monkeys = new();
foreach (var line in lines)
{
    string trimmedLine = line.Trim();
    if (trimmedLine.StartsWith("Starting"))
    {
        int index = trimmedLine.IndexOf(":", StringComparison.OrdinalIgnoreCase) + 1;
        items = trimmedLine[index..].Split(',').Select(s => s.Trim()).ToArray();
    }
    if (trimmedLine.StartsWith("Operation"))
    {
        int index = trimmedLine.IndexOf("old ", StringComparison.OrdinalIgnoreCase) + 4;
        inspect = trimmedLine[index..].Trim().Split();
    }
    if (trimmedLine.StartsWith("Test"))
    {
        int index = trimmedLine.IndexOf("by ", StringComparison.OrdinalIgnoreCase) + 3;
        yeet = int.Parse(trimmedLine[index..]);
    }
    if (trimmedLine.StartsWith("If true"))
    {
        int index = trimmedLine.IndexOf("monkey ", StringComparison.OrdinalIgnoreCase) + 7;
        targets.Item1 = int.Parse(trimmedLine[index..]);
    }
    if (trimmedLine.StartsWith("If false"))
    {
        int index = trimmedLine.IndexOf("monkey ", StringComparison.OrdinalIgnoreCase) + 7;
        targets.Item2 = int.Parse(trimmedLine[index..]);
        monkeys.Add(new Monkey(items, inspect, yeet));
        targetMonkeys.Enqueue(targets);
    }
}
int currentMonkey = 0;
while (targetMonkeys.Count > 0)
{
    var currentTargets = targetMonkeys.Dequeue();
    monkeys[currentMonkey].UpdateTargets(monkeys[currentTargets.Item1], monkeys[currentTargets.Item2]);
    currentMonkey++;
}

for (int i = 0; i < 20; i++)
{
    monkeys.ForEach(monkey => monkey.Play());
}

Console.WriteLine(monkeys.Select(monkey => monkey.Score)
    .OrderByDescending(x => x)
    .Take(2)
    .Aggregate(1, (x, y) => x * y));


#endregion
#region Part Two
targetMonkeys = new();
monkeys = new();
int ppcm = 1;
foreach (var line in lines)
{
    string trimmedLine = line.Trim();
    if (trimmedLine.StartsWith("Starting"))
    {
        int index = trimmedLine.IndexOf(":", StringComparison.OrdinalIgnoreCase) + 1;
        items = trimmedLine[index..].Split(',').Select(s => s.Trim()).ToArray();
    }
    if (trimmedLine.StartsWith("Operation"))
    {
        int index = trimmedLine.IndexOf("old ", StringComparison.OrdinalIgnoreCase) + 4;
        inspect = trimmedLine[index..].Trim().Split();
    }
    if (trimmedLine.StartsWith("Test"))
    {
        int index = trimmedLine.IndexOf("by ", StringComparison.OrdinalIgnoreCase) + 3;
        yeet = int.Parse(trimmedLine[index..]);
        ppcm *= yeet;
    }
    if (trimmedLine.StartsWith("If true"))
    {
        int index = trimmedLine.IndexOf("monkey ", StringComparison.OrdinalIgnoreCase) + 7;
        targets.Item1 = int.Parse(trimmedLine[index..]);
    }
    if (trimmedLine.StartsWith("If false"))
    {
        int index = trimmedLine.IndexOf("monkey ", StringComparison.OrdinalIgnoreCase) + 7;
        targets.Item2 = int.Parse(trimmedLine[index..]);
        monkeys.Add(new Monkey(items, inspect, yeet, 1));
        targetMonkeys.Enqueue(targets);
    }
}

currentMonkey = 0;
while (targetMonkeys.Count > 0)
{
    var currentTargets = targetMonkeys.Dequeue();
    monkeys[currentMonkey].UpdateTargets(monkeys[currentTargets.Item1], monkeys[currentTargets.Item2]);
    monkeys[currentMonkey].UpdatePPCM(ppcm);
    currentMonkey++;
}

for (int i = 0; i < 10000; i++)
{
    monkeys.ForEach(monkey => monkey.Play());
}
Console.WriteLine(monkeys.Select(monkey => monkey.Score)
    .OrderByDescending(x => x)
    .Take(2)
    .Aggregate((long)1, (x, y) => x * y));
#endregion

class Monkey
{
    private Queue<long> items;
    private Func<long, long> inspect;
    private Monkey? firstTarget;
    private Monkey? secondTarget;
    private int offset;
    private int yeetFactor;

    private int worryDiviser;
    private int ppcm = int.MaxValue;
    public int Score = 0;
    public Monkey(string[] items, string[] inspect, int yeet, int worryDiviser = 3)
    {
        this.items = new Queue<long>();
        foreach (var item in items)
        {
            this.items.Enqueue(long.Parse(item));
        }

        bool isSquare = false;
        if (int.TryParse(inspect[1], out int result))
            offset = result;
        else
            isSquare = true;

        switch (inspect[0])
        {
            case "+":
                this.inspect = Sum;
                break;
            case "*":
                if (isSquare)
                    this.inspect = Square;
                else
                    this.inspect = Multiply;
                break;
            default:
                this.inspect = (x => x);
                break;
        }

        yeetFactor = yeet;

        this.worryDiviser = worryDiviser;

    }

    public void UpdateTargets(Monkey first, Monkey second)
    {
        firstTarget = first;
        secondTarget = second;
    }
    public void Play()
    {
        while (items.Count > 0)
        {
            long item = items.Dequeue();
            item = (long)Math.Floor(inspect(item) % ppcm / (float)worryDiviser);
            Score++;
            if (Yeet(item))
            {
                firstTarget.items.Enqueue(item);
            }
            else
            {
                secondTarget.items.Enqueue(item);
            }
        }
    }

    private long Sum(long old)
    {
        return old + offset;
    }

    private long Multiply(long old)
    {
        return old * offset;
    }

    private long Square(long old)
    {
        return old * old;
    }
    private bool Yeet(long item)
    {
        return item % yeetFactor == 0;
    }

    internal void UpdatePPCM(int ppcm)
    {
        this.ppcm = ppcm;
    }
}

