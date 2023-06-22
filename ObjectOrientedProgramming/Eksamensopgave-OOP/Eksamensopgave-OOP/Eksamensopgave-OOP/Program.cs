using Eksamensopgave_OOP;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace Eksamensopgave_OOP
{
    class Program
    {
        static void Main(string[] args)
        {
            StregSystem system = new();
            StregSystemCLI ui = new(system);

            system.Initialize();
            ui.Start();
        }
    }
}
