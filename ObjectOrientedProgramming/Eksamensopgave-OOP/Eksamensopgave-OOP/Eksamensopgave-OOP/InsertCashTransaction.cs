using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Eksamensopgave_OOP
{
    class InsertCashTransaction : Transaction
    {
        public InsertCashTransaction(User u, decimal amount) : base(u, amount)
        {
        }
        public override string ToString()
        {
            return $"[{ID} {Date}] INSERTION Amount: {Amount}, New balance, {User.Balance}, User: {User.Username}";
        }
        public override void Execute() 
        {
            TextWriter textWriter = new StreamWriter(@"C:\Users\minhs\Documents\GitHub\Eksamensopgave-OOP\Eksamensopgave-OOP\Eksamensopgave-OOP\data\log.txt", true);
            textWriter.WriteLine($"[InsertCashTransaction] {User.Firstname} {User.Lastname} ({Date}): +{Amount}kr");
            textWriter.Flush();
            textWriter.Close();
            User.Balance += Amount;
        }
    }
}
