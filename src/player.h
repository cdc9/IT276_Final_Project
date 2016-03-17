#ifndef  __PLAYER__
#define __PLAYER__

#define MAXITEMS 16
#define MAXEVENTS 128

#include "entity.h"
#include "sprite.h"

typedef struct Player_t
{
	int weapon[2];				/**<the 2 offensive and 1 defensive weapon that is equipped.  -1 implies no weapon*/
	int weaponindex;			/**<the current weapon is this index*/
	int inventory[MAXITEMS];	/**<Indexed list of items that the player owns.*/
	int map;					/**<the map that the player saved in*/
	int mx, my;					/**<the coordinates that the player is in.*/
} Player;

/**
 * @brief Spawns the Dummy, assigns all of it's values and draws the sprite to screen
 * @param x The x position
 * @param y The y position
 */
Entity *SpawnDummy(int x, int y);
/**
 * @brief Spawns the player, assigns all of it's values and draws the sprite to screen
 * @param x The x position
 * @param y The y position
 */
Entity *SpawnPlayer(int x, int y);

/**
 * @brief free's sprite, then updates player position. Also works with the camera
 * @param self the player entity
 */
void UpdatePlayer(Entity *self);
/**
 * @brief Dummy update function
 * @param self the dummy entity
 */
void UpdateDummy(Entity *self);
/**
 * @brief Player think function. Mainly handles movement and speed right now
 * @param self the player entity
 */
void PlayerThink(Entity *self);
/**
 * @brief Dummy think function. 
 * @param self the Dummy entity
 */
void DummyThink(Entity *self);

/**
 * @brief Handles the player inputs. PlayerCommands will be used by other functions to do things.
 */
void UpdateInput();

//void DefaultConfig();



#endif 