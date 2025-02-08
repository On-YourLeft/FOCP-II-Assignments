#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    string whatisit;
    cout<<"Enter the string : ";
    getline (cin,whatisit);
    string revto=whatisit;
    string anotherone=whatisit;
    reverse(revto.begin(),revto.end());
    if (revto==whatisit)
    {
        cout<<whatisit<<" is a palindrome."<<endl;
    }
    else
    {
        cout<<whatisit<<" is not a palindrome."<<endl;
    }
    reverse(revto.begin(),revto.end());
    sort(revto.begin(),revto.end());
    int x = whatisit.size();
    for (int i=0;i<x;i++)
    {
        int lost=1;
        for (int j=1;j<x;j++)
        {
            if (whatisit[i]==whatisit[j])
            {
                lost++;
            }
        }
        cout<<"The frequency of "<<whatisit[i]<<" is : "<<lost<<endl;        
    }

    char replo;
    cout<<"Enter the character you want to replace all vowels with : ";
    cin>>replo;

    for (int i=0;i<x;i++)
    {
        if (anotherone[i]=='a'||anotherone[i]=='A'||anotherone[i]=='e'||anotherone[i]=='E'||anotherone[i]=='i'||anotherone[i]=='I'||anotherone[i]=='o'||anotherone[i]=='O'||anotherone[i]=='u'||anotherone[i]=='U')
        {
            anotherone[i]=replo;
        }
    }
    cout<<"The replaced string is : "<<anotherone<<endl;
}