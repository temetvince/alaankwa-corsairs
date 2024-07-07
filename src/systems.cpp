#include "../include/systems.hpp"

/**
 * @brief Update the sprites
 * @param registry The registry containing the entities
 * @param delta The time since the last frame
 */
void updateSprites(entt::registry &registry, float delta) {
  auto view = registry.view<position, sprite>();

  for (auto entity : view) {
    auto &pos = view.get<position>(entity);
    auto &spr = view.get<sprite>(entity);

    DrawCircle(pos.x, pos.y, 10, spr.color);
  }
}

/**
 * @brief Update the positions
 * @param registry The registry containing the entities
 * @param delta The time since the last frame
 */
void updatePositions(entt::registry &registry, float delta) {
  auto view = registry.view<position, velocity>();

  for (auto entity : view) {
    auto &pos = view.get<position>(entity);
    auto &vel = view.get<velocity>(entity);

    pos.x = pos.x + vel.dx * delta;
    pos.y = pos.y + vel.dy * delta;
  }
}

/**
 * @brief Updates the entities in the registry.
 * @param registry The entity registry.
 * @param delta The time since the last update.
 */
void update(entt::registry &registry, float delta) {
  auto view = registry.view<const position, velocity>();

  // use a callback
  view.each([](const auto &pos, auto &vel) { /* ... */ });

  // use an extended callback
  view.each([](const auto entity, const auto &pos, auto &vel) { /* ... */ });

  // use a range-for
  for (auto [entity, pos, vel] : view.each()) {
    // ...
  }

  // use forward iterators and get only the components of interest
  for (auto entity : view) {
    auto &vel = view.get<velocity>(entity);
    // ...
  }

  updatePositions(registry, delta);
  updateSprites(registry, delta);
}
