using System;

namespace ParkingMeter
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
        }
    }

    abstract class ParkingMeter
    {
        protected double parkingRate;

        public ParkingMeter(double parkingRate)
        {
            this.parkingRate = parkingRate;
        }

        double insertCoins(double minutes)
        {
            return parkingRate * minutes;
        }
    }

    class ParkWeekday: ParkingMeter
    {
        public ParkWeekday(double parkingRate) : base(parkingRate)
        {
            this.parkingRate = parkingRate;
        }
    }

    class ParkWeekend : ParkingMeter
    {
        public ParkWeekend(double parkingRate) : base(parkingRate)
        {
            this.parkingRate = 0.7 * parkingRate;
        }
    }
}
