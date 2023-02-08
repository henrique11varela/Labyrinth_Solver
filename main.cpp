#include "class/Image.h"
#include <iomanip>
#include <string>
using namespace std;
/*
0 - empty
1 - wall
9 - path
*/

// Display------------------------------------------------------------------------------------
void display(int **lab, int w, int h)
{
    char wall = 219;
    char solv = 178;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            switch (lab[i][j])
            {
            case 1: // wall
                cout << wall << wall;
                break;
            case 9: // path
                cout << solv << solv;
                break;
            default: // empty
                cout << setw(2) << /* lab[i][j] */ "";
                break;
            }
        }
        cout << "\n";
    }
}

/* Finds the last bread crumb and follows it back */
void pathTrace(int **lab, int w, int h, int x, int y)
{
    int value = lab[y][x];
    lab[y][x] = 9;
    if (value == 10)
    {
        return;
    }

    if (x != 0)
    {
        if (lab[y][x - 1] == value - 1)
        {
            pathTrace(lab, w, h, x - 1, y);
        }
    }
    if (x != w - 1)
    {
        if (lab[y][x + 1] == value - 1)
        {
            pathTrace(lab, w, h, x + 1, y);
        }
    }
    if (y != 0)
    {
        if (lab[y - 1][x] == value - 1)
        {
            pathTrace(lab, w, h, x, y - 1);
        }
    }
    if (y != h - 1)
    {
        if (lab[y + 1][x] == value - 1)
        {
            pathTrace(lab, w, h, x, y + 1);
        }
    }
};

/* Tests and discovers a path leaving bread crumbs */
void pathFind2(int **lab, int w, int h, int x, int y, int distance)
{
    lab[y][x] = 10 + distance;
    if ((x != 0 && x != w - 1 && y != 0 && y != h - 1))
    {

        if (lab[y][x - 1] == 0 || lab[y][x - 1] > (lab[y][x] + 1))
        {
            pathFind2(lab, w, h, x - 1, y, distance + 1);
        }
        if (lab[y][x + 1] == 0 || lab[y][x + 1] > (lab[y][x] + 1))
        {
            pathFind2(lab, w, h, x + 1, y, distance + 1);
        }
        if (lab[y - 1][x] == 0 || lab[y - 1][x] > (lab[y][x] + 1))
        {
            pathFind2(lab, w, h, x, y - 1, distance + 1);
        }
        if (lab[y + 1][x] == 0 || lab[y + 1][x] > (lab[y][x] + 1))
        {
            pathFind2(lab, w, h, x, y + 1, distance + 1);
        }
    }
    else if (distance == 0)
    {
        if (x != 0)
        {
            if (lab[y][x - 1] == 0 || lab[y][x - 1] > (lab[y][x] + 1))
            {
                pathFind2(lab, w, h, x - 1, y, distance + 1);
            }
        }
        if (x != w - 1)
        {
            if (lab[y][x + 1] == 0 || lab[y][x + 1] > (lab[y][x] + 1))
            {
                pathFind2(lab, w, h, x + 1, y, distance + 1);
            }
        }
        if (y != 0)
        {
            if (lab[y - 1][x] == 0 || lab[y - 1][x] > (lab[y][x] + 1))
            {
                pathFind2(lab, w, h, x, y - 1, distance + 1);
            }
        }
        if (y != h - 1)
        {
            if (lab[y + 1][x] == 0 || lab[y + 1][x] > (lab[y][x] + 1))
            {
                pathFind2(lab, w, h, x, y + 1, distance + 1);
            }
        }
    }
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
    // Discover Path---------------------------------------------------------------------------------
    pathFind2(lab, img.w, img.h, entrance[1], entrance[0], 0);

    // Find exit
    int maior = 0;
    int maiorPos[2];
    for (int i = 0; i < img.w; i++)
    {
        if (lab[0][i] > maior)
        {
            maior = lab[0][i];
            maiorPos[0] = 0;
            maiorPos[1] = i;
        }
        if (lab[i][img.h - 1] > maior)
        {
            maior = lab[img.h - 1][i];
            maiorPos[0] = img.h - 1;
            maiorPos[1] = i;
        }
    }
    for (int i = 1; i < img.h - 1; i++)
    {
        if (lab[i][0] > maior)
        {
            maior = lab[i][0];
            maiorPos[0] = i;
            maiorPos[1] = 0;
        }
        if (lab[i][img.h - 1] > maior)
        {
            maior = lab[i][img.w - 1];
            maiorPos[0] = i;
            maiorPos[1] = img.h - 1;
        }
    }

    // Trace Path----------------------------------------------------------------------------
    pathTrace(lab, img.w, img.h, maiorPos[1], maiorPos[0]);

    // Display------------------------------------------------------------------------------------
    display(lab, img.w, img.h);

    // make new data and output --------------------------------------------
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
