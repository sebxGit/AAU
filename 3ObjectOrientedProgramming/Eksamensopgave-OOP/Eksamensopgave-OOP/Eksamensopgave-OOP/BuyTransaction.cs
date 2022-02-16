using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Eksamensopgave_OOP
{
    class BuyTransaction : Transaction
    {
        public BuyTransaction(User u, Product p) : base(u)
        {
            Product = p;
            Amount = p.Price;
        }

        public Product Product { get; set; }
        public override string ToString()
        {
            return $"[{ID} {Date}] Price: {Product.Price}, Balance, {User.Balance}, User: {User.Username}";
        }

        public override void Execute()
        {
            if (User.Balance - Product.Price < 0) throw new InsufficientCreditsException();
            if (Product.Active == false) throw new ProductNotActiveException();

            TextWriter textWriter = new StreamWriter(@"C:\Users\minhs\Documents\GitHub\Eksamensopgave-OOP\Eksamensopgave-OOP\Eksamensopgave-OOP\data\log.txt", true);
            textWriter.WriteLine($"[BuyTransaction] {User.Firstname} {User.Lastname} ({Date}): Product -{Product.Price}kr");
            textWriter.Flush();
            textWriter.Close();
            User.Balance -= Product.Price;
        }
    }
}
