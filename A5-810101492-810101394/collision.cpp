#include "collision.h"
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

bool Collision::check_collision(Sprite *player, Sprite *object, Intersection &from)
{
    Vector2f player_position = calc_entity_position(player);
    Vector2f player_half_size = calc_entity_half_size(player);

    Vector2f object_position = calc_entity_position(object);
    Vector2f object_half_size = calc_entity_half_size(object);

    float delta_x = player_position.x - object_position.x;
    float delta_y = player_position.y - object_position.y;

    float intersect_x = abs(delta_x) - (player_half_size.x + object_half_size.x);
    float intersect_y = abs(delta_y) - (player_half_size.y + object_half_size.y);

    if (intersect_x <= 0.0f && intersect_y <= 0.0f)
    {
        if (intersect_x > intersect_y)
        {
            if (delta_x >= 0.0f)
            {
                player->move(-intersect_x, 0.0f);
                from = FROM_RIGHT;
            }
            else
            {
                player->move(intersect_x, 0.0f);
                from = FROM_LEFT;
            }
        }
        else
        {
            if (delta_y > 0.0f)
            {
                player->move(0.0f, -intersect_y);
                from = FROM_DOWN;
            }
            else
            {
                player->move(0.0f, intersect_y);
                from = FROM_UP;
            }
        }
        return true;
    }
    from = NO_WHERE;
    return false;
}

Vector2f Collision::calc_entity_position(Sprite *entity_position)
{
    return {entity_position->getGlobalBounds().left + entity_position->getLocalBounds().width / 2,
            entity_position->getGlobalBounds().top + entity_position->getLocalBounds().height / 2};
}

Vector2f Collision::calc_entity_half_size(Sprite *entitty_half_size)
{
    return {entitty_half_size->getLocalBounds().width / 2, entitty_half_size->getLocalBounds().height / 2};
}
