using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Eksamensopgave_OOP
{
    class Transaction
    {
        public int ID { get; set; }
        private User _user;
        public User User { get 
            {
                return _user;
            }
            set 
            {
                _user = value ?? throw new Exception();
            }
        }
        public DateTime Date { get; set; }
        public decimal Amount { get; set; }

        public override string ToString()
        {
            return $"{ID}, {User.ToString()}, {Amount}, {Date}";
        }

        public virtual void Execute() 
        {
            if (User.Balance + Amount < 0) throw new InsufficientCreditsException();
            TextWriter textWriter = new StreamWriter(@"C:\Users\minhs\Documents\GitHub\Eksamensopgave-OOP\Eksamensopgave-OOP\Eksamensopgave-OOP\data\log.txt", true);
            textWriter.WriteLine($"[Transaction] {User.Firstname} {User.Lastname} ({Date}): {Amount}kr");
            textWriter.Flush();
            textWriter.Close();
            User.Balance += Amount;
            
        }

        public Transaction(User u, decimal amount = 0)
        {
            this.User = u;
            Date = DateTime.Now;
            Amount = amount;
        }
    }
}
