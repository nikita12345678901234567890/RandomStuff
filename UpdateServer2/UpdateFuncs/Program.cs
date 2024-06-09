namespace UpdateFuncs
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello, World!");
        }

        public void V1()
        {
            TextBox textBox = new TextBox();
            textBox.Text = "Holy Shit it works!!!!";
            textBox.Location = new System.Drawing.Point(50, 50);
            Controls.Add(textBox);
        }
    }
}
