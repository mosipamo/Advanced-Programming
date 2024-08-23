#include<iostream>
#include<string>
using namespace std;

string to_upper(string line, int i = 0)
{
    if(i >= line.size())
        return line;
    line[i] = toupper(line[i]);
    return to_upper(line, i + 1);
}

int main()
{
    string line;
    while (getline(cin, line))
    {
        cout << to_upper(line) << endl;
    }
}