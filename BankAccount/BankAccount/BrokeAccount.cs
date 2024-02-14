using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BankAccount
{
    public class BrokeAccount : IBankAccount
    {
        public int Balance { get; private set; }

        public IBankAccount Authenticate()
        {
            return this;
        }

        public BrokeAccount(int balance)
        {
            Balance = balance;
        }

        public IBankAccount Deposit(int amount)
        {
            Balance += amount;
            if (Balance >= 0) return new Account(Balance);
            return this;
        }

        public IBankAccount Withdraw(int amount)
        {
            throw new Exception("You broke");
        }
    }
}
