using System;

namespace ITaxable
{
    class Program
    {
        static void Main(string[] args)
        {
            Bus bus = new(1, 1, 02);
            House house = new("aalborg", true, 0.5, 02);


            bus.TaxValue();
            house.TaxValue();

        }
    }

    interface ITaxable
    {
        double TaxValue();
    }

    public class FixedProperty
    {

        protected string location;
        protected bool inCity;
        protected decimal estimatedValue;

        public FixedProperty(string location, bool inCity, decimal value)
        {
            this.location = location;
            this.inCity = inCity;
            this.estimatedValue = value;
        }

        public FixedProperty(string location) :
            this(location, true, 1000000)
        {
        }

        public string Location
        {
            get
            {
                return location;
            }
        }
    }

    public class Vehicle
    {

        protected int registrationNumber;
        protected double maxVelocity;
        protected decimal value;

        public Vehicle(int registrationNumber, double maxVelocity,
                        decimal value)
        {
            this.registrationNumber = registrationNumber;
            this.maxVelocity = maxVelocity;
            this.value = value;
        }

        public int RegistrationNumber
        {
            get
            {
                return registrationNumber;
            }
        }

    }

    public class Bus : Vehicle, ITaxable
    {

        protected int numberOfSeats;

        public Bus(int numberOfSeats, int regNumber, decimal value) :
            base(regNumber, 80, value)
        {
            this.numberOfSeats = numberOfSeats;
        }

        public int NumberOfSeats
        {
            get
            {
                return numberOfSeats;
            }
        }

        public double TaxValue()
        {
            return 0.2;
        }

    }

    public class House : FixedProperty, ITaxable
    {

        protected double area;

        public House(string location, bool inCity, double area,
                        decimal value) :
            base(location, inCity, value)
        {
            this.area = area;
        }

        public double Area
        {
            get
            {
                return area;
            }
        }

        public double TaxValue()
        {
            return 0.1;
        }
    }
}
