#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <raylib.h>

/**
 * @brief Struct representing the position of an entity.
 */
struct position {
  float x; /**< The x-coordinate of the position. */
  float y; /**< The y-coordinate of the position. */
};

/**
 * @brief Struct representing the velocity of an entity.
 */
struct velocity {
  float dx; /**< The velocity in the x-direction. */
  float dy; /**< The velocity in the y-direction. */
};

/**
 * @brief Struct representing the sprite of an entity.
 */
struct sprite {
  Color color; /**< The color of the sprite. */
  int width;   /**< The width of the sprite. */
};

// You can add more components here as needed

#endif // COMPONENTS_H
