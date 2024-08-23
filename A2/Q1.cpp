#include<iostream>
using namespace std;

int n;
int j = -1;
void solve(int cur, int prev, int state, int arr[], int n)
{
    if(cur >= n)
        return ;
    
    cout << arr[cur] << " ";

    if(arr[0] == 0)
        return;
    
    if(arr[cur] == 0)
    {
        if(max(arr[prev] , arr[cur]) == 0 && min(arr[cur], arr[cur - j]) == 0)
            return ;
    }
    if(arr[cur] == 0)
    {
        if(min(arr[prev] , arr[cur]) == 0 && max(arr[cur], arr[cur - j]) == 0)
            return ;
    }
    if (state == 1)     
        j = max(arr[cur], arr[prev]);
    else
        j = min(arr[cur], arr[prev]);
    
    solve(cur + j, cur, 1 - state, arr, n);
}
int main()
{
    cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    solve(0, 0, 1, arr, n);
}