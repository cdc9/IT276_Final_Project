#ifndef __PROJECTILE__
#define __PROJECTILE__

#include "entity.h"

/**
 * @brief The update function for bullets
 * @param self The bullet itself.
 */
void UpdateBullet(Entity *self);
/**
 * @brief The Think function for bullets
 * @param self The bullet itself.
 */
void BulletThink(Entity *self);

/**
 * @brief The spawn function for the bullet. More generic stuff for projectiles.
 * @param sx The x position of the projectile
 * @param sy The y position of the projectile
 * @param angle The angle of the projectile
 * @param speed The speed the projectile will be traveling
 * @param accel The acceleration of the projectile
 * @param damage The amount of damage the projectile will do
 */
Entity *SpawnProjectile(int sx,int sy,float angle,float speed,float accel,int damage, int type);
/**
 * @brief The spawn function for the bullet. More specific stuff for bullets.
 * @param sx The x position of the bullet
 * @param sy The y position of the bullet
 * @param angle The angle of the bullet
 * @param speed The speed the bullet will be traveling
 * @param accel The acceleration of the bullet
 * @param damage The amount of damage the bullet will do
 * @param powerup The current powerup the bullet should be using
 */
Entity *SpawnBullet(Entity *owner,int sx,int sy,float angle,float speed,float accel, int damage,int powerup, int type);

/**
 * @brief The spawn function for the bullet. More specific stuff for bullets.
 * @param sx The x position of the bullet
 * @param sy The y position of the bullet
 * @param angle The angle of the bullet
 * @param speed The speed the bullet will be traveling
 * @param accel The acceleration of the bullet
 * @param damage The amount of damage the bullet will do
 * @param type The current type of enemy, which the bullet should be using
 */
Entity *SpawnEnemyBullet(Entity *owner,int sx,int sy,float angle,float speed,float accel, int damage,int type, int enType);

/**
 * @brief The spawn function for the enemy bullet. More specific stuff for bullets.
 * @param self The bullet itself
 */
void UpdateEnemyBullet(Entity *self,int type);



#endif 