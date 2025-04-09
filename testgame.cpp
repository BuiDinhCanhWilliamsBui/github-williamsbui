#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int size = 4;
    vector<vector<int>> net(4, vector<int>(4, 0));
    net[0][0] = 0;
    net[0][1] = 2;
    net[0][2] = 2;
    net[0][3] = 2;
    cout << "Bảng cũ : " << endl;
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << net[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = size - 1; i >= 0; i--)
    {
        int pos = size - 1;
        for (int j = size - 1; j >= 0; j--)
        {
            if (net[i][j] != 0)
            {
                net[i][pos] = net[i][j];
                if (pos != j)
                {
                    net[i][j] = 0;
                }
                pos--;
            }
        }
        for (int k = size - 1; k > 0; k--)
        {
            if (net[i][k] == net[i][k - 1])
            {
                net[i][k] *= 2;
                net[i][k - 1] = 0;
            }
        }
        int newpos = size - 1;
        for (int j = size - 1; j >= 0; j--)
        {
            if (net[i][j] != 0)
            {
                net[i][newpos] = net[i][j];
                if (newpos != j)
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
