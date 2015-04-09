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
    public partial class MazeWindow : Form
    {
        public const int WIDTH = 27;
        public const int HEIGHT = 27;
        private int playerx = 1, playery = 1;
        private Label[,] maze;
        public enum Mode { Mouse, Keyboard };
        private Mode gameMode;
        public enum Dirs { North, South, West, East }
        private Point checkPoint;
        public MazeWindow(Mode mode)
        {
            InitializeComponent();
            this.FormBorderStyle = FormBorderStyle.None;
            gameMode = mode;
            maze = new Label[WIDTH, HEIGHT];
            MazeGenerator.GenerateMaze();
            createGrid();
            if (gameMode == Mode.Mouse)
            {
                Point startingPoint = maze[1, 1].Location;
                startingPoint.Offset(10, 10);
                Cursor.Position = PointToScreen(startingPoint);
                checkPoint = PointToScreen(startingPoint);
                timer1.Start();
            }
            else
            {
                this.Text = "The Maze Game - Keyboard Mode";
            }
            this.KeyUp += keyboardControl;
        }
        private void smartWalk(Dirs dir)
        {
            switch (dir)
            {
                case Dirs.North:
                    if (MazeGenerator.mazetiles[playerx, playery - 1] != 1)
                    {
                        do
                        {
                            if (maze[playerx, --playery].BackColor != Color.LightGreen && maze[playerx, playery].BackColor != Color.Orange)
                                maze[playerx, playery].BackColor = Color.LightGreen;
                            else
                                maze[playerx, playery].BackColor = Color.Orange;
                        } while (countPassages(playerx, playery) <= 2 && MazeGenerator.mazetiles[playerx, playery - 1] != 1);
                    }
                    break;
                case Dirs.South:
                    if (MazeGenerator.mazetiles[playerx, playery + 1] != 1)
                    {
                        do
                        {
                            if (maze[playerx, ++playery].BackColor != Color.LightGreen && maze[playerx, playery].BackColor != Color.Orange)
                                maze[playerx, playery].BackColor = Color.LightGreen;
                            else
                                maze[playerx, playery].BackColor = Color.Orange;
                        } while (countPassages(playerx, playery) <= 2 && MazeGenerator.mazetiles[playerx, playery + 1] != 1);
                    }
                    break;
                case Dirs.East:
                    if (MazeGenerator.mazetiles[playerx + 1, playery] != 1)
                    {
                        do
                        {
                            if (maze[++playerx, playery].BackColor != Color.LightGreen && maze[playerx, playery].BackColor != Color.Orange)
                                maze[playerx, playery].BackColor = Color.LightGreen;
                            else
                                maze[playerx, playery].BackColor = Color.Orange;
                        } while (countPassages(playerx, playery) <= 2 && MazeGenerator.mazetiles[playerx + 1, playery] != 1);
                    }
                    break;
                case Dirs.West:
                    if (MazeGenerator.mazetiles[playerx - 1, playery] != 1)
                    {
                        do
                        {
                            if (maze[--playerx, playery].BackColor != Color.LightGreen && maze[playerx, playery].BackColor != Color.Orange)
                                maze[playerx, playery].BackColor = Color.LightGreen;
                            else
                                maze[playerx, playery].BackColor = Color.Orange;
                        } while (countPassages(playerx, playery) <= 2 && MazeGenerator.mazetiles[playerx - 1, playery] != 1);
                    }
                    break;
            }
        }
        private int countPassages(int x, int y)
        {
            int passages = 0;
            if (MazeGenerator.mazetiles[playerx, playery - 1] == 0) ++passages;
            if (MazeGenerator.mazetiles[playerx, playery + 1] == 0) ++passages;
            if (MazeGenerator.mazetiles[playerx - 1, playery] == 0) ++passages;
            if (MazeGenerator.mazetiles[playerx + 1, playery] == 0) ++passages;
            return passages;
        }
        private void keyboardControl(object sender, KeyEventArgs e)
        {
            if (gameMode == Mode.Keyboard)
            {
                switch (e.KeyCode)
                {
                    case Keys.Up:
                        /*if (maze[playerx, playery - 1].BackColor == Color.LightGreen || maze[playerx, playery - 1].BackColor == Color.Orange)
                            maze[playerx, playery].BackColor = Color.Orange;*/
                        smartWalk(Dirs.North);
                        break;
                    case Keys.Down:
                        smartWalk(Dirs.South);
                        /* (maze[playerx, playery + 1].BackColor == Color.LightGreen || maze[playerx, playery - 1].BackColor == Color.Orange)
                            maze[playerx, playery].BackColor = Color.Orange;*/
                        break;
                    case Keys.Left:
                        smartWalk(Dirs.West);
                        /*if (maze[playerx-1, playery].BackColor == Color.LightGreen || maze[playerx, playery - 1].BackColor == Color.Orange)
                            maze[playerx, playery].BackColor = Color.Orange;*/
                        break;
                    case Keys.Right:
                        smartWalk(Dirs.East);
                        /*if (maze[playerx+1, playery].BackColor == Color.LightGreen || maze[playerx, playery - 1].BackColor == Color.Orange)
                            maze[playerx, playery].BackColor = Color.Orange;*/
                        break;
                    case Keys.Escape:
                        this.Close();
                        break;
                }
                maze[1, 1].BackColor = Color.LightGreen;
                maze[WIDTH - 2, HEIGHT - 2].BackColor = Color.Red;
                //maze[playerx, playery].BackColor = Color.Purple;

                if (playerx == WIDTH - 2 && playery == HEIGHT - 2) finishLabel_MouseEnter(null, null);
            }
            else
                if (e.KeyCode == Keys.Escape) this.Close();
        }
        private void finishLabel_MouseEnter(object sender, EventArgs e)
        {
            MessageBox.Show("Congratulations!");
            this.Close();
        }
        private void MoveToCheckPoint()
        {
            Cursor.Position = checkPoint;
        }
        private void wall_MouseEnter(object sender, EventArgs e)
        {
            MoveToCheckPoint();
        }

        private void playGrid_MouseEnter(object sender, EventArgs e)
        {
            MoveToCheckPoint();
        }
        private void createGrid()
        {
            int x = 10, y = 10, indexx, indexy;
            for (indexy = 0; indexy < HEIGHT; ++indexy)
            {
                for (indexx = 0; indexx < WIDTH; ++indexx)
                {
                    maze[indexx, indexy] = new Label();
                    //if (counter % 29 == 0) yyy += 20;
                    maze[indexx, indexy].Location = new Point(x, y);
                    maze[indexx, indexy].Text = null;
                    if (MazeGenerator.mazetiles[indexx, indexy] == 2)
                    {
                        maze[indexx, indexy].BackColor = Color.Red;
                        if (gameMode == Mode.Mouse) maze[indexx, indexy].MouseEnter += finishLabel_MouseEnter;
                    }
                    else if (MazeGenerator.mazetiles[indexx, indexy] == 1)
                    {
                        maze[indexx, indexy].BackColor = Color.RoyalBlue;
                        if (gameMode == Mode.Mouse) maze[indexx, indexy].MouseEnter += wall_MouseEnter;
                    }
                    else if (MazeGenerator.mazetiles[indexx, indexy] == 3)
                    {
                        maze[indexx, indexy].BackColor = Color.LightGreen;
                    }
                    else
                    {
                        maze[indexx, indexy].BackColor = Color.White;
                    }
                    maze[indexx, indexy].AutoSize = false;
                    maze[indexx, indexy].Height = 20;
                    maze[indexx, indexy].Width = 20;
                    this.Controls.Add(maze[indexx, indexy]);
                    maze[indexx, indexy].BringToFront();
                    x += 20;
                }
                y += 20;
                x = 10;
            }
        }
        private void onClosing(object sender, FormClosingEventArgs e)
        {
            Application.OpenForms[0].Show();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            foreach (Control control in this.Controls)
            {
                Label label = control as Label;
                if (label != null && label.BackColor == Color.White)
                {
                    Point labelLocation = PointToScreen(label.Location);
                    if (Cursor.Position.X >= labelLocation.X && Cursor.Position.X <= (labelLocation.X + label.Width) && Cursor.Position.Y >= labelLocation.Y && Cursor.Position.Y <= (labelLocation.Y + label.Width))
                    {
                        checkPoint = Cursor.Position;
                    }
                }
            }
        }

        private void onLoad(object sender, EventArgs e)
        {

        }
    }
}
