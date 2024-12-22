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
auto main(int argc, char **argv) -> int {
  entt::registry registry;

  // Create a planet
  const auto entity = registry.create();
  const auto plantetPositionX = 100.0F;
  const auto plantetPositionY = 100.0F;
  const auto planetColor = RED;
  const auto planetWidth = 3;
  registry.emplace<position>(entity, plantetPositionX, plantetPositionY);
  registry.emplace<sprite>(entity, planetColor, planetWidth);

  // Create a sun
  const auto sun = registry.create();
  const auto sunPositionX = 400.0F;
  const auto sunPositionY = 225.0F;
  const auto sunColor = YELLOW;
  const auto sunWidth = 10;
  registry.emplace<position>(sun, sunPositionX, sunPositionY);
  registry.emplace<sprite>(sun, sunColor, sunWidth);

  // Initialize the window
  const auto screenWidth = 800;
  const auto screenHeight = 800;
  const auto *const screenTitle = "Alaankwa Corsairs";
  InitWindow(screenWidth, screenHeight, screenTitle);

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
