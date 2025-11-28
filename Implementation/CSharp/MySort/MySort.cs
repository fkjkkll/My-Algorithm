public static partial class MySort
{
    // 冒泡排序
    public static void BubbleSort<T>(IList<T> arr) where T : IComparable<T>
    {
        for (int last = arr.Count - 1; last > 0; --last)
        {
            var end = true;
            for (int i = 0; i < last; ++i)
            {
                if (arr[i].CompareTo(arr[i + 1]) > 0)
                {
                    Swap(arr, i, i + 1);
                    end = false;
                }
            }
            if (end)
                break;
        }
    }

    // 插入排序
    public static void InsertSort<T>(IList<T> arr) where T : IComparable<T>
    {
        for (int i = 1; i < arr.Count; ++i)
        {
            var pre = i - 1;
            var origin = arr[i];
            for (; pre >= 0; --pre)
            {
                if (arr[pre].CompareTo(origin) > 0)
                    arr[pre + 1] = arr[pre];
                else
                    break;
            }
            arr[pre + 1] = origin;
        }
    }

    // 希尔排序
    public static void ShellSort<T>(IList<T> arr) where T : IComparable<T>
    {
        int power = PowerOfTwoFloor(arr.Count);
        for (int delta = power - 1; delta >= 1; delta = power - 1)
        {
            for (int cur = delta; cur < arr.Count; ++cur)
            {
                var temp = arr[cur];
                var pre = cur - delta;
                for (; pre >= 0; pre -= delta)
                {
                    if (arr[pre].CompareTo(temp) > 0)
                        arr[pre + delta] = arr[pre];
                    else
                        break;
                }
                arr[pre + delta] = temp;
            }
            power >>= 1;
        }
    }

    // 选择排序
    public static void SelectSort<T>(IList<T> arr) where T : IComparable<T>
    {
        for (int i = 0; i < arr.Count - 1; ++i)
        {
            var minPosition = i;
            for (int j = i; j < arr.Count; ++j)
            {
                if (arr[j].CompareTo(arr[minPosition]) < 0)
                    minPosition = j;
            }
            if (i != minPosition)
                Swap(arr, i, minPosition);
        }
    }

    // 堆排序
    public static void HeapSort<T>(IList<T> arr) where T : IComparable<T>
    {
        int count = arr.Count;
        for (int subRoot = (arr.Count - 2) >> 1; subRoot >= 0; --subRoot)
            PriorityQueueDown(arr, subRoot, count);
        for (int left = arr.Count - 1; left > 0; --left)
        {
            Swap(arr, 0, left);
            PriorityQueueDown(arr, 0, left);
        }
    }

    // 归并排序
    public static void MergeSort<T>(IList<T> arr) where T : IComparable<T>
    {
        List<T> tempList = new(arr);
        //DoMergeSortRecursive(arr, tempList, 0, arr.Count - 1);
        DoMergeSortIterative(arr, tempList);
    }

    private static void DoMergeSortRecursive<T>(IList<T> arr, IList<T> tempList, int l, int r) where T : IComparable<T>
    {
        if (l >= r)
            return;
        int m = (l + r) >> 1;
        DoMergeSortRecursive(arr, tempList, l, m);
        DoMergeSortRecursive(arr, tempList, m + 1, r);
        Merge(arr, tempList, l, m + 1, r);
        for (int i = l; i <= r; i++)
            arr[i] = tempList[i];
    }

    // 公用merge
    private static void Merge<T>(IList<T> arr, IList<T> tempList, int lStart, int rStart, int rEnd) where T : IComparable<T>
    {
        var lEnd = rStart - 1;
        var indexT = lStart;
        while (lStart <= lEnd && rStart <= rEnd)
        {
            if (arr[lStart].CompareTo(arr[rStart]) <= 0) tempList[indexT++] = arr[lStart++];
            else tempList[indexT++] = arr[rStart++];
        }
        while (lStart <= lEnd) tempList[indexT++] = arr[lStart++];
        while (rStart <= rEnd) tempList[indexT++] = arr[rStart++];
    }

    // 这一步最是精髓
    private static void DoMergeSortIterative<T>(IList<T> arr, IList<T> tempList) where T : IComparable<T>
    {
        int mergeSize = 1;
        while (mergeSize < arr.Count)
        {
            DoMergeOnce(arr, tempList, mergeSize);
            mergeSize <<= 1;
            DoMergeOnce(tempList, arr, mergeSize);
            mergeSize <<= 1;
        }
    }

    private static void DoMergeOnce<T>(IList<T> arr, IList<T> tempList, int mergeSize) where T : IComparable<T>
    {
        int lStart = 0;
        for (; lStart + (mergeSize << 1) - 1 < arr.Count; lStart += mergeSize << 1)
        {
            int rStart = lStart + mergeSize;
            int rEnd = rStart + mergeSize - 1;
            Merge(arr, tempList, lStart, rStart, rEnd);
        }
        if (lStart + mergeSize < arr.Count)
            Merge(arr, tempList, lStart, lStart + mergeSize, arr.Count - 1);
        else if (lStart < arr.Count)
            Merge(arr, tempList, lStart, arr.Count, arr.Count - 1);
    }
}