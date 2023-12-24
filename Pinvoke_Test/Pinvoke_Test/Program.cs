using System;
using System.Runtime.InteropServices;

namespace Pinvoke_Test
{
    internal class Program
    {
        // Import the dll (containing the function we need) and define
        // the method corresponding to the native function.
        [DllImport("WinFormsApp1.dll")]
        public static extern void MessageBoxFunc(string message);

        static void Main(string[] args)
        {
            Console.WriteLine("Hello, World!");
            MessageBoxFunc("Hi");
        }
    }
}