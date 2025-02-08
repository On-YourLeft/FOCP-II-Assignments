#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int num;
    cout<<"Enter the size of the array : ";
    cin>>num;
    int arra[num];
    cout<<"Enter the numbers of the array : ";
    for (int i=0;i<num;i++)
    {
        cin>>arra[i];
    }
    cout<<endl<<"The reversed array : ";
    for (int i=num-1;i>=0;i--)
    {
        cout<<arra[i]<<" ";
    }
    cout<<endl<<endl;
    int n = sizeof(arra)/sizeof(arra[0]);
    sort(arra,arra+n);
    int secsmall = 0, seclarge = 0;
    for (int i=0;i<num;i++)
    {
        if (arra[i]!=arra[0])
        {
            secsmall = arra[i];
            break;
        }
    }

    for (int i=num-2;i>=0;i--)
    {
        if (arra[i]!=arra[num-1])
        {
            seclarge = arra[i];
            break;
        }
    }

    if (secsmall != 0)
    {
        cout<<"The second smallest number in the array is : "<<secsmall<<endl<<endl;
    }
    else
    {
        cout<<"All elements are equal!"<<endl<<endl;
    }

    if(seclarge != 0)
    {
        cout<<"The second largest number in the array is : "<<seclarge<<endl;
    }
    else
    {
        cout<<"All elements are equal!"<<endl<<endl;
    }

    return 0;
}