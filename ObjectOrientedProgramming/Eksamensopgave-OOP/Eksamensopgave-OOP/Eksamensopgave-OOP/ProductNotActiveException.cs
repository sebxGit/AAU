using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Eksamensopgave_OOP
{
    class ProductNotActiveException: Exception
    {
        public ProductNotActiveException()
        {

        }
        public ProductNotActiveException(string message) : base(message)
        {

        }
    }
}
