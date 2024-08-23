#include "MadEnemy.h"

void MadEnemy::update(const float& delta_time)
{
    total_clock += delta_time;
    if (total_clock >= mad_clock)
    {
        is_mad = !is_mad;
        total_clock -= mad_clock;
    }
    set_speed(delta_time);
    set_gravity(delta_time);
    move(delta_time);
    if (is_mad)
        body->setColor(Color::Red);
    else
    {
        body->setColor(Color::Blue);
    }
}