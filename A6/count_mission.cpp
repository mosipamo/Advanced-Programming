#include "count_mission.h"
#include <iostream>

using namespace std;

// void Count_Mission::handle()
// {
//     cin >> mission_id >> start_mission_timestamp >> end_mission_timestamp >> target_time_in_minutes >> reward_amount;
//     mission_ids.push_back(mission_id);
// }

Count_Mission::Count_Mission(int _mission_id, int _start_mission_timestamp, int _end_mission_timestamp, int _reward_amount, int target)
    : Mission(_mission_id, _start_mission_timestamp, _end_mission_timestamp, _reward_amount)
{
    if (target < 0)
        throw invalid_argument("INVALID_ARGUMENTS\n");
    target_distance_in_meters = target;
}

void Count_Mission::print()
{
    cout << mission_id << " " << start_mission_timestamp << " " << end_mission_timestamp << " " << reward_amount << " " << target_time_in_minutes;
}