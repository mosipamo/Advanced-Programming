#include "EnemyEntity.h"
#include "collision.h"

void EnemyEntity::tick(const vector<Platform *> p)
{
    Collision collision;
    Intersection from;
    int on_ground = false;
    for (Platform *platform : p)
    {
        if (collision.check_collision(this->body, platform->get_body(), from))
        {
            if (from == FROM_RIGHT || from == FROM_LEFT)
            {
                face_right = !face_right;
                animation->set_direction(!face_right);
                break;
            }
            else if (from == FROM_UP)
            {
                on_ground = true;
                can_jump = true;
            }
        }
    }
    if (on_ground == false && can_jump == true)
    {
        face_right = !face_right;
        animation->set_direction(!face_right);
    }
}
void EnemyEntity::update(const float& delta_time)
{
    set_speed(delta_time);
    set_gravity(delta_time);
    move(delta_time);
}
void EnemyEntity::move(const float& delta_time)
{
    body->setTexture(*texture);
    animation->update(delta_time, true);
    body->setTextureRect(animation->uv_rect);
    body->setOrigin({body->getLocalBounds().width / 2.0f, body->getLocalBounds().height / 2.0f});
    body->move(velocity);
}