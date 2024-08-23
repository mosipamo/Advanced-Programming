#pragma once
#include "mission.h"
using namespace std;

class Driver
{
public:
    Driver(int _driver_id)
    {
        driver_id = _driver_id;
    }
    void assign_driver(int _driver_id, Mission *mission)
    {
        driver_id = _driver_id;
        driver_missions.push_back(mission);
    };

    int get_driver_id() { return driver_id; }

    bool check_driver(int d_id)
    {
        for (int i = 0; i < driver_missions.size(); i++)
        {
            if (driver_missions[i]->get_mission_id() == d_id)
            {
                return true;
            }
        }
        return false;
    }

    void show_missions_status()
    {
        for (int i = 0; i < driver_missions.size(); i++)
        {
            cout << "mission " << driver_missions[i]->get_mission_id() << ":\n" << "start timestamp: "<< driver_missions[i]->get_start_mission_timestamp() << "\nend timestamp: " << driver_missions[i]->get_end_mission_timestamp() << 
            "\nreward: " << driver_missions[i]->get_reward_amount() << "\nstatus: " << driver_missions[i]->get_state() << "\n\n"; 
        }
    }

protected:
    int start_timestamp;
    int end_timestamp;
    int driver_id;
    vector<Mission *> driver_missions;
};