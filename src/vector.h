#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdint.h>
#include <SDL.h>
/**
 * @brief a simple 2d vector structure
 */
typedef struct
{
    float x;    /**<the x component of the vector*/
    float y;    /**<the y component of the vector*/
}Vec2d;

/**
 * @brief a simple 3d vector structure
 */
typedef struct
{
    float x;/**<the x component of the vector*/
    float y;/**<the y component of the vector*/
    float z;/**<the z component of the vector*/
}Vec3d;

/**
 * @brief a simple 4d vector structure
 */
typedef struct
{
    float x; /**<the x component of the vector*/
    float y; /**<the y component of the vector*/
    float z; /**<the z component of the vector*/
    float w; /**<the w component of the vector*/
}Vec4d;

#define ZERO 0
/**
 * @brief A vec2d constructor
 * @param x The x position
 * @param y the y position
 */
Vec2d vec2d(float x,float y);
/**
 * @brief Used for vector math. Normalization stuff.
 * @param vx The velocity.x you want to use for vector math 
 * @param vy The velocity.y you want to use for vector math.
 */
int	VectorLength(float vx, float vy);   

#define vec2d_add(a,b,c) (c.x=a.x+b.x,c.y=a.y+b.y)
#define vec3d_add(a,b,c) (c.x=a.x+b.x,c.y=a.y+b.y,c.z=a.z+b.z)
#define vec4d_add(a,b,c) (c.x=a.x+b.x,c.y=a.y+b.y,c.z=a.z+b.z,c.w=a.w+b.w)


/**	
 * @brief check if two rectangles intersect
 * @param a The rectangle of the first entity
 * @param b The rectable of the second entity
 */
int  rect_intersect(SDL_Rect a,SDL_Rect b);
/**	
 * @brief A rectangle you can use for various things like bounding boxes or the camera.
 * @param x the x position
 * @param y the y position
 * @param w the w position
 * @param h the h position
 */
SDL_Rect rect(int x,int y,int w,int h);

#endif
