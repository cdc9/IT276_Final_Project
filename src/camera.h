#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <SDL.h>
#include "vector.h"

/**
 * @brief return the current camera
 */
SDL_Rect camera_get_active_camera();
/**
 * @brief Get the position of the camera
 */
Vec2d camera_get_position();
/**
 * @brief Set the position of the camera
 * @param vector postion of where you want to set the x and y of your camera
 */
void camera_set_position(Vec2d pos);
/**
 * @brief Set the size of the camera
 * @param size the width and height of the camera must be set.
 */
void camera_set_size(Vec2d size);
/**
 * @brief Get the size of the camera
 */
Vec2d camera_get_size();



#endif
