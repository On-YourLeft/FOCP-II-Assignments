#include <iostream>
#include <cmath>

using namespace std;

int isprime(int x);
int nextprime (int x);
void factos(int x);


int main()
{
    int num;
    doit:
    cout<<"Enter the input number : ";
    cin>>num;
    if (num>0)
    {
        int check = isprime(num);
        if (check == 1)
        {
            cout<<num<<" is a prime number."<<endl;

            cout<<"The next prime number is : "<<nextprime(num);
        }
        else
        {
            cout<<num<<" is not a prime number."<<endl;
            factos(num);
        }
    }
    else
    {
        cout<<"Enter a positive integer!!!"<<endl;
        goto doit;
    }
    return 0;
}

int isprime(int x)
{
    for (int i=2;i<=sqrt(x);i++)
    {
        if ((x%i)==0)
        {
            return 0;
        }
    }
    return 1;
}

int nextprime(int x)
{
    int temp=x+1;
    while (1)
    {
        int yeso=isprime(temp);
        if (yeso==1)
        {
            return temp;
        }
        temp++;
    }
}

void factos(int x)
{
    cout << "The factors of " << x << " are: ";
    for (int i = 1; i <= x; i++)
    {
        if (x % i == 0)
        {
            cout << i << " ";
        }
    }
    cout << endl;
}