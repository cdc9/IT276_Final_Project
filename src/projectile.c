#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "entity.h"
#include "simple_logger.h"
#include "camera.h"
#include "player.h"

extern int deltaTime;

Entity *SpawnProjectile(int sx,int sy,float angle,float speed,float accel,int damage)
{
	//float cosine, sine;
	Entity *newent = NULL;
	newent = entity_new(); 
	if (newent == NULL)
	{
		fprintf(stderr, "Unable to generate player entity; %s", SDL_GetError());
		exit(0);
	}
	strcpy(newent->name,"Projectile");
	//newent->sprite = loadSprite("images/bullet.png",9,9,1);
	newent -> frameW = 9;	//TODO: make sure that this is always accurate
	newent -> frameH - 9;
	newent -> bounds.x = 9;
	newent -> bounds.y = 9;
	newent -> damage = damage;
	newent -> cameraEnt = 1;
	newent -> position.x  = sx;
	newent -> position.y = sy;
	newent -> velocity.x = speed;
	newent -> velocity.y = speed;
	if(accel != 0)
	{
		newent -> velocity.x = speed;
		newent -> velocity.y = speed;
		newent -> accel = accel;
	}
	newent -> movespeed = (int)speed;
	newent -> maxspeed = (int)speed;
	return newent;
}
Entity *SpawnBullet(Entity *owner,int sx,int sy,float angle,float speed,float accel, int damage,int powerup)
{
	Entity *newent = NULL;
	newent = SpawnProjectile(sx,sy,angle,speed,accel,damage);
	if(newent == NULL)
	{
		slog("This bullet has not been created!!");
		return NULL;
	}
	newent -> frame = 0;
	newent -> frate = 30;
	newent -> timer = 2000;
	switch(powerup)
	{
		case 0:
			newent->sprite = loadSprite("images/bullet.png",9,9,1);
			newent -> offset.x = 18;
			newent -> offset.y = 12;
			newent -> bounds.x = 1;
			newent -> bounds.y = 1;
			newent -> bounds.w = 9;
			newent -> bounds.h = 9;
			break;
		case 1:
			newent->sprite = loadSprite("images/bigbullet.png",16,16,1);
			newent -> offset.x = 18;
			newent -> offset.y = 12;
			newent -> bounds.x = 1;
			newent -> bounds.y = 1;
			newent -> bounds.w = 16;
			newent -> bounds.h = 16;
			break;
		case 2:
			newent->sprite = loadSprite("images/firebullet.png",17,10,1);
			newent -> offset.x = 18;
			newent -> offset.y = 12;
			newent -> bounds.x = 1;
			newent -> bounds.y = 1;
			newent -> bounds.w = 17;
			newent -> bounds.h = 10;
			break;
		case 3:
			newent->sprite = loadSprite("images/bluefirebullet.png",30,16,1);
			newent -> offset.x = 18;
			newent -> offset.y = 12;
			newent -> bounds.x = 1;
			newent -> bounds.y = 1;
			newent -> bounds.w = 30;
			newent -> bounds.h = 16;
			break;
		default:
			newent->sprite = loadSprite("images/bullet.png",9,9,1);
			newent -> offset.x = 18;
			newent -> offset.y = 12;
			newent -> bounds.x = 1;
			newent -> bounds.y = 1;
			newent -> bounds.w = 9;
			newent -> bounds.h = 9;
			break;
	}
//	newent -> update = UpdateBullet;
//	newent -> think = BulletThink;
	return newent;

}

void UpdateBullet(Entity *self)
{
	Entity *target = NULL;
	if(self -> timer > 0)
	{
		self-> timer -= deltaTime;
	}
	if(self-> timer <= 0)
	{
		entity_free(self);
		slog("bullet has been freed");
	}
	self->velocity.x += self->accel;
	self->movespeed = VectorLength(self->velocity.x,self->velocity.y);
		//self->grounded = 0;
		if(self->movespeed > self->maxspeed)
		{
			self->velocity.y = 0;
			self->velocity.x = self->maxspeed;
			self->movespeed = self->maxspeed;
		}
		self->position.x += self->velocity.x;
		//slog("This is is working");
	//self->position.y += self->velocity.y; <- y movement which will come later
}
void BulletThink(Entity *self)
{
	UpdateBullet(self);
}
/*
	GetFace(owner);
	//Getting the correct offset to shoot from depending on where the player is facing
	if(owner -> face == F_East || owner -> face == F_NE || owner -> face == F_SE)
	{
		newent-> offset.x = owner->position.x + 10; 
		newent -> movespeed = speed;
	}
	if(owner -> face == F_West || owner -> face == F_NW || owner -> face == F_SW)
	{
		newent-> offset.x = owner->position.x - 2;
		newent -> movespeed = speed * -1;
	}
	if(owner -> face == F_NE)
	{
		newent -> offset.y = owner -> position.y - 2; 
	}
	if(owner -> face == F_SE)
	{
		newent -> offset.y = owner -> position.y + 2; 
	}
	if(owner -> face == F_NW)
	{
		newent -> offset.y = owner -> position.y - 2; 
	}
	if(owner -> face == F_SW)
	{
		newent -> offset.y = owner -> position.y + 2; 
	}

*/