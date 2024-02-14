namespace BankAccount
{
    internal class Program
    {
        static void Main(string[] args)
        {
            IBankAccount account = new UnauthedAccount();

            account = account.Authenticate();

            account = account.Deposit(5);
            account = account.Withdraw(3);
            Console.WriteLine(account.Balance);
            account = account.Withdraw(5);

            account = account.Deposit(10);
            account = account.Withdraw(2);
            Console.WriteLine(account.Balance);
        }
    }
}