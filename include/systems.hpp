#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include "components.hpp"

#include <entt.hpp>
#include <raylib.h>

/**
 * @brief Updates the entities in the registry.
 * @param registry The entity registry.
 * @param delta The time since the last update.
 */
void update(entt::registry& registry, float delta);

#endif // SYSTEMS_HPP
