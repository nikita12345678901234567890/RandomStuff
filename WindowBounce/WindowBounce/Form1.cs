namespace WindowBounce
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        Point speed = new Point(10, 10);
        private void timer1_Tick(object sender, EventArgs e)
        {
            Location = new Point(Location.X + speed.X, Location.Y + speed.Y);
            pictureBox1.Location = new Point((int)((float)Location.X * ((float)Location.X / 1920)), (int)((float)Location.Y * ((float)Location.Y / 1080)));
            

            if (Location.X <= 0 || Location.X + Size.Width >= 1920)
            {
                speed.X *= -1;
            }
            if (Location.Y <= 0 || Location.Y + Size.Height >= 1080)
            {
                speed.Y *= -1;
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}