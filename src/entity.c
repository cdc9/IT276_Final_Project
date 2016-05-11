#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>

#include "entity.h"
#include "simple_logger.h"
#include "camera.h"
#include "player.h"
#include "projectile.h"
#include "enemy.h"
#include "vector.h"

static Entity * EntityList = NULL;
static Uint32 MaxEntities = 0;



int entity_intersect(Entity *a, Entity *b);			//Collision code
int entity_intersect_rect(Entity *a,SDL_Rect r);
int max_ents;
extern int currentLevel;
extern SDL_Rect _Camera;

void initEntitySystem(int maxEntities)
{
    if (maxEntities == 0)
    {
        slog("cannot allocate zero Entities!");
        return;
    }
    EntityList = (Entity *)malloc(sizeof(Entity) * maxEntities);
    if (!EntityList)
    {
        slog("failed to allocate Entity system.");
        return;
    }
    memset(EntityList,0,sizeof(Entity)*maxEntities);
    MaxEntities = maxEntities;
    atexit(closeEntitySystem);
}

void closeEntitySystem()
{
    int i;
    Entity *ent;
    for (i = 0; i < MaxEntities;i++)
    {
        ent= &EntityList[i];
        entity_free(&ent);
    }
    free(EntityList);
}


Entity *entity_new()
{
    int i;
    for (i = 0; i < MaxEntities;i++)
    {
        if (EntityList[i].inuse)
        {
            continue;
        }
        memset(&EntityList[i],0,sizeof(Entity));
        /*set some default values here*/
        EntityList[i].inuse = 1;
		//slog("entities have been used");
		max_ents++;
        return &EntityList[i];
    }
    return NULL;
}
/*
void entity_free(Entity **entity) //original
{
    Entity *self;
    if (!entity)return;
    if (!*entity)return;
    self = *entity;
    freeSprite(&self->sprite);
    *entity = NULL;
}
*/
void entity_free(Entity *entity) 
{
	entity->inuse = 0;
	max_ents--;

    freeSprite(entity->sprite);

}
void entity_free_all()
{
	int i;
    Entity *ent = NULL;
    for (i = 0; i < MaxEntities;i++)
    {
		ent= &EntityList[i];
		if(ent->inuse == 0)
		{
			continue;
		}
        entity_free(ent);
    }

}
void entity_draw(Entity *ent,SDL_Renderer *render)
{
    Vec2d position;
    SDL_Rect camera;
    if ((!ent)||(!render))
    {
        slog("error: no entity or renderer passed");
        return;
    }
    if (!ent->sprite)
    {
        slog("error: entity %s has no sprite!",ent->name);
        return;
    }
    camera = camera_get_active_camera();
    if (!entity_intersect_rect(ent,camera))
    {
        return;
    }
    if (ent->cameraEnt)
    {
        position.x = ent->position.x - camera.x;
        position.y = ent->position.y - camera.y;
    }
    drawSprite(ent->sprite,ent->frame,position);
}

void entity_draw_all()
{
	Vec2d position;
    SDL_Rect camera;
	Entity *temp = NULL;
	int i;
	camera = camera_get_active_camera();
    for (i = 0; i < MaxEntities;i++)
    {
        if (!EntityList[i].inuse)
        {
            continue;
        }
        if(EntityList[i].inuse == 1)
		{
			temp = &EntityList[i];
			
		/*if (!entity_intersect_rect(temp,camera))
		{
			return;
		}*/
		if (temp->cameraEnt)
		{
			position.x = temp->position.x - camera.x;
			position.y = temp->position.y - camera.y;
		}
		drawSprite(temp->sprite,temp->frame, position);
		}
     
    }
}
/*
void entity_think_all()
{
    int i;
    for (i = 0; i < MaxEntities;i++)
    {
        if (!EntityList[i].inuse)
        {
            continue;
        }
        
        if (!EntityList[i].think)
        {
            continue;
        }
        
        EntityList[i].think(&EntityList[i]);
    }
}

*/
Entity *entity_intesect_all(Entity *a)
{
    int i;
    if (!a)return NULL;
    for (i = 0; i < MaxEntities;i++)
    {
        if (!EntityList[i].inuse)
        {
            continue;
        }
        if (a == &EntityList[i])
        {
            continue;
            /*don't clip self*/
        }
        if (entity_intersect(a, &EntityList[i]))
        {
            return &EntityList[i];
        }
    }
    return NULL;
}

int entity_intersect_rect(Entity *a,SDL_Rect r)
{
    SDL_Rect aB;
    if (!a)
    {
        slog("ERROR: Missing entity for check");
        return 0;
    }
    aB = rect(
        a->position.x + a->bounds.x,
        a->position.y + a->bounds.y,
        a->bounds.w,
        a->bounds.h);
    return rect_intersect(aB,r);
}

int entity_intersect(Entity *a, Entity *b)
{
    SDL_Rect aB,bB;
    if ((!a) || (!b))
    {
        slog("ERROR: Missing entity for check");
        return 0;
    }
    aB = rect(
        a->position.x + a->bounds.x,
        a->position.y + a->bounds.y,
        a->bounds.w,
        a->bounds.h);
    bB = rect(
        b->position.x + b->bounds.x,
        b->position.y + b->bounds.y,
        b->bounds.w,
        b->bounds.h);
    return rect_intersect(aB,bB);
}

void GetFace(Entity *self)
{
  if((self->velocity.x == 0)&&(self->velocity.y == 0))
  {
    self->face = F_NULL;
    return;
  }
  if(self->velocity.x < -2)
  {
    if(self->velocity.y < -2)self->face = F_NW;
    else if(self->velocity.y > 2)self->face = F_SW;
    else self->face = F_West;
  }
  else if(self->velocity.x > 2)
  {
    if(self->velocity.y < -2)self->face = F_NE;
    else if(self->velocity.y > 2)self->face = F_SE;
    else self->face = F_East;
  }
  else
  {
    if(self->velocity.y < 0)self->face = F_North;
    else if(self->velocity.y > 0)self->face = F_South;
  }
}

void update()
{
	int i = 0;
	int j;
	while (i < MaxEntities)
	{
		//do think function
		/*if(EntityList[i].inuse == 1 && EntityList[i].think != NULL)
		{
			(*EntityList[i].think)(&EntityList[i]);
		}*/

		//scrolls through entities in use
		if(EntityList[i].inuse == 1)
		{
			Entity *tempEnt;
			int X;
			int Y;

			tempEnt = &EntityList[i];
			X = tempEnt -> position.x;
			Y = tempEnt -> position.y;
			if(strcmp(tempEnt ->name, "Player")==0)
			{
				PlayerThink(tempEnt);
			}
			if(strcmp(tempEnt ->name, "Dummy")==0)
			{
				DummyThink(tempEnt);
			}
			if(strcmp(tempEnt ->name, "Camera")==0)
			{
				EntityList[i].position.x = _Camera.x;
				EntityList[i].position.y = _Camera.y;
			}
			if(strcmp(tempEnt ->name, "Projectile")==0)
			{
				UpdateBullet(tempEnt);
			}
			if(strcmp(tempEnt ->name, "EnemyProjectile1")==0)
			{
				UpdateEnemyBullet(tempEnt,1);
			}
			if(strcmp(tempEnt ->name, "EnemyProjectile2")==0)
			{
				UpdateEnemyBullet(tempEnt,2);
			}
			if(strcmp(tempEnt ->name, "EnemyProjectile3")==0)
			{
				UpdateEnemyBullet(tempEnt,3);
			}
			if(strcmp(tempEnt ->name, "EnemyProjectile4")==0)
			{
				UpdateEnemyBullet(tempEnt,4);
			}
			if(strcmp(tempEnt ->name, "Enemy")==0)
			{
				if(strcmp(tempEnt ->type, "type1")==0)
				UpdateEnemy(tempEnt,1);
			}
			if(strcmp(tempEnt ->name, "Enemy")==0)
			{
				if(strcmp(tempEnt ->type, "type2")==0)
				UpdateEnemy(tempEnt,2);
			}
			if(strcmp(tempEnt ->name, "Enemy")==0)
			{
				if(strcmp(tempEnt ->type, "type3")==0)
				UpdateEnemy(tempEnt,3);
			}
			if(strcmp(tempEnt ->name, "Enemy")==0)
			{
				if(strcmp(tempEnt ->type, "type4")==0)
				UpdateEnemy(tempEnt,4);
			}
		}
		//Stuff for collision
		for(j=0; j <  MaxEntities; j++)
		{
			if(EntityList[j].inuse && j != i)
			{
				if(entity_intersect(&EntityList[i],&EntityList[j]))
				{
					//slog("The player is colliding %d", EntityList[i].name);
					if(!strcmp(EntityList[i].name, "Player"))
					{
						if(!strcmp(EntityList[j].name, "Platform"))
						{
							EntityList[i].grounded = 0;
							EntityList[i].position.y = EntityList[i].lastPosition.y;
							//slog("it has been set to %d", EntityList[i].grounded);
						}
						if(!strcmp(EntityList[j].name, "Platform2"))
						{
							EntityList[i].grounded = 0;
							EntityList[i].position.y = EntityList[i].lastPosition.y;
							//slog("it has been set to %d", EntityList[i].grounded);
						}
						if(!strcmp(EntityList[j].name, "Platform3"))
						{
							EntityList[i].grounded = 0;
							EntityList[i].position.x = EntityList[i].lastPosition.x;
							//slog("it has been set to %d", EntityList[i].grounded);
						}
						if(!strcmp(EntityList[j].name, "EnemyProjectile1") ||!strcmp(EntityList[j].name, "EnemyProjectile2") ||!strcmp(EntityList[j].name, "EnemyProjectile3") ||!strcmp(EntityList[j].name, "EnemyProjectile4"))
						{
							EntityList[i].health -= EntityList[j].damage;
							entity_free(&EntityList[j]);
							//slog("it has been set to %d", EntityList[i].grounded);
						}
						if(!strcmp(EntityList[j].name, "Enemy"))
						{
							EntityList[i].health -= 5;
						}
					}
					if(!strcmp(EntityList[i].name, "Enemy"))
					{
						if(!strcmp(EntityList[i].type, "type1") ||!strcmp(EntityList[i].type, "type2") ||!strcmp(EntityList[i].type, "type4"))
						{
							if(!strcmp(EntityList[j].name, "Platform")||!strcmp(EntityList[j].name, "Platform2")||!strcmp(EntityList[j].name, "Platform3"))
							{
								EntityList[i].position.y = EntityList[i].lastPosition.y;
							}
						}
						if(!strcmp(EntityList[j].name, "Projectile"))
						{
							EntityList[i].health -= EntityList[j].damage;
							entity_free(&EntityList[j]);
						}
					}
					if(!strcmp(EntityList[i].name, "Dummy"))
					{
						if(!strcmp(EntityList[j].name, "Camera"))
						{
							slog("The camera has collided with the dummy! Spawn enemy!");
							SpawnEnemy(EntityList[i].position.x,EntityList[i].position.y, EntityList[i].spawnType);
							entity_free(&EntityList[i]);
						}
					}
				}
			}
		}
		i++; // ANSWER!!!
		
	}
	
}

Entity* getPlayer()
{
	int i;

	for (i = 0; i < MaxEntities; i++)
	{
		if (!strcmp(EntityList[i].name, "Player"))
		{
			return &EntityList[i];
		}
	}
	return NULL;
}

int entity_get_number_of_type(int currentType)
{
	int i;
	int amount = 0;

	for (i = 0; i < MaxEntities; i++)
	{
		if(!EntityList[i].inuse)
		{
			continue;
		}
		if(EntityList[i].entType != currentType)
		{
			continue;
		}
		amount++;
	}
	return amount++;
}

Vec2d entity_get_position_of_type(int type)
{
	static int i = 0;
	static int currentType = 0;
	Vec2d pos = vec2d(0, 0);

	if(type != currentType)
	{
		i = 0;
		currentType = type;
	}
	while(i < MaxEntities)
	{
		if(!EntityList[i].inuse)
		{
			i++;
			continue;
		}
		if(EntityList[i].entType != currentType)
		{
			i++;
			continue;
		}
		pos = EntityList[i].position;
		i++;
		break;
	}
	return pos;
}
/*eol@eof*/