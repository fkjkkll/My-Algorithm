using System.Diagnostics;

var random = new Random();
int range = 100000;
var arr = Enumerable.Range(0, range).Select(_ => random.Next(0, range + 1)).ToArray();



Stopwatch stopwatch = new();
stopwatch.Start();

MySort.MergeSort(arr);

stopwatch.Stop();
Console.WriteLine($"执行时间: {stopwatch.ElapsedMilliseconds} ms");

if (range <= 10000)
    MySort.ShowLog(arr);

public static partial class MySort
{
    
}