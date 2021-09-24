using System;
using System.Collections.Generic;
using System.Linq;

namespace sample
{
    class Program
    {


        static void Main(string[] args)
        {
            int chosenPersonID = 0;
            Person p = new();
            p.Fornavn = "Sebastian";
            p.Efternavn = "Truong";
            p.Far = "Day";
            p.Mor = "Thao";
            p.Bedstefar = "BEDSFAR";
            p.Bedstemor = "BEDSMOR";
            p.Alder = 20;
            p.PersonID = chosenPersonID++;
            
        }
    }

    class Person
    {
        private string _far;
        private string _mor;
        private string _bedstefar;
        private string _bedstemor;
        public string Fornavn;
        public string Efternavn;
        public int Alder;
        public int _personID;

        public Person(string _far, string _mor)
        {
            this._far = _far;
            this._mor = _mor;
        }

        public int PersonID
        {
            get { return _personID; }
            set { _personID = value; }
        }

        public string Far
        {
            get { return _far; }
            set
            {
                if (value.Length == 0 || value.Length > 15)
                {
                    throw new Exception();
                }
                _far = value;
            }
        }

        public string Mor
        {
            get { return _mor; }
            set
            {
                if (value.Length == 0 || value.Length > 15)
                {
                    throw new Exception();
                }
                _mor = value;
            }
        }

        public string Bedstefar
        {
            get { return _bedstefar; }
            set
            {
                if (value.Length == 0 || value.Length > 15)
                {
                    throw new Exception();
                }
                _bedstefar = value;
            }
        }

        public string Bedstemor
        {
            get { return _bedstemor; }
            set
            {
                if (value.Length == 0 || value.Length > 15)
                {
                    throw new Exception();
                }
                _bedstemor = value;
            }
        }


    }
    
    class PersonPrinter
    {
        void printPerson(Person p)
        {
            Console.WriteLine($"{p.Fornavn} {p.Efternavn}, {p.Alder}");
        }

        void printFamTree(Person p)
        {
            Console.WriteLine($"far: {p.Far}\nmor: {p.Mor}\nBedstefar: {p.Bedstefar}\nBedstemor: {p.Bedstemor}");
        }
    }
}
