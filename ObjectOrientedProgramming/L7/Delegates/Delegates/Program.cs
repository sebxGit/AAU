using System;
using System.Collections.Generic;

namespace Delegates
{
    class Program
    {
        static void Main(string[] args)
        {
        }
    }

    class smth
    {
        private delegate string StringJoin(string a, string b);

        string ConcatString(string l, string r) { return 1 + r; }

        string JoinThree(string r, string k, string l, StringJoin f) => f(r, f(k, l));

        string JoinAllStrings(List<String> lst, StringJoin f)
        {
            string fullStr = "";
            for(int i=0; i<lst.Count - 1; i++)
            {
                fullStr = f(lst[i], lst[i + 1]);
            }
            return fullStr;
        }

        string Join<T> (T a, T b)
        {

        }
    }
}
