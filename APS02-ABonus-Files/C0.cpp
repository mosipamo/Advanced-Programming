#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

#define sixty 60
#define movement_time 30
#define possible_check_time 15
#define ten_oclock_or_minutes 10
#define third_index_for_minutes 3
#define start_pos 0
#define zero_str "0"
#define seperate_character ","

struct Time
{
	int hour;
	int minute;
};

struct Place
{
	string name;
	int rank;
	Time open_time;
	Time close_time;
	bool have_gone;
};

bool sort_by_rank(Place beginning, Place next)
{
	return beginning.rank < next.rank;
}

vector<string> seperate_words(const string line, string separate_char = seperate_character)
{
	vector<string> words;
	string temp = line;
	size_t pos = start_pos;
	while ((pos = temp.find(separate_char)) != string::npos)
	{
		words.push_back(temp.substr(start_pos, pos));
		temp.erase(start_pos, pos + separate_char.length());
	}
	words.push_back(temp);
	return words;
}

vector<Place> get_command_line2(vector<Place> places, vector<string> title, vector<string> lines)
{
	int name_index = distance(title.begin(), find(title.begin(), title.end(), "name"));
	int rank_index = distance(title.begin(), find(title.begin(), title.end(), "rank"));
	int open_time_index = distance(title.begin(), find(title.begin(), title.end(), "openingTime"));
	int close_time_index = distance(title.begin(), find(title.begin(), title.end(), "closingTime"));
	for (int i = 1; i < lines.size(); i++)
	{
		Place temp;
		vector<string> words_in_line = seperate_words(lines[i]);
		temp.name = words_in_line[name_index];
		temp.rank = stoi(words_in_line[rank_index]);
		temp.open_time.hour = stoi(words_in_line[open_time_index]);
		temp.open_time.minute = stoi(words_in_line[open_time_index].substr(third_index_for_minutes));
		temp.close_time.hour = stoi(words_in_line[close_time_index]);
		temp.close_time.minute = stoi(words_in_line[close_time_index].substr(third_index_for_minutes));
		temp.have_gone = false;
		places.push_back(temp);
	}
	return places;
}

vector<Place> get_command_line1(int argc, char const *argv[])
{
	ifstream instream;
	instream.open(argv[1]);
	if (instream.fail())
	{
		cout << "Input file opening failed.\n";
		exit(1);
	}
	vector<string> lines;
	string temp;
	while (getline(instream, temp))
		lines.push_back(temp);
	instream.close();
	vector<string> title = seperate_words(lines[start_pos]);
	vector<Place> temp_places;
	vector<Place> places = get_command_line2(temp_places, title, lines);
	sort(places.begin(), places.end(), sort_by_rank);
	return places;
}

int doring_time(Place place, Time now)
{
	return (place.close_time.hour - now.hour) * sixty + (place.close_time.minute - now.minute);
}

Time add_time(Time now, int doring__time)
{
	if (doring__time >= sixty)
	{
		now.hour += 1;
		return now;
	}
	now.minute += doring__time;
	if (now.minute >= sixty)
	{
		now.hour++;
		now.minute -= sixty;
	}
	return now;
}

bool is_time_grater(Time t1, Time t2)
{
	if (t1.hour * sixty + t1.minute >= t2.hour * sixty + t2.minute)
		return true;
	return false;
}

int find_first_open_time(const vector<Place> places, Time start_time = {0, 0})
{
	int index = -1, i;
	for (i = 0; i < places.size(); i++)
		if (is_time_grater(places[i].open_time, start_time))
		{
			index = i;
			break;
		}
	for (int j = i + 1; j < places.size(); j++)
	{
		if (places[j].open_time.hour < places[index].open_time.hour && is_time_grater(places[j].open_time, start_time))
		{
			index = j;
			continue;
		}
		if (places[j].open_time.hour == places[index].open_time.hour && places[j].open_time.minute < places[index].open_time.minute && is_time_grater(places[j].open_time, start_time))
			index = j;
	}
	return index;
}

int find_best_place_index(const vector<Place> places, const Time now)
{
	int index = -1;
	if (now.minute == -1)
	{
		index = find_first_open_time(places);
	}
	else
	{
		for (int i = 0; i < places.size(); i++)
		{
			if (!places[i].have_gone && doring_time(places[i], now) >= possible_check_time && is_time_grater(now, places[i].open_time))
			{
				index = i;
				return index;
			}
		}
	}
	return index;
}

string time2_str(Time t)
{
	string str;
	if (t.hour < ten_oclock_or_minutes)
		str += zero_str + to_string(t.hour);
	else
		str += to_string(t.hour);
	str += ":";
	if (t.minute < ten_oclock_or_minutes)
		str += zero_str + to_string(t.minute);
	else
		str += to_string(t.minute);
	return str;
}

void print_places(Place place, Time start_time, Time end_time)
{
	string start = time2_str(start_time);
	string end = time2_str(end_time);
	cout << "Location " << place.name << endl;
	cout << "Visit from " << start << " until " << end << endl;
	cout << "---" << endl;
}

Time skip_time(const vector<Place> places, Time now)
{
	int index = find_first_open_time(places, now);
	Time skiped_time = {-1, -1};
	if (index == -1)
		return skiped_time;
	else
	{
		skiped_time = places[index].open_time;
		return skiped_time;
	}
}

void where_to_go(vector<Place> places)
{
	Time now = {-1, -1};
	Time end_time;
	for (int i = 0; i < places.size(); i++)
	{
		int index = find_best_place_index(places, now);
		if (index == -1)
		{
			now = skip_time(places, add_time(now, 1));
			if (now.hour == -1)
				break;
			else
			{
				i--;
				continue;
			}
		}
		if (now.minute == -1)
		{
			now.hour = places[index].open_time.hour;
			now.minute = places[index].open_time.minute;
			end_time = add_time(now, doring_time(places[index], now));
		}
		else
			end_time = add_time(now, doring_time(places[index], now));
		places[index].have_gone = true;
		print_places(places[index], now, end_time);
		now = add_time(end_time, movement_time);
	}
}

int main(int argc, char const *argv[])
{
	vector<Place> places = get_command_line1(argc, argv);
	where_to_go(places);
	return 0;
}