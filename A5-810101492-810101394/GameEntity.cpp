#include "GameEntity.h"
#include <string>
using namespace std;

void GameEntity::draw(RenderWindow *window)
{
    window->draw(*body);
}

void GameEntity::set_animation(const string& image_file,const IntRect& int_rect,const ImageMatrix& images,const float& switch_time)
{
    set_texture(image_file, int_rect);

    texture->setSmooth(true);

    animation = new Animation(texture, images, switch_time);
}

void GameEntity::set_texture(const string& image_file,const IntRect& int_rect)
{
    texture->loadFromFile(image_file, int_rect);
}