namespace StringForLoop
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string yeet = "Hello";

            for (string i = yeet; i.Length > 0; i = i.Remove(i.Length - 1))
            {
                Console.Write(i[^1]);
            }
        }
    }
}