using System.Drawing;
using System.Runtime.CompilerServices;

namespace WindowTest
{
    public partial class Form1 : Form
    {
        Image image;
        Rectangle view;
        Graphics gfx;
        HashSet<Keys> pressed = new HashSet<Keys>();
        public Form1()
        {
            InitializeComponent();
            image = Image.FromFile(@"\\GMRDC1\\Folder Redirection\Nikita.Ulianov\Desktop\Stann\whirlpool.jpg");
            view = pictureBox1.Bounds;
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            gfx = Graphics.FromImage(image);
            //gfx.Clear(Color.CornflowerBlue);

            gfx.DrawImage(image, pictureBox1.Bounds, view, GraphicsUnit.Pixel);

            pictureBox1.Image = image;
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            pressed.Add(e.KeyCode);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            gfx = Graphics.FromImage(image);
            //gfx.Clear(Color.CornflowerBlue);

            if (pressed.Contains(Keys.Left))
            {
                view.X -= 10;
                Location = new Point(Location.X - 10, Location.Y);
            }
            if (pressed.Contains(Keys.Right))
            {
                view.X += 10;
                Location = new Point(Location.X + 10, Location.Y);
            }
            if (pressed.Contains(Keys.Up))
            {
                view.Y -= 10;
                Location = new Point(Location.X, Location.Y - 10);
            }
            if (pressed.Contains(Keys.Down))
            {
                view.Y += 10;
                Location = new Point(Location.X, Location.Y + 10);
            }

            gfx.DrawImage(image, pictureBox1.Bounds, view, GraphicsUnit.Pixel);

            pictureBox1.Image = image;
        }
    }
}