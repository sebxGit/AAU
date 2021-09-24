using System;

namespace Employeetc
{
    class Program
    {
        /* 1. private encapsulates that the variable is only available in the current class.
         *    protected means that the variable is only accessible in the class itself or a subclass
         *    public means that it is available in any way.
         */
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
        }
    }

    class Employee
    {
        protected string name;
        protected string jobTitle;
        protected double salary;
        protected int levelPerc;

        public Employee(string name, string jobTitle, double salary, int levelPerc)
        {
            this.name = name;
            this.jobTitle = jobTitle;
            this.salary = salary;
            this.levelPerc = levelPerc;
        }

        public virtual double CalculateYearlySalary() 
        {
            return (salary * levelPerc) * 12;
        }
    }
    
    class Manager : Employee
    {
        private double bonus;
        public Manager(string name, string jobTitle, double salary, int levelPerc, double bonus) : base(name,jobTitle, salary, levelPerc)
        {
            this.bonus = bonus;
        }

        public override double CalculateYearlySalary()
        {
            return (salary * levelPerc * bonus) * 12;
        }

    }

}
