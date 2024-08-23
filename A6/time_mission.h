#pragma once
#include <iostream>
#include "mission.h"

class Time_Mission : public Mission
{
public:
    virtual void print();
    // virtual bool check_target()
    // {
    //     if (target_time_in_minutes > 0)
    //     {
    //         return true;
    //     }
    //     else
    //     {
    //         cout << "INVALID_ARGUMENTS\n";
    //         return false;
    //     }
    // };
    Time_Mission (int _mission_id, int _start_mission_timestamp, int _end_mission_timestamp, int _reward_amount, int target);
    Time_Mission();
private:    
};