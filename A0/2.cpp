#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int main()
{
    int n = 0, p = 0, q = 0, m = 0;
    int sum = 0, start, end;
    cin >> n;
    int array[n] = {1};
    for(int i = 0; i < n; i++)
    {
        sum = 0;
        cin >> p >> q >> m;
        for(int j = 0; j < m; j++)
        {
            cin >> start >> end;
            int dif = end - start;
            sum += dif;
            if(sum <= p && dif <= q)
            {
                array[i] = 1;
            }
            else
            {
                array[i] = 0;
            }
        }
    }
    for(int i = 0; i < n;i++)
    {
        cout << array[i];
    }
}