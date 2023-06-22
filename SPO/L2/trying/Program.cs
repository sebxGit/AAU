using System;

namespace trying
{
    class Program
    {
        static void Main(string[] args)
        {
            int[] arr = new int[] { 6, 4, 3, 2, 5, 8 };
            qsort(arr);
        }
    }
    void qsort(int[] arr)
    {
        int[] j = new();
        int[] k = new();
        int pivot = arr[arr.Length - 1];
        System.Console.WriteLine(pivot);
    }
}
