#ifndef __PROJECTILE__
#define __PROJECTILE__

#include "entity.h"

void UpdateBullet(Entity *self);

void BulletThink(Entity *self);

Entity *SpawnProjectile(int sx,int sy,float angle,float speed,float accel,int damage);
Entity *SpawnBullet(Entity *owner,int sx,int sy,float angle,float speed,float accel, int damage,int powerup);





#endif 