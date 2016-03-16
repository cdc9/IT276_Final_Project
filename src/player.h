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

Entity *SpawnPlayer(int x, int y);

/**
 * @brief free's sprite, then updates player position.
 * @param self the player entity
 */
void UpdatePlayer(Entity *self);

/**
 * @brief Player think function. Mainly handles movement and speed right now
 * @param self the player entity
 */
void PlayerThink(Entity *self);


/**
 * @brief Handles the player inputs. PlayerCommands will be used by other functions to do things.
 */
void UpdateInput();

//void DefaultConfig();



#endif 