#pragma once
#include "LiveEntity.h"
#include <map>

const Color SEMI_TRANSPARENT = {255,255,255,128};
const Color ORIGINAL = {255,255,255,255};


class Turtix : public LiveEntity
{
public:
    Turtix();
    void move(const float& delta_time);
    virtual void update(const float& delta_time,const State& s);

    void add_point(int point);
    int get_point();
    int get_HP();
    void loose_HP(){ HP--; gosted = true;}
    bool get_gosted(){return gosted;}
    void handle_gost(const float& delta_time);
    void set_speed(const float& delt_time,const State& s,const float& cur_speed);
    void set_jump_speed(const float& delta_time ,const State& s);
    
private:
    bool gosted = false;
    int HP = 3;
    int point = 0;
    const int jump_height = 600;
    float max_gost_time = 3;
    float tatal_gosting_time = 0;
};