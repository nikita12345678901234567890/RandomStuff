using System;
using System.Drawing;

using Windows.Win32;
using Windows.Win32.Foundation;
using Windows.Win32.UI.WindowsAndMessaging;

namespace Pinvoke_Test
{
    internal unsafe class Program
    {
        static void Main(string[] args)
        {
            MessageBoxFunc("Hi");
        }

        public static void MessageBoxFunc(string message)
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
                PInvoke.MoveWindow(WindowHandle, position.X, position.Y, 500, 500, false);

                PInvoke.GetWindowInfo(WindowHandle, ref windowInfo);
                if (windowInfo.rcWindow.top <= desktopInfo.rcWindow.top || windowInfo.rcWindow.bottom >= desktopInfo.rcWindow.bottom) speed.Y *= -1;

                if (windowInfo.rcWindow.left <= desktopInfo.rcWindow.left || windowInfo.rcWindow.right >= desktopInfo.rcWindow.right) speed.X *= -1;

                position.X += speed.X;
                position.Y += speed.Y;

                Thread.Sleep(1000);
            }
        }
    }
}