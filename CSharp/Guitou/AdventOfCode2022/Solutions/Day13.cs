using System.Collections;
using System.Collections.Generic;
using System.Numerics;
using System.Text;

string inputsPath = "C:\\Users\\guill\\Desktop\\AdventOfCode2022\\CSharp\\Guitou\\AdventOfCode2022\\Inputs\\"; //change to your own

string input = File.ReadAllText(inputsPath + "Input13.txt");
#region Part one

string[] lines = input.Split(Environment.NewLine);
int result = 0;
for(int i=0; i < (lines.Length+1)/3; i++)
{
    string left = lines[3*i];
    string right = lines[3*i + 1];

    if (Compare(Parse(left), Parse(right)) != -1)
       result += i + 1;
}

Console.WriteLine(result);

#endregion

#region PartTwo

var allPackets = new List<List<object>>() { Parse("[[2]]") , Parse("[[6]]")};

foreach(var line in lines)
{
    if(!string.IsNullOrEmpty(line))
        allPackets.Add(Parse(line));
}

allPackets.Sort((x,y) => Compare(y,x));

var result2 = (allPackets.FindIndex(list => Compare(list, Parse("[[2]]")) == 0)+1) * (allPackets.FindIndex(list => Compare(list, Parse("[[6]]")) == 0)+1);

Console.WriteLine(result2);
#endregion

List<object> Parse(string left)
{
    Stack<List<object>> ListStack = new();
    var split = left.Split(','); 

    foreach(string s in split)
    {
        for (int i = 0; i < s.Length; i++)
        {
            if (s[i] == '[')
            {
                ListStack.Push(new List<object>());
            }
            else if (s[i] == ']')
            {
                var list = ListStack.Pop();
                if (ListStack.Count > 0)
                    ListStack.Peek().Add(list);
                else
                {
                    return list;
                }
            }
            else
            {
                if (i != 0)
                {
                    if(!int.TryParse(s[i - 1].ToString(), out int current))
                    {
                        if (!s.Contains(']'))
                            ListStack.Peek().Add(int.Parse(s[i..].ToString()));
                        else
                            ListStack.Peek().Add(int.Parse(s[i..s.IndexOf(']')].ToString()));
                    }
                }
                else
                {
                    if (!s.Contains(']'))
                        ListStack.Peek().Add(int.Parse(s[i..].ToString()));
                    else
                        ListStack.Peek().Add(int.Parse(s[i..s.IndexOf(']')].ToString()));
                }
            }
        }
    }
    return null;
}

int Compare(List<object> left, List<object> right)
{
    for(int i = 0; i < Math.Min(left.Count, right.Count); i++)
    {
        if (left[i] is int first && right[i] is int second) {
            if (first > second)
                return -1;
            if (first < second)
                return 1;
        }
        else if (left[i] is int intFirst && right[i] is List<object> ListSecond) {
            var res = Compare(new List<object>() { intFirst }, ListSecond);
            if(res != 0)
                return res;

        }
        else if (left[i] is List<object> ListFirst && right[i] is int intSecond)
        {
            var res = Compare(ListFirst, new List<object>() { intSecond });
            if (res != 0)
                return res;
        }
        else if (left[i] is List<object> firstList && right[i] is List<object> secondList)
        {
            var res = Compare(firstList, secondList);
            if (res != 0)
                return res;
        }
    }

    if (left.Count < right.Count)
    {
        return 1;
    }

    if (left.Count > right.Count)
    {
        return -1;
    }

    return 0;
}

