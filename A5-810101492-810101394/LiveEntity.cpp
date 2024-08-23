#include "LiveEntity.h"

void LiveEntity::tick(vector<Platform *> p)
{
}

void LiveEntity::set_moving_status(bool _is_moving)
{
    is_moving = _is_moving;
}

void LiveEntity::set_state(State state)
{
    set_animation_direction(state);
    if (state == RIGHT)
        set_moving_status(true);
    else if (state == LEFT)
        set_moving_status(true);
    else
        set_moving_status(false);
}

void LiveEntity::set_animation_direction(State state)
{
    if (state == RIGHT)
        animation->set_direction(false);
    else if (state == LEFT)
        animation->set_direction(true);
}

void LiveEntity::handle_collision(Intersection from)
{
    if (from == FROM_DOWN)
    {
        velocity.y = 1.0f;
    }
    else if (from == FROM_UP)
    {
        velocity.y = 0.0f;
    }
    if (from == FROM_RIGHT)
    {
        is_moving = false;
        velocity.x = 0.0f;
    }
    else if (from == FROM_LEFT)
    {
        is_moving = false;
        velocity.x = 0.0f;
    }
}
void LiveEntity::set_jump_status(bool _can_jump)
{
    can_jump = _can_jump;
}
void LiveEntity::set_gravity(const float& delta_time)
{
    if (!can_jump)
        velocity.y += 9.8f * delta_time;
    else
        velocity.y = 0.0f;
}
void LiveEntity::set_speed(const float& delta_time,const float& cur_speed)
{
    if (face_right == false)
        velocity.x = -cur_speed * delta_time;
    else if (face_right == true)
        velocity.x = cur_speed * delta_time;
}