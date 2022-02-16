using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Eksamensopgave_OOP
{
    class ProductNotInListException : Exception
    {
        public ProductNotInListException()
        {

        }
        public ProductNotInListException(string message) : base(message)
        {

        }
    }
}
