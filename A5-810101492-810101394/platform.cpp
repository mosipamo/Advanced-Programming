// #pragma once
#include "platform.h"
Sprite *Platform::get_body() { return body; }
void Platform::draw(RenderWindow *window)
{
    window->draw(*body);
}
Platform::Platform(Texture *texture, Vector2f size, Vector2f position)
{
    body->setOrigin({size.x, size.y});
    body->setTexture(*texture);
    body->setPosition(position);
}