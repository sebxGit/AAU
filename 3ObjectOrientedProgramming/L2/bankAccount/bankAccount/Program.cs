using System;

namespace bankAccount
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
        }
    }

    class BankAccount
    {
        protected double balance;
        protected double borrowingRate = 0.10;
        protected double savingsRate = 0.01;

        void deposit(double value)
        {
            if (balance + value > 250000)
            {
                Console.WriteLine("You cannot deposit more than 250.000");
                return;
            } else if (value < 0)
            {
                Console.WriteLine("You cannot deposit a negative amount of money");
            }
            balance += value;
        }

        void withdraw(double value)
        {
            if(balance + value < -100000)
            {
                Console.WriteLine("You cannot withdraw below -100.000.");
                return;
            } else if (value < 0)
            {
                Console.WriteLine("You cannot deposit a negative amount of money");
            }
            balance -= value;
        }

        void changeBorrowingRate(double value)
        {
            if (value < 0.06)
            {
                Console.WriteLine("You cannot borrow at this low value.");
                return;
            }
            borrowingRate = value;
        }

        void changeSavingsRate(double value)
        {
            if (value > 0.02)
            {
                Console.WriteLine("You cannot save at this high value.");
                return;
            }
            borrowingRate = value;
        }
    }
}
