#pragma once
#include "GameEntity.h"
#include <SFML/Graphics.hpp>

enum Intersection
{
    FROM_UP,
    FROM_DOWN,
    FROM_RIGHT,
    FROM_LEFT,
    NO_WHERE
};

class LiveEntity : public GameEntity
{
public:
    virtual void tick(const vector<Platform *> platfroms);
    void set_moving_status(bool _is_moving);
    void set_jump_status(bool _can_jump);
    void set_animation_direction(State s);
    void set_state(State state);
    void handle_collision(Intersection from);
    void set_gravity(const float& dt);
    void set_speed(const float& dt,const float &speed = 250);

protected:
    Vector2f velocity;
    bool is_moving = false;
    bool face_right = true;
    float speed = 250;
    bool can_jump = true;
};