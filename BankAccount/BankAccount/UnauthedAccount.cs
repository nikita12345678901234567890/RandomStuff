using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BankAccount
{
    public class UnauthedAccount : IBankAccount
    {
        public int Balance => throw new Exception("Not Authed");

        public IBankAccount Authenticate()
        {
            return new Account(0);
        }

        public IBankAccount Deposit(int amount)
        {
            throw new Exception("Not Authed");
        }

        public IBankAccount Withdraw(int amount)
        {
            throw new Exception("Not Authed");
        }
    }
}
