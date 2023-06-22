using System;
using System.Collections.Generic;

namespace Generics_exercises
{
    class Program
    {
        static void Main(string[] args)
        {
            HandyMethods<int> a = new();
            List<int> Mylist = new() { 1, 2, 3, 4, 5, 6, 6, 7, 8, 9 };

            a.Max<int>(Mylist);
        }
    }

    class HandyMethods<T>
    {
        // 1a
        public T Max<T>(List<T> list) where T : IComparable<T>
        {
            T max = list[0];
            for (int i = 0; i < list.Count - 1; i++)
            {
                bool a = !EqualityComparer<T>.Default.Equals(list[i], list[i + 1]);
                if(a) max = list[i];
                else  max = list[i + 1];
            }
            return max;
        }

        // 1b
        public T Min<T>(List<T> list) where T : IComparable<T>
        {
            T max = list[0];
            for (int i = 0; i < list.Count - 1; i++)
            {
                bool a = !EqualityComparer<T>.Default.Equals(list[i], list[i + 1]);
                if (a) max = list[i + 1];
                else max = list[i];
            }
            return max;
        }

        // 1c
        public void randint<T>(List<T> list)
        {
        Random rnd = new Random();
            foreach( var item in list)
            {
                int a = rnd.Next(1, 100);
                int b = rnd.Next(1, 100);
                int tempvar = a;
                a = b;
                b = tempvar;
            }
        }
    }

    class Pair<T1, T2>
    {
        public Pair(T1 fst, T2 snd)
        {
            first = fst;
            second = snd;
        }
        public T1 first { get; }
        public T2 second { get; }

        public (T2 second, T1 first) swap<T>()
        {
            return (second, first);
        }

        Tuple<T1, C> setFst<C>(Tuple<C, C> tuple)
        {
            return Tuple.Create(first, tuple.Item2);
        }

        Tuple<C, T2> setSnd<C>(Tuple<C, C> tuple) 
        {
            return Tuple.Create(tuple.Item1, second);
        }

    }

    class Dict<K, V>
    {
        List<Pair<K, V>> data = new();
        public V Get(K key)
        {
            foreach (var item in data)
            {
                if (item.first.Equals(key))
                    return item.second;
            }
            throw new KeyNotFoundException();
        }

        public void Set(K key, V val)
        {
            for (int i = 0; i < data.Count; i++)
            {
                if (data[i].first.Equals(key))
                {
                    data[i] = new Pair<K, V>(key, val);
                    return;
                }
            }
            data.Add(new Pair<K, V>(key, val));
        }
    }
}

