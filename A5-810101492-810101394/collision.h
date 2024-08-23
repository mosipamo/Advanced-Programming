#pragma once
#include <SFML/Graphics.hpp>
#include "turtix.h"

using namespace sf;

class Collision
{
public:
    bool check_collision(Sprite *player, Sprite *object, Intersection &from);

private:
    Vector2f calc_entity_position(Sprite *entity);
    Vector2f calc_entity_half_size(Sprite *entiy_haalf_size);

    void move(Sprite body, float dx, float dy) { body.move(dx, dy); }
};
