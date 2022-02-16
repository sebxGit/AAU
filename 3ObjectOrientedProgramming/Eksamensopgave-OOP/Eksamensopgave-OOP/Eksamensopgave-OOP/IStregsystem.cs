using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static Eksamensopgave_OOP.User;

namespace Eksamensopgave_OOP
{
    interface IStregsystem
    {
        void BuyProduct(User u, Product p);
        void AddCreditsToAccount(User u, decimal amount);

        BuyTransaction ExecuteTransaction(User u, Product p);
        Product GetProductByID(int ID);

        List<User> GetUsers(Func<User, bool> predicate);

        User GetUserByUsername(string username);
        List<Transaction> GetTransactions(User user, int count);

        List<Product> ActiveProducts();
        public void Initialize();
    }
}
