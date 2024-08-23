#include <iostream>
#include "driver.h"
#include "time_mission.h"
#include "count_mission.h"
#include "distance_mission.h"

const string ADD_TIME_MISSION = "add_time_mission";
const string ADD_DISTANCE_MISSION = "add_distance_mission";
const string ADD_COUNT_MISSION = "add_count_mission";
const string ASSIGN_MISSION = "assign_mission";
const string SHOW_MISSION_STATUS = "show_missions_status";
const string EXIT = "exit";
const string PRINT = "print";

using namespace std;

void handle_assign_mission(vector<Driver *> &drivers, vector<int> mission_ids, int mission_id, vector<Mission *> missions)
{
    try
    {
        int driver_id, j = 0;
        cin >> mission_id >> driver_id;
        Driver *driver;
        for (j = 0; j < drivers.size(); j++)
        {
            if (drivers[j]->get_driver_id() == driver_id)
            {
                driver = drivers[j];
                break;
            }
        }
        if (j == drivers.size())
            driver = new Driver(driver_id);

        for (j = 0; j < missions.size(); j++)
        {
            if (missions[j]->get_mission_id() == mission_id)
            {
                if (driver->check_driver(mission_id))
                    throw invalid_argument("DUPLICATE_DRIVER_MISSION\n");
                driver->assign_driver(driver_id, missions[j]);
                drivers.push_back(driver);
                cout << "OK" << endl;
                break;
            }
        }
        if (j == missions.size())
        {
            throw invalid_argument("MISSION_NOT_FOUND\n");
        }
    }
    catch (const invalid_argument &e)
    {
        cerr << e.what();
    }
}

void input_time_mission(vector<Mission *> &missions, vector<int> &mission_ids)
{
    int mission_id, mission_start_timestamp, mission_end_timestamp, reward_amount;
    int target_time_in_minutes;
    cin >> mission_id >> mission_start_timestamp >> mission_end_timestamp >> reward_amount >> target_time_in_minutes;
    try
    {
        Time_Mission *time_mission = new Time_Mission(mission_id, mission_start_timestamp, mission_end_timestamp, reward_amount, target_time_in_minutes);
        for (int i = 0; i < mission_ids.size(); i++)
            if (mission_ids[i] == mission_id)
                throw invalid_argument("DUPLICATE_MISSION_ID\n");
        mission_ids.push_back(mission_id);
        missions.push_back(time_mission);
        cout << "OK" << endl;
    }
    catch (const invalid_argument &e)
    {
        cerr << e.what();
    }
}

void input_distance_mission(vector<Mission *> &missions, vector<int> &mission_ids)
{
    int mission_id, mission_start_timestamp, mission_end_timestamp, reward_amount;
    int target_distance_in_meters;
    cin >> mission_id >> mission_start_timestamp >> mission_end_timestamp >> reward_amount >> target_distance_in_meters;
    try
    {
        Distance_mission *distance_mission = new Distance_mission(mission_id, mission_start_timestamp, mission_end_timestamp, reward_amount, target_distance_in_meters);
        for (int i = 0; i < mission_ids.size(); i++)
            if (mission_ids[i] == mission_id)
                throw invalid_argument("DUPLICATE_MISSION_ID\n");
        mission_ids.push_back(mission_id);
        missions.push_back(distance_mission);
        cout << "OK" << endl;
    }
    catch (const invalid_argument &e)
    {
        cerr << e.what();
    }
}

void input_count_mission(vector<Mission *> &missions, vector<int> &mission_ids)
{
    int mission_id, mission_start_timestamp, mission_end_timestamp, reward_amount;
    int target_number;
    cin >> mission_id >> mission_start_timestamp >> mission_end_timestamp >> reward_amount >> target_number;
    try
    {
        Count_Mission *count_mission = new Count_Mission(mission_id, mission_start_timestamp, mission_end_timestamp, reward_amount, target_number);
        for (int i = 0; i < mission_ids.size(); i++)
            if (mission_ids[i] == mission_id)
                throw invalid_argument("DUPLICATE_MISSION_ID\n");
        mission_ids.push_back(mission_id);
        missions.push_back(count_mission);
        cout << "OK" << endl;
    }
    catch (const invalid_argument &e)
    {
        cerr << e.what();
    }
}

void show_missions(vector<Mission *> &missions, vector<Driver *> drivers)
{
    int driver_id;
    cin >> driver_id;
    for (int i = 0; i < drivers.size(); i++)
    {
        if (drivers[i]->get_driver_id() == driver_id)
        {
            cout << "mission status for driver " << i + 1 << endl;
            drivers[i]->show_missions_status();
            break;
        }
    }
}

int main()
{
    string command;
    vector<Mission *> missions;
    vector<Driver *> drivers;
    vector<int> mission_ids;
    int mission_id, mission_start_timestamp, mission_end_timestamp, reward_amount;
    int target_distance_in_meters, target_number, target_time_in_minutes;
    while (cin >> command)
    {
        if (command == ADD_TIME_MISSION)
            input_time_mission(missions, mission_ids);

        else if (command == ADD_DISTANCE_MISSION)
            input_distance_mission(missions, mission_ids);

        else if (command == ADD_COUNT_MISSION)
            input_count_mission(missions, mission_ids);

        else if (command == PRINT)
        {
            for (int i = 0; i < missions.size(); i++)
            {
                missions[i]->print();
                cout << "\n";
            }
        }

        else if (command == ASSIGN_MISSION)
            handle_assign_mission(drivers, mission_ids, mission_id, missions);

        else if (command == SHOW_MISSION_STATUS)
            show_missions(missions, drivers);
        
        else if (command == EXIT)
            break;
    }
}