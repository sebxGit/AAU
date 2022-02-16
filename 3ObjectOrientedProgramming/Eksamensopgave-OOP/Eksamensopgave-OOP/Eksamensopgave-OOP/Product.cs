using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Eksamensopgave_OOP
{
    class Product
    {
        private int _ID;
        public int ID { 
            get 
            {
                return _ID;
            } 
            set 
            {
                if (value < 1) throw new ArgumentOutOfRangeException();
                _ID = value;
            } 
        }

        private string _name;
        public string Name
        {
            get
            {
                return _name;
            }
            set
            {
                _name = value ?? throw new ArgumentNullException();
            }
        }
        public decimal Price { get; set; }
        public bool Active { get; set; }
        public bool CanBeBoughtOnCredit { get; set; }

        public override string ToString()
        {
            return $"{ID}, {Name}, {Price}";
        }

        public Product(int id, string name, decimal price, bool active)
        {
            ID = id;
            Name = name;
            Price = price;
            Active = active;
        }
    }
}
