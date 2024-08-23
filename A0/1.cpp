#include <iostream>
using namespace std;
int main()
{
    int n = 0, p = 0, q = 0, m = 0;
    int sum = 0, start, end;
    cin >> n;
    int array[n] = {1};
    int array2[n] = {0};
    for(int i = 0; i < n; i++)
    {
        sum = 0;
        cin >> p >> q >> m;
        for(int j = 0; j < m; j++)
        {
            cin >> start >> end;
            int dif = end - start;
            sum += dif;
            if(sum <= p && dif <= q) // ok
            {
                array[i] = 0;
                array2[i] = 0;
            }
            else if(sum <= p && dif > q) // sum ok dif nok
            {
                array[i] = 0;
                array2[i] = dif - q;
            }
            else if (sum > p && dif <=q) // sum nok dif ok
            {
                array[i] = sum - p;
                array2[i] = 0;
            }
            else if(sum > p && dif > q) // sum va dif nok
            {
                array[i] = sum - p;
                array2[i] = dif - q;
            }
        }
    }
    for(int i = 0; i < n;i++)
    {
        cout << array[i] << " " << array2[i] << endl;
    }
}