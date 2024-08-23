#pragma once
#include "mission.h"
#include <iostream>

class Distance_mission : public Mission
{
public:

    // virtual void handle();
    virtual void print();
    Distance_mission(int _mission_id, int _start_mission_timestamp, int _end_mission_timestamp, int _reward_amount,int target);
private:
};