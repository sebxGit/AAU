using System;

namespace postnr
{
    class Program
    {
        static void Main(string[] args)
        {
            By Aalborg = new(bynavn: "Aalborg", postnr: new(9200));
            Aalborg.ShowInfo();
        }
    }

    class By
    {
        Postnummer postnummer;
        private string _name = "";
        public string Name
        {
            get
            {
                return _name;
            }
            set
            {
                if (value.Length <= 0)                  throw new ArgumentOutOfRangeException("Bynavne kan ikke være under 0");
                if (value.GetType() != _name.GetType()) throw new Exception("Et ugyldigt format var indtastet for byen");
                else                                    _name = value;
            }
        }

        public By(string bynavn, Postnummer postnr)
        {
        this.Name = bynavn;
        postnummer = postnr;
        }

        public void ShowInfo()
        {
            Console.WriteLine($"bynavn: {_name}, postnr: {postnummer.Nummer}");
        }
    }

    class Postnummer
    {
        private int _nummer;
        public int Nummer {
            get
            {
                return _nummer;
            }
            set
            {
                if (value <= 0)                         throw new ArgumentOutOfRangeException("Postnumre kan ikke være under 0");
                else                                    _nummer = value;
            }
        }

        int Get() 
        {
            return _nummer;
        }

        public Postnummer(int Nummer)
        {
            this.Nummer = Nummer;
        }
    }
}
