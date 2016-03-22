#ifndef  __ENEMY__
#define __ENEMY__

#define MAXITEMS 16
#define MAXEVENTS 128

#include "entity.h"
#include "sprite.h"
#include "player.h"

typedef struct Enemy_t
{
	int weapon[2];				/**<the 2 offensive and 1 defensive weapon that is equipped.  -1 implies no weapon*/
	int weaponindex;			/**<the current weapon is this index*/
	int inventory[MAXITEMS];	/**<Indexed list of items that the player owns.*/
	int map;					/**<the map that the player saved in*/
	int mx, my;					/**<the coordinates that the player is in.*/
} Enemy;

/**
 * @brief Spawns the Enemy, assigns all of it's values and draws the sprite to screen
 * @param x The x position
 * @param y The y position
 * @param type The type of enemy you wish to spawn
 */
Entity *SpawnEnemy(int x, int y,int type);

/**
 * @brief update the enemy
 * @param self the enemy entity
 */
void UpdateEnemy(Entity *self, int type);
/**
 * @brief Spawns the Enemy, assigns all of it's values and draws the sprite to screen
 * @param x The x position
 * @param y The y position
 * @param type The type of enemy you wish to spawn
 */
Entity *SpawnBoss(int x, int y);

/**
 * @brief update the enemy
 * @param self the enemy entity
 */
void UpdateBoss(Entity *self);
/**
 * @brief Enemy think function. 
 * @param self the Enemy entity
 */
void EnemyThink(Entity *self);

#endif