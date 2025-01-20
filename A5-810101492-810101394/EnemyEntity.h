#include "turtix.h"
class EnemyEntity : public LiveEntity
{
public:
    virtual void tick(const vector<Platform *> platfroms);
    void update(const float& delta_time);
    virtual void move(const float& delta_time);

private:
};