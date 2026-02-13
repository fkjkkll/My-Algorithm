

using System.Runtime.InteropServices;

Item[] items = new Item[3]
{
    new Item() { Id = 1, Num = 1 },
    new Item() { Id = 2, Num = 2 },
    new Item() { Id = 3, Num = 3 },
};
var span = items.AsSpan();

var bSpan = MemoryMarshal.Cast<Item, int>(span);
foreach (var n in bSpan)
{
    Console.WriteLine(n);
}


public struct Item
{
    public int Id;
    public int Num;
    public override string ToString()
    {
        return $"{Id} {Num}";
    }
}