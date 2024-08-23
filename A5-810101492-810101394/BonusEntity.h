#pragma once
#include "GameEntity.h"

class BonusEntity : public GameEntity
{
public:
    BonusEntity(int _point);
    void update(const float& delta_time);
    int get_point();

private:
    int point;
};