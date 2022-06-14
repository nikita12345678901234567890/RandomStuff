using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FizzBuzz
{
    class Program
    {
        static void Main(string[] args)
        {
            string[] Fizz = {"Fizz"};
            string[] Buzz = { "Buzz" };
            string[] FizzBuzz = { "FizzBuzz" };

            for (int i = 1; i < 100; i++)
            {
                string output = i.ToString();

                int mod3 = i % 3;

                try
                {
                    output = Fizz[mod3];
                }
                catch (IndexOutOfRangeException)
                { 

                }


                int mod5 = i % 5;

                try
                {
                    output = Buzz[mod5];
                }
                catch (IndexOutOfRangeException)
                { 

                }


                int mod15 = i % 15;

                try
                {
                    output = FizzBuzz[mod15];
                }
                catch (IndexOutOfRangeException)
                { 

                }

                Console.WriteLine(output);
            }
        }
    }
}
