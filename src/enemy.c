#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <SDL.h>

#include "enemy.h"
#include "player.h"
#include "graphics.h"
#include "entity.h"
#include "projectile.h"
#include "simple_logger.h"
#include "camera.h"

extern SDL_Surface *screen;
extern SDL_Rect _Camera;
extern int deltaTime;

Entity *TheEnemy = NULL;

Entity *SpawnEnemy(int x, int y,int type)
{
	Entity *newent = NULL;
	newent = entity_new();
	if (newent == NULL)
	{
		fprintf(stderr, "Unable to generate player entity; %s", SDL_GetError());
		exit(0);
	}
	strcpy(newent->name,"Enemy");
	switch(type)
	{
	case 1:
		strcpy(newent->type,"type1");
		newent->sprite = loadSprite("images/enemy1.png",24,26,1);
		newent -> bounds.x = 0;
		newent -> bounds.y = 0;
		newent -> bounds.w = 24;
		newent -> bounds.h = 26;
		newent -> maxhealth = 20;
		newent -> health = 20;
		newent -> velocity.x = 0;
		newent -> velocity.y = 0;
		newent -> maxspeed = 0;
		newent -> movespeed = 0;
		newent -> accel = 0;
		newent -> state = 0;
		newent -> timer = 0;
		break;
	case 2:
		strcpy(newent->type,"type2");
		slog("Enemy type 2 is being drawn");
		newent->sprite = loadSprite("images/enemy2.png",16,32,1);
		newent -> bounds.x = 0;
		newent -> bounds.y = 0;
		newent -> bounds.w = 16;
		newent -> bounds.h = 32;
		newent -> maxhealth = 20;
		newent -> health = 20;
		newent -> velocity.x = 0;
		newent -> velocity.y = 0;
		newent -> maxspeed = 0;
		newent -> movespeed = 0;
		newent -> accel = 0;
		newent -> state = 0;
		newent -> timer = 0;
		break;
	case 3:
		strcpy(newent->type,"type3");
		newent->sprite = loadSprite("images/enemy3.png",32,22,1);
		newent -> bounds.x = 0;
		newent -> bounds.y = 0;
		newent -> bounds.w = 32;
		newent -> bounds.h = 22;
		newent -> maxhealth = 20;
		newent -> health = 20;
		newent -> velocity.x = 0;
		newent -> velocity.y = 0;
		newent -> maxspeed = 1;
		newent -> movespeed = 0;
		newent -> accel = 1;
		newent -> state = 0;
		newent -> timer = 0;
		break;
	case 4:
		strcpy(newent->type,"type4");
		newent->sprite = loadSprite("images/boss.png",121,135,1);
		newent -> bounds.x = 0;
		newent -> bounds.y = 0;
		newent -> bounds.w = 121;
		newent -> bounds.h = 135;
		newent -> maxhealth = 150;
		newent -> health = 150;
		newent -> velocity.x = 0;
		newent -> velocity.y = 0;
		newent -> maxspeed = 0;
		newent -> movespeed = 0;
		newent -> accel = 0;
		newent -> state = 0;
		newent -> timer = 0;
		newent -> switcher = 0;
		newent -> bulletTimer2 = 3000;

	}
	newent -> cameraEnt = 1;
	newent -> frame = 0;
	newent -> position.x = x;
	newent -> position.y = y;
	newent -> lastPosition.x = newent-> position.x;
	newent -> lastPosition.y = newent -> position.y;
	TheEnemy = newent;
	return newent;
}

void UpdateEnemy(Entity *self, int type)
{
	self -> lastPosition = self-> position;
	if(self-> health <= 0)
	{
		entity_free(self);
	}
	switch(type)
	{
		//Standard stationary shooter type enemy
		case 1:
			if(self-> bulletTimer <= 0)
			{
				SpawnEnemyBullet(self,self->position.x,self->position.y,0,8,2, 10,1,2);//TODO: change for enemy bullets`
				self-> bulletTimer = 1250;
			}
			if(self-> bulletTimer >=  0)
			{
				self -> bulletTimer -= deltaTime;
			}
			self->position.y += 2;
			//Entity *SpawnEnemyBullet(Entity *owner,int sx,int sy,float angle,float speed,float accel, int damage,int type)
			//SpawnEnemyBullet(self,self->position.x,self->position.y,0,8,2, 10,1);
			break;
		//Flamethrower type enemy
		case 2:
			if(self-> bulletTimer <= 0)
			{
				SpawnEnemyBullet(self,self->position.x,self->position.y,0,8,2, 5,2,3);//TODO: change for enemy bullets`
				self-> bulletTimer = 50;
			}
			if(self-> bulletTimer >=  0)
			{
				self -> bulletTimer -= deltaTime;
			}
			self->position.y += 2;
			//SpawnEnemyBullet(self,self->position.x,self->position.y,0,8,2, 10,2);
			break;
		//Flying type enemy
		case 3:
			self->velocity.x -= self->accel;
			self->movespeed = VectorLength(self->velocity.x,self->velocity.y);
			//self->grounded = 0;
			if(self->movespeed > self->maxspeed)
			{
				self->velocity.y = 0;
				self->velocity.x = self->maxspeed * -1;
				self->movespeed = self->maxspeed;
			}
			self->position.x += self->velocity.x;
			if(self-> bulletTimer <= 0)
			{
				SpawnEnemyBullet(self,self->position.x,self->position.y,0,8,2, 10,3,4); //TODO: change for enemy bullets
				self-> bulletTimer = 750;
			}
			if(self-> bulletTimer >=  0)
			{
				self -> bulletTimer -= deltaTime;
			}
			break;
		//Boss type enemy
		case 4:
			if(self -> switcher == 0)
			{
				if(self-> bulletTimer <= 0)
				{
					SpawnEnemyBullet(self,self->position.x,self->position.y +10,0,8,2, 10,4,5);//TODO: change for enemy bullets`
					self-> bulletTimer = 750;
				}
				if(self-> bulletTimer >=  0)
				{
					self -> bulletTimer -= deltaTime;
				}
			}
			if(self -> switcher == 1)
			{
				if(self-> bulletTimer <= 0)
				{
					SpawnEnemyBullet(self,self->position.x,self->position.y + 110,0,8,2, 10,4,5);//TODO: change for enemy bullets`
					self-> bulletTimer = 750;
				}
				if(self-> bulletTimer >=  0)
				{
					self -> bulletTimer -= deltaTime;
				}
			}
			if(self -> bulletTimer2 >= 0)
			{
				self -> bulletTimer2 -= deltaTime;
			}
			if(self -> bulletTimer2 <= 0)
			{
				self -> bulletTimer2 = 3000;
				if(self-> switcher == 0)
				{
					self -> switcher = 1;
					break;
				}
				if(self-> switcher == 1)
				{
					self -> switcher = 0;
					break;
				}
			}
			self->position.y += 2;
			break;
	}
}
