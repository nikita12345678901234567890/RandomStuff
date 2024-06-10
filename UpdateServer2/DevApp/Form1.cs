namespace DevApp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            V1();
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
