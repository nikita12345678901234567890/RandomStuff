using System.Reflection.Metadata;
using System.Security.Cryptography;

using Windows.Win32;
using Windows.Win32.Foundation;
using Windows.Win32.UI.WindowsAndMessaging;

namespace WinFormsApp1
{
    public unsafe partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            WindowBounce(this);
        }

        public static void WindowBounce(Form1 form)
        {
            Point position = new Point(5, 5);
            Point speed = new Point(10, 10);

            HWND desktopWindow = PInvoke.GetDesktopWindow();
            WINDOWINFO desktopInfo = default;
            PInvoke.GetWindowInfo(desktopWindow, ref desktopInfo);

            HWND WindowHandle = PInvoke.GetForegroundWindow();
            WINDOWINFO windowInfo = default;
            while (true)
            {
                form.BringToFront();
                PInvoke.MoveWindow(WindowHandle, position.X, position.Y, form.Width, form.Height, false);
                windowInfo.cbSize = (uint)sizeof(WINDOWINFO);
                PInvoke.GetWindowInfo(WindowHandle, ref windowInfo);
                if (windowInfo.rcWindow.top <= desktopInfo.rcWindow.top || windowInfo.rcWindow.bottom >= desktopInfo.rcWindow.bottom) speed.Y *= -1;

                if (windowInfo.rcWindow.left <= desktopInfo.rcWindow.left || windowInfo.rcWindow.right >= desktopInfo.rcWindow.right) speed.X *= -1;

                position.X += speed.X;
                position.Y += speed.Y;

                Thread.Sleep(17);
            }
        }

        private void Form1_Shown(object sender, EventArgs e)
        {
            BackgroundImageLayout = ImageLayout.Zoom;
            Focus();
            WindowBounce(this);

        }
    }
}