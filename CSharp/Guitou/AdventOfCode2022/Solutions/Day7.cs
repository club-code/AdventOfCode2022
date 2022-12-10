using System.Collections.Generic;
using System.Text;

string inputsPath = "C:\\Users\\guill\\Desktop\\AdventOfCode2022\\CSharp\\Guitou\\AdventOfCode2022\\Inputs\\"; //change to your own

string input = File.ReadAllText(inputsPath + "Input7.txt");

#region Part one

string[] lines = input.Split(Environment.NewLine);
int result = 0;
Dictionary<string, int> folders = new();
Stack<string> folderStack = new();
foreach(string line in lines)
{
    string[] split = line.Split(' ');
    if (split[0] == "$" && split[1] == "cd" && split[2] != "..")
    {
        StringBuilder path = new();
        foreach (var folder in folderStack)
        {
            path.Append(folder);
            path.Append('/');
        }
        path.Append(split[2]);

        folderStack.Push(path.ToString());
    }

    if (int.TryParse(split[0], out int number))
    {
        foreach (var folder in folderStack)
        {
            if(!folders.TryAdd(folder, number))
                folders[folder] += number;
        }
    }
    if (split[0] == "$" && split[1] == "cd" && split[2] == "..")
    {
       var x = folderStack.Pop();
    }
}

foreach(KeyValuePair<string, int> pair in folders) {
    if (pair.Value < 100000)
        result += pair.Value;
}

Console.WriteLine(result);
#endregion
#region Part Two
long spaceToFree = 30000000 - (70000000 - folders["/"]);
long min = folders["/"];
foreach (KeyValuePair<string, int> pair in folders)
{
    if (pair.Value > spaceToFree && pair.Value < min)
        min = pair.Value;
}
Console.WriteLine(min);
#endregion
