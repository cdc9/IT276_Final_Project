#ifndef  __PLATFORMS__
#define __PLATFORMS__

#define MAXITEMS 16
#define MAXEVENTS 128

#include "entity.h"
#include "sprite.h"
#include "player.h"



/**
 * @brief Spawns the platform, assigns all of it's values and draws the sprite to screen
 * @param x The x position
 * @param y The y position
 */
Entity *SpawnPlatform(int x, int y);

/**
 * @brief Spawns the platform, assigns all of it's values and draws the sprite to screen
 * @param x The x position
 * @param y The y position
 */
Entity *SpawnPlatform2(int x, int y);


#endif