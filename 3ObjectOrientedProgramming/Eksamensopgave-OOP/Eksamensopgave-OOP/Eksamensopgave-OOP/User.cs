using Eksamensopgave_OOP;
using System;
using System.Globalization;
using System.Linq;


namespace Eksamensopgave_OOP
{
    
    class User
    {
        public int ID { get; set; }
        public delegate void UserBalanceNotification(User user, decimal balance);
        private string _firstname, _lastname, _username, _email;
        private decimal _balance;
        private int _notifications;


        public string Firstname
        {
            get { return _firstname; }
            set { _firstname = value ?? throw new ArgumentOutOfRangeException(); }
        }

        public string Lastname
        {
            get { return _lastname; }
            set { _lastname = value ?? throw new ArgumentOutOfRangeException(); }
        }

        public string Username
        {
            get { return _username; }
            set
            {
                foreach (Char c in value)
                {
                    if(!Char.IsLower(c) && !Char.IsNumber(c) && !c.Equals('_')) throw new ArgumentOutOfRangeException();
                }
                _username = value;
            }
        }

        public string Email
        {
            get { return _email; }
            set
            {
                string LocalPart = value.Split('@')[0];
                string Domain = value.Split('@')[1];
                bool hasDot = false;

                foreach (Char c in LocalPart)
                {
                    if (!Char.IsLetterOrDigit(c) && !"._-".Contains(c)) throw new Exception();
                }

                foreach (Char c in Domain)
                {
                    if (!Char.IsLetterOrDigit(c) && !".-".Contains(c)) throw new Exception();
                    if (c == '.') hasDot = true;
                }

                if (!hasDot) throw new Exception();
                if ("_.".Contains(Domain.First()) || "_.".Contains(Domain.Last()) ) throw new Exception();

                _email = value;
            }
        }

        public decimal Balance
        {
            get
            {
                return _balance;
            }
            set 
            {
                if ((Balance + value) < 50)
                {
                    UserBalanceNotification notify = SendNotification;
                    notify(this, _balance);
                    _notifications++;
                }
                _balance = value;
            }
        }
        
        public void SendNotification(User u, decimal balance)
        {
            if(_notifications == 0)
                Console.WriteLine($"Your balance {this._firstname} is getting rather low. Consider inserting more cash!");
            if(_notifications >= 1)
                Console.WriteLine($"Your balance {this._firstname} is too low. Please insert more cash.");
        }

        public override string ToString()
        {
            return $"{Firstname}, {Lastname} ({Email})";
        }

        public override bool Equals(object obj)
        {
            if (obj is User user)
            {
                return _firstname == user._firstname & _lastname == user._lastname & _email == user._email;
            }
            return false;
        }

        public override int GetHashCode()
        {
            return ID;
        }

        public int CompareTo(User u)
        {
            return ID.CompareTo(u.ID);
        }

        public User(int id, string firstname, string lastname, string username, decimal balance, string email)
        {
            ID = id;
            Firstname = firstname;
            Lastname = lastname;
            Username = username;
            Balance = balance;
            Email = email;
        }
    }


}
