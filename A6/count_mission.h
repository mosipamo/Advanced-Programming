#pragma once
#include "mission.h"
#include <iostream>

class Count_Mission : public Mission
{
public:

    // virtual void handle();
    virtual void print();
    // virtual bool check_target()
    // {
    //     if (target_number > 0)
    //     {
    //         return true;
    //     }
    //     else
    //     {
    //         cout << "INVALID_ARGUMENTS\n";
    //         return false;
    //     }
    // };

    Count_Mission (int _mission_id, int _start_mission_timestamp, int _end_mission_timestamp, int _reward_amount, int target);

private:
};