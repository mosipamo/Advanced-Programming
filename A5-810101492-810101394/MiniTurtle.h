#pragma ocne
#include "LiveEntity.h"

class MiniTurtle : public LiveEntity
{
public:
    void move(const float &dt);
    void set_spawn_texture(Texture *_spawn_texture);
    void set_anime_texture(Texture *_anime_texture);
    void make_free();
    void tick(const vector<Platform *> platfroms);
    virtual void update(const float &delta_time);

private:
    bool reached_by_turtix = false;
    Texture *spawn_texture = new Texture;
    Texture *anime_texture = new Texture;
};