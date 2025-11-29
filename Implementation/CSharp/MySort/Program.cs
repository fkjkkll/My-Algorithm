using System.Diagnostics;

var random = new Random();
int range = 100000;
int distribute = 100;
var arr = Enumerable.Range(0, range).Select(_ => random.Next(0, distribute)).ToArray();

//arr = new int[] { 5, 4, 3, 2, 1 };

Stopwatch stopwatch = new();
stopwatch.Start();

MySort.QuickSort(arr);

stopwatch.Stop();
Console.WriteLine($"执行时间: {stopwatch.ElapsedMilliseconds} ms");

if (range <= 10000)
    MySort.ShowLog(arr);

public static partial class MySort
{
    public static void QuickSortTest<T>(IList<T> arr) where T : IComparable<T>
    {
        QuickSortTest1(arr, 0, arr.Count - 1);
    }

    public static void QuickSortTest1<T>(IList<T> arr, int l, int r) where T : IComparable<T>
    {
        if (r - l < 16)
        {
            InsertSort(arr, l, r);
            return;
        }
        var pivot = arr[l];
        int left = l;
        for (int explorer = l + 1; explorer <= r; ++explorer)
        {
            if (arr[explorer].CompareTo(pivot) < 0)
            {
                ++left;
                Swap(arr, explorer, left);
            }
        }
        Swap(arr, left, l);
        QuickSortTest1(arr, l, left - 1);
        QuickSortTest1(arr, left + 1, r);
    }

}