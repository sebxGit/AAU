using System;
using System.Collections.Generic;
using System.Linq;

namespace Interfaces
{
    class Program
    {
        static void Main(string[] args)
        {
            List<Car> Cars = new()
            {
                new Car() { Make = "Skoda", Model = "Fabia", Price = 80000 },
                new Car(){Make="Skoda", Model = "Fabia", Price = 60000},
                new Car() { Make = "Skoda", Model = "Something", Price = 30000 },
                new Car(){Make="Skoda", Model = "Octavia", Price = 50000},
                new Car() { Make = "Renault", Model = "Clio", Price = 40000 }
            };
            Car a = new();
            a.SortCarsPrice(Cars);
            Cars.Sort(a);
            foreach (var car in Cars)
            {
                Console.WriteLine($"{car.Make}, {car.Model}, {car.Price}");
            }
        }
    }

    interface IComparable
    {
        void SortCarsPrice(List<Car> Cars);
    }



    class Car : IComparable, IComparer<Car>
    {
        public string Make { get; set; }
        public string Model { get; set; }
        public double Price { get; set; }

        public void SortCarsPrice(List<Car> Cars)
        {
            List<Car> SortedCars = Cars.OrderBy(Car => Car.Price).ToList();
            /*foreach (Car item in SortedCars)
            {
                Console.WriteLine($"{item.Make}, {item.Model}, {item.Price}");
            }*/
        }

        int IComparer<Car>.Compare(Car x, Car y)
        {
            /* 1b
            int res = x.Make.CompareTo(y.Make);

            if (res == 0)
            {
                res = x.Model.CompareTo(y.Model);
            }

            if (res == 0)
            {
                res = x.Price.CompareTo(y.Price);
            }*/
            int res = x.Model.CompareTo(y.Model);

            if (res == 0)
            {
                res = x.Price.CompareTo(y.Price);
            }
            return res;
        }
    }
}
