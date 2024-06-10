using Microsoft.Win32;

namespace UpdateApp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void UpdateTimer_Tick(object sender, EventArgs e)
        {

        }

        private void Update_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            var result = ofd.ShowDialog();
            if(result == DialogResult.OK)
            {
                var newDLL = ofd.FileName;

                File.Copy(newDLL, @"UpdateAppV1.dll");

                PInvoke
            }
        }
    }
}