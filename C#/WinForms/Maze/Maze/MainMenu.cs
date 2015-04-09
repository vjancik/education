using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Maze
{
    public partial class MainMenu : Form
    {
        public MainMenu()
        {
            InitializeComponent();
        }

        private void mouseMode_Click(object sender, EventArgs e)
        {
            MazeWindow gameWindow = new MazeWindow(MazeWindow.Mode.Mouse);
            //gameWindow.Left = (int)Screen.PrimaryScreen.Bounds.Width/2 - gameWindow.Width/2;
            //gameWindow.Top = (int)Screen.PrimaryScreen.Bounds.Height/2 - gameWindow.Height/2;
            gameWindow.Show();
            this.Hide();
        }

        private void keyboardMode_Click(object sender, EventArgs e)
        {
            MazeWindow gameWindow = new MazeWindow(MazeWindow.Mode.Keyboard);
            gameWindow.Show();
            gameWindow.Left = (int)Screen.PrimaryScreen.Bounds.Width / 2 - gameWindow.Width / 2;
            gameWindow.Top = (int)Screen.PrimaryScreen.Bounds.Height / 2 - gameWindow.Height / 2;
            this.Hide();
        }
    }
}
