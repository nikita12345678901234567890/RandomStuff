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

        Point buttonSpeed = new Point(4, 5);

        int sideStanSpeed = 8;

        public Form1()
        {
            InitializeComponent();
            LPaddle.StartPosition = FormStartPosition.Manual;
            LPaddle.Size = new System.Drawing.Size(20, 400);
            LPaddle.Location = new System.Drawing.Point(5, Screen.PrimaryScreen.Bounds.Height / 3);
            LPaddle.Visible = true;
            LPaddle.Controls.Add(LStan);
            LPaddle.Controls[0].Visible = true;
            LPaddle.Controls[0].Location = new Point(5, 5);

            RPaddle.StartPosition = FormStartPosition.Manual;
            RPaddle.Size = new System.Drawing.Size(20, 400);
            RPaddle.Location = new System.Drawing.Point(Screen.PrimaryScreen.Bounds.Width - (RPaddle.Size.Width + 5), Screen.PrimaryScreen.Bounds.Height / 3);
            RPaddle.Visible = true;
            RPaddle.Controls.Add(RStan);
            RPaddle.Controls[0].Visible = true;
            RPaddle.Controls[0].Location = new Point(5, 0);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (Bottom >= Screen.PrimaryScreen.Bounds.Height || Top <= 0) speed.Y *= -1;

            if (this.DesktopBounds.IntersectsWith(LPaddle.DesktopBounds))
            {
                speed.X = Math.Abs(speed.X);
                speed.Y += sideStanSpeed;
            }
            if (this.DesktopBounds.IntersectsWith(RPaddle.DesktopBounds))
            {
                speed.X = -Math.Abs(speed.X);
                speed.Y += sideStanSpeed;
            }

            if (RDirection == true && RPaddle.Top > 20) RPaddle.Location = new Point(RPaddle.Location.X, RPaddle.Location.Y - 20);
            else if (RDirection == false && RPaddle.Bottom < Screen.PrimaryScreen.Bounds.Bottom - 20) RPaddle.Location = new Point(RPaddle.Location.X, RPaddle.Location.Y + 20);

            Location = new Point(Location.X + speed.X, Location.Y + speed.Y);


            if (button.Right >= ClientSize.Width - buttonSpeed.X || button.Left <= 0) buttonSpeed.X *= -1;
            if (button.Bottom >= ClientSize.Height - buttonSpeed.Y || button.Top <= 0) buttonSpeed.Y *= -1;

            button.Location = new Point(button.Location.X + buttonSpeed.X, button.Location.Y + buttonSpeed.Y);


            if (LPaddle.Controls[0].Top <= 0 || LPaddle.Controls[0].Bottom >= LPaddle.ClientSize.Height) sideStanSpeed *= -1;
            LPaddle.Controls[0].Location = new Point(LPaddle.Controls[0].Location.X, LPaddle.Controls[0].Location.Y + sideStanSpeed);
            RPaddle.Controls[0].Location = LPaddle.Controls[0].Location;
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

        private void Form1_Click(object sender, EventArgs e)
        {
            
        }
    }
}