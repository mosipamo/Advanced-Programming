#include "BonusEntity.h"

BonusEntity::BonusEntity(int _point)
{
    point = _point;
}

void BonusEntity::update(const float& delta_time)
{
    body->setTexture(*texture);
    animation->update(delta_time, true);
    body->setTextureRect(animation->uv_rect);
}

int BonusEntity::get_point()
{
    return point;
}
