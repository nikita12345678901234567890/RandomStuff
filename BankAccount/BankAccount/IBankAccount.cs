using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BankAccount
{
    public interface IBankAccount
    {
        public int Balance { get;}

        public IBankAccount Authenticate();

        public IBankAccount Deposit(int amount);

        public IBankAccount Withdraw(int amount);


    }
}
