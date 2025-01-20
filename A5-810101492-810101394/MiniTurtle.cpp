#include "MiniTurtle.h"
#include "collision.h"
void MiniTurtle::set_spawn_texture(Texture *_spawn_texture)
{
    spawn_texture = _spawn_texture;
}

void MiniTurtle::set_anime_texture(Texture *_anime_texture)
{
    anime_texture = _anime_texture;
}

void MiniTurtle::make_free()
{
    reached_by_turtix = true;
}

void MiniTurtle::tick(const vector<Platform *> p)
{
    if (!reached_by_turtix)
    {
        velocity = {0.0f, 0.0f};
        return;
    }
    Collision collision;
    Intersection from;
    bool is_on_ground = false;
    for (Platform *platform : p)
    {
        if (collision.check_collision(this->body, platform->get_body(), from))
        {
            this->handle_collision(from);

            if (from == FROM_UP)
                is_on_ground = true;
            if (from == FROM_LEFT )
                {
                    face_right = true;
                    animation->set_direction(true);
                }
            if (from == FROM_RIGHT)
                {
                    face_right = false;
                    animation->set_direction(false);
                }
        }
    }
    if (!is_on_ground)
        this->set_jump_status(false);
    else
        this->set_jump_status(true);

    if (reached_by_turtix == true){
        is_moving =true;
    }
    return;
}
void MiniTurtle::update(const float& delta_time)
{
    float cur_speed = (is_moving) ? speed : 0;
    set_gravity(delta_time);
    set_speed(delta_time, -cur_speed);
    move(delta_time);
}
void MiniTurtle::move(const float& delta_time){
    if (reached_by_turtix == false)
        body->setTexture(*spawn_texture);
    else
    {
        is_moving = true;
        body->setTexture(*anime_texture);
        animation->update(delta_time, is_moving);
        body->setTextureRect(animation->uv_rect);
    }
    body->setOrigin({body->getLocalBounds().width / 2.0f, body->getLocalBounds().height / 2.0f});
    body->move(velocity);
}
