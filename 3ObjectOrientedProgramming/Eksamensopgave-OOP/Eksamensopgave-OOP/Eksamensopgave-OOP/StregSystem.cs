using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static Eksamensopgave_OOP.User;

namespace Eksamensopgave_OOP
{
    class StregSystem : IStregsystem
    {
        public List<User> Users = new();
        public List<Product> Products = new();
        public List<Transaction> Transactions = new();

        public void BuyProduct(User u, Product p)
        {
            try
            {
                BuyTransaction t = new(u, p);
                t.Execute();
                Transactions.Add(t);
            }
            catch (Exception ex)
            {
                if(ex is InsufficientCreditsException || ex is ProductNotActiveException)
                    Console.WriteLine(ex.Message);
            }
        }

        public void AddCreditsToAccount(User u, decimal amount)
        {
            InsertCashTransaction insertCash = new InsertCashTransaction(u, amount);
            insertCash.Execute();
            Transactions.Add(insertCash);
        }

        public BuyTransaction ExecuteTransaction(User u, Product p)
        {
            try {
                BuyTransaction buyTransaction = new(u, p);
                buyTransaction.Execute();
                Transactions.Add(buyTransaction);
                return buyTransaction;
            }
            catch (Exception ex){
                Console.WriteLine(ex);
                return null; 
            }
        }

        public Product GetProductByID(int ID) 
        {
            Product p = Products?.Where(o => o.ID == ID)?.FirstOrDefault();
            try 
            { 
                if (p == null) throw new ProductNotInListException("The product was not in the list!");
                return p;
            }
            catch (ProductNotInListException ex)
            {
                Console.WriteLine(ex.Message);
                return null;
            }
        }

        public List<User> GetUsers(Func<User, bool> predicate)
        {
            List<User> uList = new();
            foreach (User u in Users)
            {
                if (predicate(u)) uList.Add(u);
            }
            return uList;
        }

        public User GetUserByUsername(string username)
        {
            User u = Users?.Where(o => o.Username == username)?.FirstOrDefault();
            try
            {
                if (u == null) throw new InvalidUsernameException();
                return u;
            }
            catch(InvalidUsernameException ex)
            {
                Console.WriteLine(ex.Message);
                return null;
            }
        }

        public List<Transaction> GetTransactions(User user, int count)
        {
            int ct = 0;
            return Transactions?.OrderBy(t => t.Date)?.Where(t => t.User == user && ct++ < count)?.ToList();
        }

        public List<Product> ActiveProducts()
        {
            return Products?.Where(p => p.Active == true)?.ToList();
        }
        public void Initialize()
        {
            //initializes products
            using (var reader = new StreamReader(@"C:\Users\minhs\Documents\GitHub\Eksamensopgave-OOP\Eksamensopgave-OOP\Eksamensopgave-OOP\data\products.csv"))
            {
                while (!reader.EndOfStream)
                {
                    var line = reader.ReadLine();
                    var val = line.Split(";");
                    if (val.First() == "id") continue;
                    while (val[1].Contains("<"))
                    {
                        int startIndex = val[1].IndexOf("<");
                        int length = val[1].IndexOf(">") - startIndex + 1;
                        val[1] = val[1].Replace(val[1].Substring(startIndex, length), "");
                    }

                    Products.Add(new Product(id: Int32.Parse(val[0]), name: val[1], price: decimal.Parse(val[2]), active: !val[3].Equals("0")));
                }
            }

            //initializes users
            using (var reader = new StreamReader(@"C:\Users\minhs\Documents\GitHub\Eksamensopgave-OOP\Eksamensopgave-OOP\Eksamensopgave-OOP\data\users.csv"))
            {
                while (!reader.EndOfStream)
                {
                    var line = reader.ReadLine();
                    var val = line.Split(",");
                    if (val.First() == "id") continue;
                    Users.Add(new User(id: Int32.Parse(val[0]), firstname: val[1], lastname: val[2], username: val[3], balance: decimal.Parse(val[4]), email: val[5]));
                }
            }
        }
    }
}
