#include "EnemyEntity.h"
class  MadEnemy : public EnemyEntity
{
public:
    void update(const float& delta_time);
    bool get_mad(){ return is_mad;}
    private:
    bool is_mad = false;    
    float mad_clock = 3.0;
    float total_clock = 0;
};