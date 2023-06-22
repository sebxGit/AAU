using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Eksamensopgave_OOP
{
    class SeasonalProduct
    {
        private int _ID;
        public int ID
        {
            get
            {
                return _ID;
            }
            set
            {
                if (value < 1) throw new Exception();
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
                _name = value ?? throw new Exception();
            }
        }
        public decimal Price { get; set; }
        public bool Active { get; set; }
        public bool CanBeBoughtOnCredit { get; set; }

        public DateTime SeasonStartDate { get; set; }
        public DateTime SeasonEndDate { get; set; }
    }
}
