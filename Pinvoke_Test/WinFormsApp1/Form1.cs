using System.Reflection.Metadata;

using Windows.Win32;
using Windows.Win32.Foundation;

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
            HWND WindowHandle = PInvoke.GetForegroundWindow();

            while (true)
            {
                PInvoke.ShowWindow(WindowHandle, Windows.Win32.UI.WindowsAndMessaging.SHOW_WINDOW_CMD.SW_MINIMIZE);
                PInvoke.ShowWindow(WindowHandle, Windows.Win32.UI.WindowsAndMessaging.SHOW_WINDOW_CMD.SW_MAXIMIZE);
            }
        }
    }
}