#ifndef __INITIALIZE_H__
#define __INITIALIZE_H__

/**
 * @brief Calls all other initalization functions
 */
void Init_All();
/**
 * @brief initalizes entity and sprite systems and window size
 */
void Init_Begin();
/**
 * @brief spawns all the entities in the level
 */
void Init_Level();
/**
 * @brief spawns a player entity
 */
void Init_Player();
/**
 * @brief spawns a dummy entity
 */
void Init_Dummy();
/**
 * @brief spawns a platform entity
 */
void Init_Platform();

#endif