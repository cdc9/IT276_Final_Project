#ifndef __LEVELEDITOR_H__
#define __LEVELEDITOR_H__

#include "vector.h"
#include "sprite.h"
#include "entity.h"

typedef struct Editor_t
{
    int      inuse;             /**<flag for tracking resource use*/
    char     name[128];			/**< Used for the names of the entities */
	char	 type[128];			/**< Used to describe the type of entity*/
	int		 entType;			/**< Used to describe the type of entity*/
    Vec2d    position;			/**< Used for the position of the entity */
	Vec2d    lastPosition;		/**< Used for the previous position of the entity */
    Sprite  *sprite;			/**< The sprite of the entity */
}LevelEditor;

/**
 * @brief This will show the editor on screen
 */
void showEditor();
/**
 * @brief This is the get amount of certain type of entity.
 * @param editorEnt This represents the entity within the level editor
 * @param objectList The current object number that gets spawned into the editor
 */
void spriteChange(LevelEditor *editorEnt, int objectList);

/**
 * @brief This is the get amount of certain type of entity.
 * @param cursor The cursor within the level editor
 * @param editorEnt This represents the entity within the level editor
 */
void placeObject(Entity *cursor, LevelEditor *editorEnt);



#endif