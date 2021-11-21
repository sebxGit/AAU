namespace Generics_exercises
{
    internal class HandyMethodsBase
    {
        public static T Add<T>(List<T> list) where T : IComparable<T>
        {
            for (int i = 0; i < list.Count; i++)
            {
                int largest = list[i].CompareTo(list[i + 1]);
                if (largest < 0)
                {
                    return list[i];
                }
            }
        }
    }
}