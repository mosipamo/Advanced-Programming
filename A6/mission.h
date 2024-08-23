#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Mission
{
public:
    // virtual void handle() = 0;
    virtual void print() = 0;

    // bool check_timestamps(int start_mission_timestamp, int end_mission_timestamp)
    // {
    //     if (end_mission_timestamp - start_mission_timestamp > 0)
    //         return true;
    //     else
    //     {
    //         cout << "INVALID_ARGUMENTS\n";
    //         return false;
    //     }
    // }

    // bool check_mission_id(int mission_id)
    // {
    //     for (int i = 0; i < mission_ids.size(); i++)
    //     {
    //         cout << mission_ids[i] << " " << mission_id << " ";
    //         if (mission_ids[i] != mission_id)
    //             return true;
    //         else
    //         {
    //             cout << "DUPLICATE_MISSION_ID\n";
    //             return false;
    //         }
    //     }
    // }

    // bool check_reward(int reward_amount)
    // {
    //     if (reward_amount < 0)
    //     {
    //         cout << "INVALID_ARGUMENTS\n";
    //         return false;
    //     }
    //     else return true;
    // }

    // virtual bool check_target() = 0;

    Mission(int _mission_id, int _start_mission_timestamp, int _end_mission_timestamp, int _reward_amount);

    int get_mission_id(){ return mission_id;}
    int get_start_mission_timestamp(){ return start_mission_timestamp;}
    int get_end_mission_timestamp(){ return end_mission_timestamp;}
    int get_reward_amount(){ return reward_amount;}
    int get_target_time_in_minutes(){ return target_time_in_minutes;}
    int get_target_distance_in_meters(){ return target_time_in_minutes;}
    int get_target_number(){ return target_number;}
    string get_state(){ return state;}
protected:
    // هر ماموریتی از اینا داره
    int mission_id;
    int start_mission_timestamp;
    int end_mission_timestamp;
    int reward_amount;
    string state;

    // if زمانی -> target_time_in_minutes
    int target_time_in_minutes;

    // if مسافتی -> target_distance_in_meters
    int target_distance_in_meters;

    // if تعدادی -> target_number
    int target_number;

    // vector< Driver*> driver;
};