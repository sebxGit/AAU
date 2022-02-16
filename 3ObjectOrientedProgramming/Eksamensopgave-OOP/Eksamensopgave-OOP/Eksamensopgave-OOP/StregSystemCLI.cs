using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Eksamensopgave_OOP
{
    class StregSystemCLI : IStregsystemUI
    {
        public delegate void StregsystemEvent(User u, string command);
        StregSystem system;

        private Dictionary<string, Action> _adminCommands = new();

        public void Close()
        {
            Console.WriteLine("You exited the program. Bye!");
        }

        public void DisplayAdminCommandNotFoundMessage(string adminCommand)
        {
            Console.WriteLine($"The admin command {adminCommand} was not found!");
        }

        public void DisplayGeneralError(string errorString)
        {
            Console.WriteLine(errorString);
        }

        public void DisplayInsufficientCash(User user, Product product)
        {
            Console.WriteLine($"Your balance {user.Balance} was too low on funds! Product price: {product.Price}");
        }

        public void DisplayProductNotFound(string product)
        {
            Console.WriteLine($"The product: {product} was not found!");
        }

        public void DisplayTooManyArgumentsError(string command)
        {
            Console.WriteLine(
                "You wrote too many arguments. Please try again!" +
                $"\nYour Command: {command}\n");
        }

        public void DisplayUserBuysProduct(BuyTransaction transaction)
        {
            Console.WriteLine($"You bought the product: {transaction.Product.Name}");
        }

        public void DisplayUserBuysProduct(int count, BuyTransaction transaction)
        {
            bool isVowel = "aeiouAEIOU".IndexOf(transaction.Product.Name[0]) != -1;
            Console.WriteLine($"User bought a{((isVowel) ? 'n' : "")} {transaction.Product.Name} {count} time{((count > 1) ? 's' : "")}");
        }

        public void DisplayUserInfo(User user)
        {
            Console.WriteLine($"{user.Username}: {user.Balance}kr, {user.Firstname} {user.Lastname}, email: {user.Email}");
        }

        public void DisplayUserNotFound(string username)
        {
            Console.WriteLine($"{username} was not found!");
        }

        public void Start()
        {
            string Input;
            
            Console.WriteLine("Welcome to the Stregsystem :)");
            foreach(var p in system.Products.Where(o => o.Active == true))
            {
                Console.WriteLine($"[{p.ID}] {p.Name}, {p.Price}");
            }
            while (true)
            {
                Console.Write("\nQuickbuy: ");
                Input = Console.ReadLine();
                var ParseCommand = Input.Split(" ");
                switch (ParseCommand[0].ToLower())
                {
                    case ":q": case ":quit":
                        QuitAction();
                        break;
                    case ":activate":
                        ActivateAction(Int32.Parse(ParseCommand[1]));
                        break;
                    case ":deactivate":
                        DeactivateAction(Int32.Parse(ParseCommand[1]));
                        break;
                    case ":crediton":
                        CreditonAction(Int32.Parse(ParseCommand[1]));
                        break;
                    case ":creditoff":
                        CreditoffAction(Int32.Parse(ParseCommand[1]));
                        break;
                    case ":addcredits":
                        AddcreditsAction(username: ParseCommand[1], amount: Int32.Parse(ParseCommand[2]));
                        break;
                    default:
                        try { User myUser = system.GetUserByUsername(ParseCommand[0]); }
                        catch { }

                        if (ParseCommand.Length == 1)
                        {
                            CommandSimpleUsername(system, username: ParseCommand[0]);
                            break;
                        }
                        if (ParseCommand.Length == 2)
                        {
                            BuyProduct(system, username: ParseCommand[0], productID: ParseCommand[1]);
                            break;
                        }
                        if (ParseCommand.Length == 3)
                        {
                            BuyProducts(system, username: ParseCommand[0], amountStr: ParseCommand[1], productID: ParseCommand[2]);
                            break;
                        }
                        
                        DisplayTooManyArgumentsError(Input);
                        break;
                }
            }
        }

        void CommandSimpleUsername(StregSystem s, string username)
        {
            User u = s.Users.Where(o => o.Username == username).First();
            if (u == null) {Console.WriteLine("The user does not exist!"); return;}

            Console.WriteLine($"{u.Username}, {u.Firstname} {u.Lastname} [{u.Balance}kr]");

            List<Transaction> Transactions = s.GetTransactions(u, 10);
            foreach (var t in Transactions) 
                if (t != null) 
                    Console.WriteLine($"[Transaction] ({t.Date}): {t.User.Username}, {t.Amount}kr");

            if (u.Balance < 50) DisplayGeneralError("Your balance is under 50kr!");
        }

        void BuyProduct(StregSystem s, string username, string productID)
        {
            int id = -1;
            try { id = Int32.Parse(productID); }
            catch { Console.WriteLine($"The product ID: '{productID}' does not exist!"); return; }

            User u = s.Users.Where(o => o.Username == username).First();
            Product p = s.Products.Where(o => o.ID == id).First();
            if (u == null) { DisplayUserNotFound(username); return; }
            if (p == null) { DisplayProductNotFound(productID); return; }
            if (u.Balance < p.Price) { DisplayInsufficientCash(u, p); return; }

            system.BuyProduct(u, p);
            Console.WriteLine($"You bought the product {p.Name}. Your current balance: {u.Balance}");
        }

        void BuyProducts(StregSystem s, string username, string amountStr, string productID)
        {
            int amount = 0;
            try { amount = Int32.Parse(amountStr); }
            catch { Console.WriteLine("You wrote an invalid amount of products!"); return; }
            for(int i = 0; i < amount; i++)
            {
                BuyProduct(s, username, productID); 
            }
        }

        public StregSystemCLI(StregSystem s)
        {
            system = s;
            //_adminCommands.Add(":activate", () => system.Products.Where(o => o.ID == InspectedID).First().Active = true);
        }

        void QuitAction()
        {
            Close();
            Environment.Exit(1);
        }
        void ActivateAction(int ID)
        {
            system.Products.Where(o => o.ID == ID).First().Active = true;
            Console.WriteLine($"You activated product {ID}.");
        }
        void DeactivateAction(int ID)
        {
            system.Products.Where(o => o.ID == ID).First().Active = false;
            Console.WriteLine($"You deactivated product {ID}.");
        }
        void CreditonAction(int ID)
        {
            system.Products.Where(o => o.ID == ID).First().CanBeBoughtOnCredit = true;
            Console.WriteLine($"The product price can be bought on credit! ID: {ID}.");
        }
        void CreditoffAction(int ID)
        {
            system.Products.Where(o => o.ID == ID).First().CanBeBoughtOnCredit = false;
            Console.WriteLine($"The product price can't be bought on credit! ID: {ID}.");
        }
        void AddcreditsAction(string username, decimal amount)
        {
            system.Users.Where(o => o.Username == username).First().Balance += amount;
            Console.WriteLine($"{username} was appended {amount}kr to their account!");
        }
    }
}
