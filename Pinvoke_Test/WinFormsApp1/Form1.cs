using System.Reflection.Metadata;

namespace WinFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            MessageBoxFunc("Hi");
        }

        public static void MessageBoxFunc(string message)
        {
            MessageBox.Show(message);
        }
    }
}