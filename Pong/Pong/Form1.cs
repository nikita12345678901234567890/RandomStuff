using Microsoft.VisualBasic.Devices;

using System.Numerics;

namespace Pong
{
    public partial class Form1 : Form
    {
        Form LPaddle = new Form();
        Form RPaddle = new Form();

        Point speed = new Point(10, 10);

        bool? RDirection = null;
        
        public Form1()
        {
            InitializeComponent();
            LPaddle.StartPosition = FormStartPosition.Manual;
            LPaddle.Size = new System.Drawing.Size(20, 400);
            LPaddle.Location = new System.Drawing.Point(5, Screen.PrimaryScreen.Bounds.Height / 3);
            LPaddle.Visible = true;

            RPaddle.StartPosition = FormStartPosition.Manual;
            RPaddle.Size = new System.Drawing.Size(20, 400);
            RPaddle.Location = new System.Drawing.Point(Screen.PrimaryScreen.Bounds.Width - (RPaddle.Size.Width + 5), Screen.PrimaryScreen.Bounds.Height / 3);
            RPaddle.Visible = true;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Location = new Point(Location.X + speed.X, Location.Y + speed.Y);

            if (Bottom >= Screen.PrimaryScreen.Bounds.Height || Top <= 0) speed.Y *= -1;

            if (this.DesktopBounds.IntersectsWith(LPaddle.DesktopBounds)) speed.X = Math.Abs(speed.X);
            if (this.DesktopBounds.IntersectsWith(RPaddle.DesktopBounds)) speed.X = -Math.Abs(speed.X);

            if (RDirection == true && RPaddle.Top > 20) RPaddle.Location = new Point(RPaddle.Location.X, RPaddle.Location.Y - 20);
            else if (RDirection == false && RPaddle.Bottom < Screen.PrimaryScreen.Bounds.Bottom - 20) RPaddle.Location = new Point(RPaddle.Location.X, RPaddle.Location.Y + 20);
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.Up:
                    RDirection = true;
                    break;

                case Keys.Down:
                    RDirection = false;
                    break;
            }
        }

        private void Form1_KeyUp(object sender, KeyEventArgs e)
        {
            RDirection = null;
        }
    }
}