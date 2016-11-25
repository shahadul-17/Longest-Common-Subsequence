#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

static int i, j, sizes[2], **e, **c;
static string lcs = "", inputs[2];

enum
{
    TOP = 1,
    DIAGONAL = 2,
    LEFT = 3
};

void initialize_2D_structures()
{
    c = new int*[sizes[0]];
    e = new int*[sizes[0]];

    for (i = 0; i < sizes[0]; i++)
    {
        c[i] = new int[sizes[1]];
        e[i] = new int[sizes[1]];

        for (j = 0; j < sizes[1]; j++)
        {
            c[i][j] = e[i][j] = 0;
        }
    }
}

void calculate_lcs(int x, int y)
{
	if ((e[x][y] == TOP || e[x][y] == DIAGONAL || e[x][y] == LEFT) && inputs[0].at(x - 1) == inputs[1].at(y - 1))
    {
		lcs = inputs[0].at(x - 1) + lcs;        // lcs - a global variable to store LCS...
    }

	if (e[x][y] == TOP)
	{
		x--;
	}
	else if (e[x][y] == DIAGONAL)
	{
		x--;
		y--;
	}
	else if (e[x][y] == LEFT)
	{
		y--;
	}
	else
	{
		return;
	}

	calculate_lcs(x, y);
}

int main()
{
    cout << "Please enter your first string = ";

    getline(cin, inputs[0]);

    cout << "Now enter your second string = ";

    getline(cin, inputs[1]);

    /*
     * while writing the code, it was assumed that
     * first string will always be longer than the second one...
     */
    if (inputs[1].size() > inputs[0].size())
    {
        string temp = inputs[0];
        inputs[0] = inputs[1];
        inputs[1] = temp;
    }

    sizes[0] = inputs[0].size() + 1;
    sizes[1] = inputs[1].size() + 1;

    initialize_2D_structures();

    for (i = 0; i < sizes[0] - 1; i++)
    {
        for (j = 0; j < sizes[1] - 1; j++)
        {
            if (inputs[0].at(i) == inputs[1].at(j))
            {
                c[i + 1][j + 1] = c[i + 1 - 1][j + 1 - 1] + 1;
                e[i + 1][j + 1] = DIAGONAL;
            }
            else
            {
                if (c[i + 1][j + 1 - 1] > c[i + 1 - 1][j + 1])
                {
                    c[i + 1][j + 1] = c[i + 1][j + 1 - 1];
                    e[i + 1][j + 1] = LEFT;
                }
                else
                {
                    c[i + 1][j + 1] = c[i + 1 - 1][j + 1];
                    e[i + 1][j + 1] = TOP;
                }
            }
        }
    }

    cout << endl << "2D Structure" << endl << "============" << endl << endl;

    for (i = 0; i < sizes[0]; i++)
    {
        for (j = 0; j < sizes[1]; j++)
        {
            cout << "\t" << c[i][j];
        }

        cout << endl << endl;
    }

    cout << endl << "2D Structure of Arrows (Here, T = Top, D = Diagonal, L = Left)" << endl << "==============================================================" << endl << endl;

    for (i = 0; i < sizes[0]; i++)
    {
        for (j = 0; j < sizes[1]; j++)
        {
            cout << "\t";

            switch (e[i][j])
            {
            case TOP:
                cout << "T";

                break;
            case DIAGONAL:
                cout << "D";

                break;
            case LEFT:
                cout << "L";

                break;
            default:
                cout << "0";

                break;
            };
        }

        cout << endl << endl;
    }

    calculate_lcs(sizes[0] - 1, sizes[1] - 1);

    cout << endl << "Length of Longest Common Subsequence (LCS) = " << c[sizes[0] - 1][sizes[1] - 1] << endl;
    cout << "Longest Common Subsequence (LCS) = " << lcs << endl;

    _getch();

    return 0;
}
