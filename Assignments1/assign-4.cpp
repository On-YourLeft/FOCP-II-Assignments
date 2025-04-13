#include <iostream>

using namespace std;

int main()
{
    int num;
    cout << "Enter the size of 'n' for the matrix (nxn) : ";
    cin >> num;
    int matra[num][num];
    
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            cout << "Enter the value [" << i + 1 << "][" << j + 1 << "] : ";
            cin >> matra[i][j];
        }
    }

    int top = 0, bottom = num - 1, left = 0, right = num - 1;

    cout<<endl<<"The matrix : "<<endl<<endl;

    for (int i=0;i<num;i++)
    {
        for (int j=0;j<num;j++)
        {
            cout<<matra[i][j]<<" ";
        }
        cout<<endl;
    }

    cout << endl << "Spiral order : ";
    while (top <= bottom && left <= right)
    {
        for (int i = left; i <= right; i++)
        {
            cout << matra[top][i] << " ";
        }
        top++;

        for (int i = top; i <= bottom; i++)
        {
            cout << matra[i][right] << " ";
        }
        right--;

        if (top <= bottom)
        {
            for (int i = right; i >= left; i--)
            {
                cout << matra[bottom][i] << " ";
            }
            bottom--;
        }

        if (left <= right)
        {
            for (int i = bottom; i >= top; i--)
            {
                cout << matra[i][left] << " ";
            }
            left++;
        }
    }

    cout << endl<<endl;

    return 0;
}
