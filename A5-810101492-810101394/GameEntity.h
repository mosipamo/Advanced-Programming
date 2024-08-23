#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "animation.h"
#include "platform.h"
#include <vector>

using namespace std;

enum State
{
    LEFT,
    IDLE,
    RIGHT,
    JUMP,
};

enum GameObject
{
    TURTIX,
    ENEMY,
    MADENEMY,
    MINITURTLE,
    STAR,
    DIAMOND,
    WALL,
};

using namespace sf;

class GameEntity
{
public:
    virtual void draw(RenderWindow *window);
    virtual void set_animation(const string& image,const IntRect& int_rect,const ImageMatrix& images,const float& switch_time = 0.15f);
    GameObject get_name() { return name; }
    void set_texture(const string& image,const IntRect& int_rect);
    Vector2f get_position() { return body->getPosition(); }
    Sprite *get_body() { return body; }
    void set_pos(int x, int y)
    {
        body->setPosition(x, y);
    }
    void set_body()
    {
        body->setTexture(*texture);
    }

protected:
    IntRect position;
    Sprite *body = new Sprite;
    Texture *texture = new Texture;
    Animation *animation;
    GameObject name;
};