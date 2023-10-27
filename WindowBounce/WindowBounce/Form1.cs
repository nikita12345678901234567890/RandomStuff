namespace WindowBounce
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        Point speed = new Point(5, 5);
        private void timer1_Tick(object sender, EventArgs e)
        {
            Location = new Point(Location.X + speed.X, Location.Y + speed.Y);
            pictureBox1.Location = new Point(pictureBox1.Location.X + ((Size.Width - (pictureBox1.Location.X + pictureBox1.Size.Width)) / ((Size.Width / pictureBox1.Width) * speed.X)), pictureBox1.Location.Y);

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