#pragma ocne
#include <SFML/Graphics.hpp>
using namespace sf;

class Platform
{
public:
    Platform(Texture *texture, Vector2f size, Vector2f position);
    void draw(RenderWindow *window);
    Sprite *get_body();

private:
    Sprite *body = new Sprite;
};