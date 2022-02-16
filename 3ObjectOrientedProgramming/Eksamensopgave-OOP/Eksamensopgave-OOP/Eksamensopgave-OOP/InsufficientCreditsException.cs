using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Eksamensopgave_OOP
{
    class InsufficientCreditsException : Exception
    {
        public InsufficientCreditsException()
        {

        }
        public InsufficientCreditsException(string message) : base(message)
        {

        }
    }
}
