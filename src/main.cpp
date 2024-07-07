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
int main(int argc, char** argv)
{
    entt::registry registry;

    // Create 10 entities with a position component and a velocity component for every even entity
    for(auto i = 0u; i < 10u; ++i) {
        const auto entity = registry.create();
        registry.emplace<position>(entity, i * 1.f, i * 1.f);
        if(i % 2 == 0) { registry.emplace<velocity>(entity, i * 1.0f, i * 1.0f); }
    }    

    // For each entity with a position component, add a sprite component
    registry.view<position>().each([&registry](const auto entity, const auto &pos) {
        registry.emplace<sprite>(entity, RED);
    });

    InitWindow(800, 450, "raylib [core] example - basic window");
    
    while (!WindowShouldClose())
    {
        auto delta = GetFrameTime();
        std::cout << delta << std::endl;
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();

        update(registry, delta);
    }

    CloseWindow();

    return 0;
}
