#include "mission.h"
#include <iostream>

using namespace std;

Mission::Mission(int _mission_id, int _start_mission_timestamp, int _end_mission_timestamp, int _reward_amount)
{
  if (_end_mission_timestamp - _start_mission_timestamp < 0)
  {
    throw invalid_argument("INVALID_ARGUMENTS\n");
  }
  // for (int i = 0; i < mission_ids.size(); i++)
  // {
  //   if (mission_ids[i] == _mission_id)
  //     throw invalid_argument("DUPLICATE_MISSION_ID\n");
  // }
  if (_reward_amount < 0)
  {
    throw invalid_argument("INVALID_ARGUMENTS\n");
  }
  mission_id = _mission_id;
  start_mission_timestamp = _start_mission_timestamp;
  end_mission_timestamp = _end_mission_timestamp;
  reward_amount = _reward_amount;
  state = "ongoing";
}
