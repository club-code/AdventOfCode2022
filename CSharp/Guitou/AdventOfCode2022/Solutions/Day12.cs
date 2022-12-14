using System.Collections.Generic;
using System.Numerics;
using System.Text;

string inputsPath = "C:\\Users\\guill\\Desktop\\AdventOfCode2022\\CSharp\\Guitou\\AdventOfCode2022\\Inputs\\"; //change to your own

string input = File.ReadAllText(inputsPath + "Input12.txt");
#region Part one

string[] lines = input.Split(Environment.NewLine);
var start = new Tile
{
    Y = Array.FindIndex(lines, x => x.Contains('S'))
};
start.X = lines[start.Y].IndexOf('S');

var finish = new Tile();
finish.Y = Array.FindIndex(lines, x => x.Contains('E'));
finish.X = lines[finish.Y].IndexOf('E');

string[] map = new string[lines.Length];

lines.CopyTo(map, 0);

Console.WriteLine(AStar(map, start, finish));

#endregion

#region PartTwo
var startList = new List<Tile>();

List<int> YIndexes = lines.Select((value, index) => new { value, index }).Where(x => x.value.Contains('a')).Select(x => x.index).Distinct().ToList();
foreach(int yIndex in YIndexes)
{
    List<int> XIndexes = lines[yIndex].Select((value, index) => new { value, index }).Where(x => x.value == 'a').Select(x => x.index).ToList();
    foreach(int xIndex in XIndexes)
    {
        startList.Add(new Tile()
        {
            X = xIndex,
            Y = yIndex
        });
    }
}

Console.WriteLine(startList.Select(tile => 
    {
        map = new string[lines.Length];
        lines.CopyTo(map, 0);
        return AStar(map, tile, finish);
    })
    .Where(result => result > 0).Min());

#endregion



List<Tile> GetWalkableTiles(string[] map, Tile currentTile, Tile targetTile)
{
    var possibleTiles = new List<Tile>()
    {
        new Tile { X = currentTile.X, Y = currentTile.Y - 1, Parent = currentTile, Cost = currentTile.Cost + 1 },
        new Tile { X = currentTile.X, Y = currentTile.Y + 1, Parent = currentTile, Cost = currentTile.Cost + 1 },
        new Tile { X = currentTile.X - 1, Y = currentTile.Y, Parent = currentTile, Cost = currentTile.Cost + 1 },
        new Tile { X = currentTile.X + 1, Y = currentTile.Y, Parent = currentTile, Cost = currentTile.Cost + 1 },
    };

    possibleTiles.ForEach(tile => tile.SetDistance(targetTile.X, targetTile.Y));

    var maxX = map.First().Length - 1;
    var maxY = map.Length - 1;

    return possibleTiles
            .Where(tile => tile.X >= 0 && tile.X <= maxX)
            .Where(tile => tile.Y >= 0 && tile.Y <= maxY)
            .Where(tile => map[tile.Y][tile.X] <= map[currentTile.Y][currentTile.X] || map[tile.Y][tile.X] == map[currentTile.Y][currentTile.X] + 1)
            .ToList();
}

int AStar(string[] map, Tile start, Tile finish)
{
    int result = 0;

    var newStartPointRow = map[start.Y].ToCharArray();
    newStartPointRow[start.X] = 'a';
    map[start.Y] = new string(newStartPointRow);

    var newFinishPointRow = map[finish.Y].ToCharArray();
    newFinishPointRow[finish.X] = 'z';
    map[finish.Y] = new string(newFinishPointRow);

    start.SetDistance(finish.X, finish.Y);

    var activeTiles = new List<Tile>
    {
        start
    };
    var visitedTiles = new List<Tile>();

    while (activeTiles.Any())
    {
        var checkTile = activeTiles.OrderBy(x => x.CostDistance).First();

        if (checkTile.X == finish.X && checkTile.Y == finish.Y)
        {
            var tile = checkTile;
            while (true)
            {
                result++;
                tile = tile.Parent;
                if (tile == null)
                {
                    return result - 1;
                }
            }
        }

        visitedTiles.Add(checkTile);
        activeTiles.Remove(checkTile);

        var walkableTiles = GetWalkableTiles(map, checkTile, finish);

        foreach (var walkableTile in walkableTiles)
        {
            if (visitedTiles.Any(x => x.X == walkableTile.X && x.Y == walkableTile.Y))
                continue;

            if (activeTiles.Any(x => x.X == walkableTile.X && x.Y == walkableTile.Y))
            {
                var existingTile = activeTiles.First(x => x.X == walkableTile.X && x.Y == walkableTile.Y);
                if (existingTile.CostDistance > checkTile.CostDistance)
                {
                    activeTiles.Remove(existingTile);
                    activeTiles.Add(walkableTile);
                }
            }
            else
            {
                activeTiles.Add(walkableTile);
            }
        }
    }

    return -1;
}

class Tile
{
    public int X { get; set; }
    public int Y { get; set; }
    public char Value { get; set; }
    public int Cost { get; set; }
    public int Distance { get; set; }
    public int CostDistance => Cost + Distance;
    public Tile Parent { get; set; }
    public void SetDistance(int targetX, int targetY)
    {
        this.Distance = Math.Abs(targetX - X) + Math.Abs(targetY - Y);
    }
}