#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "entity.h"

/** @file	level.h
 */

/** This is the definition file for the level editor level*/
#define EDITOR_LEVEL					"def/levels/EditorLevel.txt"

/**
 * @struct Level
 * @brief used to check if the end of the level has been reached by the player
 */
typedef struct {
	Entity *cam;
	Entity *player;
	char *level_def_file;
	int end;
}Level;


/**
 * @brief parses the def file for entities to load from the editor level def file
 * @param	[in]	level_def_file	the level's def file
 * @return	the fully loaded editor level
 */
Level *level_load(char *level_def_file);

/**
 * @brief saves the level the editor created in a def file
 */
void level_save();

/**
 * @brief checks if the player is past the end flag for the level
 * @return 1 if player past the end, else 0
 */
Uint8 level_end_reached(Level *level);


#endif