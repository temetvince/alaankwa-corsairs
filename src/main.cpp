#include "../include/components.hpp"
#include "../include/systems.hpp"

#include <entt.hpp>
#include <raylib.h>

#include <iostream>

/**
 * @brief The main function.
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 * @return The exit status of the program.
 */
int main(int argc, char **argv) {
  entt::registry registry;

  // Create an entity with a position component
  auto entity = registry.create();
  registry.emplace<position>(entity, 100.0f, 100.0f);
  registry.emplace<sprite>(entity, RED, 3);

  // Create a Sun
  auto sun = registry.create();
  registry.emplace<position>(sun, 400.0f, 225.0f);
  registry.emplace<sprite>(sun, YELLOW, 10);

  InitWindow(800, 800, "Alaankwa Corsairs");

  while (!WindowShouldClose()) {
    auto delta = GetFrameTime();

    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();

    update(registry, delta);
  }

  CloseWindow();

  return 0;
}
