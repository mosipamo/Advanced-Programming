#include<iostream>
using namespace std;

int Catalan(int n)
{
    if(n <= 1)
        return 1;
    int catalan_num = 0;
    for(int i = 0; i < n; i++)
    {
        catalan_num += Catalan(i) * Catalan(n - i - 1);
    }
    return catalan_num;
}

int main()
{
    int num;
    cin >> num;
    cout << Catalan(num);
}