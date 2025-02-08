#include <iostream>

using namespace std;

int main()
{
    int num;
    cout<<"Enter the size of 'n' for the matrix (nxn) : ";
    cin>>num;
    int matra[num][num];
    for (int i=0;i<num;i++)
    {
        for (int j=0;j<num;j++)
        {
            cout<<"Enter the value ["<<i+1<<"]["<<j+1<<"] : ";
            cin>>matra[i][j];
        }
    }
    
    int rotated[num][num];
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            rotated[j][num - i - 1] = matra[i][j];
        }
    }

    cout << "The matrix after 90 degrees rotation:" << endl;
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            cout << rotated[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}