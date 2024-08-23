#include<iostream>
#include<vector>
using namespace std;

const int ROW_COUNT = 7;
const int COL_COUNT = 7;

vector<pair<int, int>> valid_moves;

vector < pair < int, int >> mamad (char board[ROW_COUNT][COL_COUNT])
{    
    vector < pair < int , int >> res;
    for(int i = 0; i < ROW_COUNT; i++)
    {
        for(int j = 0; j < COL_COUNT; j++)
        {
            if(board[i][j] == 'N')
            {
                if(j <= 5 && board[i][j + 1] == 'N' && board[i][j + 2] == 'O')
                    res.push_back(make_pair(i * 7 + j, 0));
                if (i <= 5 && board[i + 1][j] == 'N' && board[i + 2][j] == 'O')
                    res.push_back(make_pair(i * 7 + j, 1));
                if (j >= 2 && board[i][j - 1] == 'N' && board[i][j - 2] == 'O')
                    res.push_back(make_pair(i * 7 + j, 2));
                if (i >= 2 && board[i - 1][j] == 'N' && board[i - 2][j] == 'O')
                    res.push_back(make_pair(i * 7 + j, 3));
            }
        }
    }
    return res;
}

void print_moves( pair < int, int > mv)
{
    char alphabet[7] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    int x = mv.first / 7;
    int y = mv.first % 7;
    if(mv.second == 0)
        cout << alphabet[x] << y + 1 << " " << "RIGHT\n";
    else if (mv.second == 1)
        cout << alphabet[x] << y + 1 << " " << "DOWN\n";
    else if (mv.second == 2)
        cout << alphabet[x] << y + 1 << " " << "LEFT\n";
    else if (mv.second == 3)
        cout << alphabet[x] << y + 1 << " " << "UP\n";
}
int solve(char board[ROW_COUNT][COL_COUNT], int count)
{
    if(count == 1 && board[3][3] == 'N') 
        return 1;
    int state = 0;
    vector < pair < int, int >> moves = mamad(board);
    for(int i = 0; i < moves.size(); i++)
    {
        int x = moves[i].first / 7;
        int y = moves[i].first % 7;
        if(moves[i].second == 0)
        {
            board[x][y] = 'O';
            board[x][y + 1] = 'O';
            board[x][y + 2] = 'N';
        }
        else if(moves[i].second == 1)
        {
            board[x][y] = 'O';
            board[x + 1][y] = 'O';
            board[x + 2][y] = 'N';
        }
        else if(moves[i].second == 3)
        {
            board[x][y] = 'O';
            board[x - 1][y] = 'O';
            board[x - 2][y] = 'N';
        }
        else if(moves[i].second == 2)
        {
            board[x][y] = 'O';
            board[x][y - 1] = 'O';
            board[x][y - 2] = 'N';
        }

        int state = solve(board, count - 1);
        if(state == 1)
        {
            valid_moves.push_back(moves[i]);
            return 1; 
        }

        if(moves[i].second == 0)
        {
            board[x][y] = 'N';
            board[x][y + 1] = 'N';
            board[x][y + 2] = 'O';
        }
        else if(moves[i].second == 1)
        {
            board[x][y] = 'N';
            board[x + 1][y] = 'N';
            board[x + 2][y] = 'O';
        }
        else if(moves[i].second == 3)
        {
            board[x][y] = 'N';
            board[x - 1][y] = 'N';
            board[x - 2][y] = 'O';
        }
        else if(moves[i].second == 2)
        {
            board[x][y] = 'N';
            board[x][y - 1] = 'N';
            board[x][y - 2] = 'O';
        }
    }
    return 0;
}
int main()
{
    char arr[ROW_COUNT][COL_COUNT];
    int cnt = 0;
    for(int i = 0; i < ROW_COUNT; i++)
    {
        for(int j = 0; j < COL_COUNT; j++)
        {
            cin >> arr[i][j];
        }
    }

    for(int i = 0; i < ROW_COUNT; i++)
    {
        for(int j = 0; j < COL_COUNT; j++)
        {
            if(arr[i][j] == 'N')
                cnt++; 
        }
    }
    
    int state = solve(arr, cnt);
    if(state == 0) 
        cout << "Loser\n";
    else 
    {
        for(int i = valid_moves.size() - 1; i >= 0; i--)
        {
            print_moves(valid_moves[i]);
        }
    }
}