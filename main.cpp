#include "class/Image.h"
#include <string>
using namespace std;
/*
0 - empty
1 - wall
2 - seen
3 - negative
9 - path
 */

/* Tests and discovers a path */
int pathFind(int **lab, int w, int h, int x, int y, bool start)
{
    lab[y][x] = 2; // marks seen
    if (!start)    // check if end
    {
        if (x == 0 || x == w - 1 || y == 0 || y == h - 1)
        {
            lab[y][x] = 9;
            return 9;
        }
    }

    // check NEWS
    if (lab[y][x - 1] == 0) // W
    {
        if (pathFind(lab, w, h, x - 1, y, false) == 9)
        {
            lab[y][x] = 9;
            return 9;
        }
    }
    if (lab[y][x + 1] == 0) // E
    {
        if (pathFind(lab, w, h, x + 1, y, false) == 9)
        {
            lab[y][x] = 9;
            return 9;
        }
    }
    if (lab[y - 1][x] == 0) // N
    {
        if (pathFind(lab, w, h, x, y - 1, false) == 9)
        {
            lab[y][x] = 9;
            return 9;
        }
    }
    if (lab[y + 1][x] == 0) // S
    {
        if (pathFind(lab, w, h, x, y + 1, false) == 9)
        {
            lab[y][x] = 9;
            return 9;
        }
    }
    lab[y][x] = 3; // marks negative
    return 3;
}

/* looks for the entrance */
int *findEntrance(int **lab, int w, int h)
{
    int *entrance = new int[2];
    for (int i = 0; i < w; i++)
    {
        if (lab[0][i] == 0)
        {
            entrance[1] = i;
            entrance[0] = 0;
        }
        if (lab[w - 1][i] == 0)
        {
            entrance[1] = i;
            entrance[0] = w - 1;
        }
    }
    for (int i = 1; i < h - 1; i++)
    {
        if (lab[i][0] == 0)
        {
            entrance[1] = 0;
            entrance[0] = i;
        }
        if (lab[i][h - 1] == 0)
        {
            entrance[1] = h - 1;
            entrance[0] = i;
        }
    }
    return entrance;
}

int main(int argc, char const *argv[])
{
    cout << "Write the path for the png: ";
    char *path;
    cin >> path;
    Image img(path); // instance
    // img to 2d array
    int counter = 0;
    int **lab = new int *[img.h];
    for (int i = 0; i < img.h; i++)
    {
        lab[i] = new int[img.w];
        for (int j = 0; j < img.w; j++)
        {
            lab[i][j] = (img.data[counter++ * img.channels] == 0) ? 1 : 0;
        }
    }
    // look for entrance
    int *entrance = findEntrance(lab, img.w, img.h);
    if (pathFind(lab, img.w, img.h, entrance[1], entrance[0], true) == 9)
    {
        cout << "Labyrinth solved!!!!\n";
    }
    else
    {
        cout << "Labyrinth not solved...\n";
    }
    // Display
    char wall = 219;
    char solv = 178;
    for (int i = 0; i < img.h; i++)
    {
        for (int j = 0; j < img.w; j++)
        {
            switch (lab[i][j])
            {
            case 1: // wall
                cout << wall << wall;
                break;
            case 3: // negative
                cout << "X ";
                break;
            case 9: // path
                cout << solv << solv;
                break;
            default: // empty
                cout << "  ";
                break;
            }
        }
        cout << "\n";
    }
    // make new data and output
    counter = 0;
    uint8_t *newData = new uint8_t[img.size];
    for (int i = 0; i < img.h; i++)
    {
        for (int j = 0; j < img.w; j++)
        {
            switch (lab[i][j])
            {
            case 1: // wall
                newData[counter * 3] = 0;
                newData[counter * 3 + 1] = 0;
                newData[counter * 3 + 2] = 0;
                break;
            case 9: // path
                newData[counter * 3] = 255;
                newData[counter * 3 + 1] = 0;
                newData[counter * 3 + 2] = 0;
                break;
            default: // empty
                newData[counter * 3] = 255;
                newData[counter * 3 + 1] = 255;
                newData[counter * 3 + 2] = 255;
                break;
            }
            counter++;
        }
    }
    img.write("output.png", newData);
    cout << "\nThe output is in 'output.png'\n\nGithub: henrique11varela\n\n";
    cout << "Press Enter...";
    cin.ignore();
    cin.ignore();
    return 0;
}
