using System;
using System.Collections.Generic;
using System.IO;

namespace ConsoleApp1
{
    class Program
    {
        static void Main(string[] args)
        {
            /*
            // Make a reference to a directory.
            DirectoryInfo di = new DirectoryInfo("C:/Users/minhs/Desktop");
            // Get a reference to each file in that directory.
            FileInfo[] fiArr = di.GetFiles();
            // Display the names and sizes of the files.
            Console.WriteLine("The directory {0} contains the following files:", di.Name);
            foreach (FileInfo f in fiArr)
                Console.WriteLine("The size of {0} is {1} bytes.", f.Name, f.Length);
            */
            /*refComp A = new();
            refComp B = new();

            Console.WriteLine(A == B);*/


        }
    }

    /*class refComp
    {
        private string A;
        private int B;
        public string C;
    }*/

    class myVector
    {
        public double x;
        public double y;

        public void UseAdd(double x2, double y2)
        {
            this.x += x2;
            this.y += y2;
        }

        public void UseSubtraction(double x2, double y2)
        {
            this.x -= x2;
            this.y -= y2;
        }

        public void UseScalar(double s)
        {
            this.x *= s;
            this.y *= s;
        }

        public Tuple<double,double> UseMutate(double s)
        {
            return Tuple.Create(this.x*s, this.y*s);
        }
    }
}
