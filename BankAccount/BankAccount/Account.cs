using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BankAccount
{
    public class Account : IBankAccount
    {
        public int Balance { get; private set; }

        public Account(int balance)
        {
            Balance = balance;
        }

        public IBankAccount Authenticate()
        {
            return this;
        }

        public IBankAccount Deposit(int amount)
        {
            Balance += amount;
            return this;
        }

        public IBankAccount Withdraw(int amount)
        {
            Balance -= amount;

            if(Balance < 0) return new BrokeAccount(Balance);

            return this;
        }
    }
}
