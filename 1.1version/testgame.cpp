#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int size = 4;
    vector<vector<int>> net(4, vector<int>(4, 0));
    net[3][0] = 2;
    net[1][0] = 2;
    net[2][0] = 2;
    cout << "Bảng cũ : " << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << net[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (int j = 0; j < size; j++)
    {
        int pos = size - 1;
        for (int i = size - 1; i >= 0; i--)
        {
            if (net[i][j] != 0)
            {
                net[pos][j] = net[i][j];
                if (pos != i)
                {
                    net[i][j] = 0;
                }
                pos--;
            }
        }
        for (int k = size - 1; k >= 1; k--)
        {
            if (net[k][j] == net[k - 1][j])
            {
                net[k][j] *= 2;
                net[k - 1][j] = 0;
            }
        }
        int newpos = size - 1;
        for (int i = size - 1; i >= 0; i--)
        {
            if (net[i][j] != 0)
            {
                net[newpos][j] = net[i][j];
                if (newpos != i)
                {
                    net[i][j] = 0;
                }
                newpos--;
            }
        }
    }
    cout << "Bảng mới : " << endl;
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << net[i][j] << " ";
        }
        cout << endl;
    }
}
