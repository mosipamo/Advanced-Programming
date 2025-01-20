#include "turtix.h"
#include <cmath>
#include <iostream>

int delta_x[4] = {-1, 0, 1, 0};
int delta_y[4] = {0, -1, 0, 1};
const int STEP_SIZE = 2;

Turtix::Turtix() { name = TURTIX; }

void Turtix::update(const float& delta_time,const State& state)
{
    handle_gost(delta_time);
    float cur_speed = (is_moving) ? speed : 0;
    set_jump_speed(delta_time, state);
    set_gravity(delta_time);
    set_speed(delta_time, state, cur_speed);
    move(delta_time);
}

void Turtix::add_point(int point)
{
    this->point += point;
}

int Turtix::get_point()
{
    return point;
}

int Turtix::get_HP()
{
    return HP;
}

void Turtix::handle_gost(const float& delta_time)
{
    if (gosted)
    {
        tatal_gosting_time += delta_time;
    }
    if (tatal_gosting_time >= max_gost_time)
    {
        gosted = false;
        tatal_gosting_time = 0;
    }
}
void Turtix::set_speed(const float& delta_time,const State& state,const float& cur_speed)
{
    if (state == RIGHT)
        velocity.x = cur_speed * delta_time;

    else if (state == LEFT)
        velocity.x = -cur_speed * delta_time;

    else
        velocity.x = 0.0f;
}
void Turtix::move(const float& delta_time)
{
    body->setTexture(*texture);
    animation->update(delta_time, is_moving);
    body->setTextureRect(animation->uv_rect);
    body->setOrigin({body->getLocalBounds().width / 2.0f, body->getLocalBounds().height / 2.0f});
    body->move(velocity);
    if (gosted)
        body->setColor(SEMI_TRANSPARENT);
    else
        body->setColor(ORIGINAL);
}
void Turtix::set_jump_speed(const float& delta_time,const State& state)
{

    if (state == JUMP && can_jump)
    {
        can_jump = false;
        velocity.y = -sqrtf(0.25f * jump_height);
    }
}