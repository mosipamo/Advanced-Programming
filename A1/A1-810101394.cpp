#include <bits/stdc++.h>
using namespace std;

#define START_DAY_COMMAND 9
#define SHOW_DAY_COMMAND 8
#define SHOW_THE_LONGEST_DAY_COMMAND 20
#define SHOW_THE_BEST_DAY_COMMAND 17
#define SUMMARY 20
#define SPACE_NOT_FOUND -1
#define SHOW_THE_LONGEST_DAY "show_the_longest_day"
#define SHOW_THE_BEST_DAY "show_the_best_day"
#define SUMMARY_STR "..."

vector<string> file_words;
vector<pair<string, string>> diary;

string to_upper(string s)
{
    string temp;
    for (int i = 0; i < s.size(); i++)
    {
        temp += toupper(s[i]);
    }
    return temp;
}

int find_word(string &pat, string &txt)
{
    int cnt = 0;
    int M = pat.size();
    int N = txt.size();

    for (int i = 0; i <= N - M; i++)
    {
        int j;
        for (j = 0; j < M; j++)
            if (txt[i + j] != pat[j])
                break;

        if (j == M)
            cnt++;
    }
    return cnt;
}

void read_file()
{
    ifstream input_file;
    string read_line_from_txt;

    input_file.open("positive-words.txt");
    while (getline(input_file, read_line_from_txt))
        file_words.push_back(read_line_from_txt);
    input_file.close();
}

void add_date(string command, string tempDate)
{
    tempDate = command.substr(START_DAY_COMMAND + 1, (int)command.size());
    diary.push_back(make_pair(tempDate, ""));
}

void show_day(string command)
{
    string tempdate;
    tempdate = command.substr(SHOW_DAY_COMMAND + 1, (int)command.size());
    for (int i = 0; i < (int)diary.size(); i++)
    {
        if (diary[i].first == tempdate)
            cout << diary[i].second;
    }
}

void find_longest_day()
{
    int ind = 0;
    for (int i = 1; i < diary.size(); i++)
    {
        if (diary[i].second.size() > diary[ind].second.size())
            ind = i;
    }
    if (diary[ind].second.size() <= SUMMARY)
        cout << diary[ind].first << "\n"
             << diary[ind].second;
    else
        cout << diary[ind].first << "\n"
             << diary[ind].second.substr(0, 20) << "..." << endl;
}

int find_best_day()
{
    int max_word = 0, ind = 0;
    for (int i = 0; i < diary.size(); i++)
    {
        int count = 0;
        for (int j = 0; j < file_words.size(); j++)
        {
            string txt = to_upper(diary[i].second);
            string pat = to_upper(file_words[j]);
            count += find_word(pat, txt);
        }
        if (count > max_word)
        {
            max_word = count;
            ind = i;
        }
    }
    return ind;
}

void print_best_day(int ind)
{
    if (diary[ind].second.size() <= SUMMARY)
        cout << diary[ind].first << "\n" << diary[ind].second;
    else
        cout << diary[ind].first << "\n" << diary[ind].second.substr(0, SUMMARY) << "..." << endl;
}

int main()
{
    read_file();

    string command, tempDate;
    while (getline(cin, command))
    {
        int space_ind = command.find(" ");

        if (space_ind == START_DAY_COMMAND)
            add_date(command, tempDate);

        else if (space_ind == SHOW_DAY_COMMAND)
            show_day(command);

        else if (space_ind == -1 and command == SHOW_THE_LONGEST_DAY)
            find_longest_day();

        else if (space_ind == -1 and command == SHOW_THE_BEST_DAY)
        {
            int ind = find_best_day();
            print_best_day(ind);
        }

        else if (command == "end")
            break;

        else
            diary[diary.size() - 1].second.append(command + "\n");
    }
    return 0;
}