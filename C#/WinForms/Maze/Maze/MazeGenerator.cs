using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Maze
{
    public class MazeGenerator
    {
        private static Random random;
        public static int[,] mazetiles;
        public static void GenerateMaze()
        {
            random = new Random();
            mazetiles = new int[MazeWindow.WIDTH, MazeWindow.HEIGHT];
            int indexx, indexy;
            for (indexy = 0; indexy < MazeWindow.HEIGHT; ++indexy)
            {
                for (indexx = 0; indexx < MazeWindow.WIDTH; ++indexx)
                {
                    mazetiles[indexx, indexy] = 1;
                }
            }
            mazetiles[MazeWindow.WIDTH - 2, MazeWindow.HEIGHT - 2] = 2;
            DFS(MazeWindow.WIDTH - 2, MazeWindow.HEIGHT - 2);
            mazetiles[1, 1] = 3;
        }
        public enum Dirs { North, South, West, East }
        private static bool check_neighbours(int x, int y)
        {
            if (x + 1 < MazeWindow.WIDTH) if (mazetiles[x + 1, y] != 1) return false;
            if (x - 1 > 0) if (mazetiles[x - 1, y] != 1) return false;
            if (y + 1 < MazeWindow.HEIGHT) if (mazetiles[x, y + 1] != 1) return false;
            if (x + 1 < MazeWindow.WIDTH && y + 1 < MazeWindow.HEIGHT) if (mazetiles[x + 1, y + 1] != 1) return false;
            if (x - 1 > 0 && y + 1 < MazeWindow.HEIGHT) if (mazetiles[x - 1, y + 1] != 1) return false;
            if (y - 1 > 0) if (mazetiles[x, y - 1] != 1) return false;
            if (x + 1 < MazeWindow.WIDTH && y - 1 > 0) if (mazetiles[x + 1, y - 1] != 1) return false;
            if (x - 1 > 0 && y - 1 > 0) if (mazetiles[x - 1, y - 1] != 1) return false;
            return true;
        }
        private static void DFS(int x, int y)
        {
            List<Dirs> neighbours = new List<Dirs>(4);
            int count = 0;
            if (x + 2 < MazeWindow.WIDTH) if (mazetiles[x + 2, y] == 1) { if (x + 1 < MazeWindow.WIDTH - 1) neighbours.Add(Dirs.East); ++count; }
            if (x - 2 > 0) if (mazetiles[x - 2, y] == 1) { neighbours.Add(Dirs.West); ++count; }
            if (y + 2 < MazeWindow.HEIGHT) if (mazetiles[x, y + 2] == 1) { if (y + 1 < MazeWindow.HEIGHT - 1) neighbours.Add(Dirs.South); ++count; }
            //if(x + 2 < 28 && y + 2 < 27)if (mazetiles[x + 2, y + 2] == 1) ++count;
            //if (x - 2 > 0 && y + 2 < 27) if (mazetiles[x - 2, y + 2] == 1) ++count;
            if (y - 2 > 0) if (mazetiles[x, y - 2] == 1) { neighbours.Add(Dirs.North); ++count; }
            //if (x + 2 < 28 && y - 2 > 0) if (mazetiles[x + 2, y - 2] == 1) ++count;
            //if (x - 2 > 0 && y - 2 > 0) if (mazetiles[x - 2, y - 2] == 1) ++count;
            if (count == 0) return;
            switch (neighbours.ElementAt(random.Next(neighbours.Count)))
            {
                case Dirs.East:
                    if (check_neighbours(x + 2, y))
                    {
                        mazetiles[x + 1, y] = 0;
                        mazetiles[x + 2, y] = 0;
                        DFS(x + 2, y);
                    }
                    break;
                case Dirs.West:
                    if (check_neighbours(x - 2, y))
                    {
                        mazetiles[x - 2, y] = 0;
                        mazetiles[x - 1, y] = 0;
                        DFS(x - 2, y);
                    }
                    break;
                case Dirs.South:
                    if (check_neighbours(x, y + 2))
                    {
                        mazetiles[x, y + 1] = 0;
                        mazetiles[x, y + 2] = 0;
                        DFS(x, y + 2);
                    }
                    break;
                case Dirs.North:
                    if (check_neighbours(x, y - 2))
                    {
                        mazetiles[x, y - 1] = 0;
                        mazetiles[x, y - 2] = 0;
                        DFS(x, y - 2);
                    }
                    break;
            }
            DFS(x, y);
            return;
        }
    }
}
