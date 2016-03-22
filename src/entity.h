#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "vector.h"
#include "sprite.h"

#define MAXSTATES     6

enum STATES     {ST_IDLE,ST_WALK, ST_DIE, ST_DEAD,ST_ATTACK1,ST_ATTACK2}; /**< This will be used for animations*/
enum FACE       {F_South, F_SW, F_West, F_NW,F_North, F_NE, F_East, F_SE,F_NULL}; /**< This will be used to determine where the sprite is facing*/

/**
 * @brief the core data structure for our entity system
 */
typedef struct Entity_S
{
    int      inuse;             /**<flag for tracking resource use*/
    char     name[128];			/**< Used for the names of the entities */
	char	 type[128];			/**< Used to describe the type of entity*/
    Vec2d    position;			/**< Used for the position of the entity */
	Vec2d    lastPosition;		/**< Used for the previous position of the entity */
	Vec2d    offset;			/**< Used for the offset of the entity */
    Vec2d    velocity;			/**< Used for the velocity of the entity*/
    SDL_Rect bounds;			/**<Used for collision detection*/
    Sprite  *sprite;			/**< The sprite of the entity */
	int		 state;				/**<Used for switching states*/
	int		 face;				/**<The direction we are moving in*/
	int		 facing;			/**<The direction we are facing. Lamer version for prototype*/
    int      cameraEnt;         /**<true if the entity is drawn relative to the camera*/
	int		 fcount;			/**<used for animation, the loop variable*/
	int		 frate;				/**<How often we update our frames*/
    int      frame;				/**< The frame of the entity */
	int		 frameW;			/**< The frame width of the entity*/
	int		 frameH;			/**< The frame height of the entity*/
    float    health,maxhealth;	/**< The health and maxhealth of the entity */
	float	 maxspeed, movespeed;	/**< The maximum speed of the entity, and the entities current speed */
	int		 accel;				/**< The accelaration of the entity */
	float	 jumpAccel,maxJumpSpeed;	/**< The jump accelaration of the entity */
	int		 grounded;				/**< int to check see if the player is on the ground */
	int		 timer;				/**< timer for various entities*/
	int		 bulletTimer;				/**< bullet timer for various entities*/
	int		 damage;			/**< Damage of the entity*/
	int		 powerup;			/**< Current powerup the player has*/
    void     (*draw)(struct Entity_S *self,SDL_Renderer *renderer); /**< Defining the draw entity */
    int      nextThink;			/**< time index for next think*/
    int      thinkRate;			/**< how often to run think*/
    void     (*think)(struct Entity_S *self); /**<think function for entity*/
    void     (*update)(struct Entity_S *self); /**<update function for entity */
    void     (*touch)(struct Entity_S *self, struct Entity_S *other); /**<touch function for entity */
    void     (*free)(struct Entity_S *self); /**<cleanup function called on free*/
	struct ENTITY_S *owner;   /**< for bullets, drones and other things spawned by other entities*/
	struct ENTITY_S *target;  /**< used for MANY units: attack target, healing target, etc*/
}Entity;


/**
 * @brief return a pointer to an empty entity structure
 * @return NULL on error or no more space for entities or a valid entity pointer otherwise.
 */
Entity *entity_new();

//Here are a bunch of functions that will be used by the entity

/**
 * @brief initializes entity system and queues up cleanup on exit
 * @param maxEntities how many entities the system should support.  Should not be zero
 */
void initEntitySystem(int maxEntities);

/**
 * @brief closes entity system and cleans up any remaining entities
 */
void closeEntitySystem();


//void entity_free(Entity **entity);

/**
 * @brief removes the entity that was in use and free its sprite at the same time
 * @param entity accept the entity that you wish to be freed.
 */
void entity_free(Entity *entity);

/**
 * @brief Draws entity along with its sprite to its newest location. Also works with camera to update its position.
 * @param ent accept the entity that you wish draw 
 * @param render Accept the render you wish to draw to.
 */
void entity_draw(Entity *ent,SDL_Renderer *render);

/**
 * @brief draws all entities in the entity list
 */
void entity_draw_all();


/**
 * @brief Looking at player velocity, we can determine what direction we should be facing
 * @param self Accepts the player entity 
 */
void GetFace(Entity *self);


//void entity_think_all();
//void entity_draw_all();

/**
 * @brief This is the main update function. Calls the player think function and other entities think functions.
 */
void update();

#endif
