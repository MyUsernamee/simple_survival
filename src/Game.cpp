#include "Game.hpp"

#include <algorithm>

Game::Game()
{

    window = new raylib::Window(800, 450, "Game", FLAG_WINDOW_RESIZABLE);
    window->Maximize();
    camera = new raylib::Camera2D(
        raylib::Vector2(window->GetWidth() / 2.0f, window->GetHeight() / 2.0f),
        raylib::Vector2(0.0f, 0.0f),
        0.0f,
        1.0f
    );

    player = new Player();

    for (int x = 0; x < MAP_WIDTH; x++) {

        for (int y = 0; y < MAP_WIDTH; y++) {

            tiles[x][y] = TileType::GRASS;

        }

    }

}

void Game::update()
{

    for (Entity* entity : entities) {

        entity->update(this);

    }

}

void Game::render()
{

    if(window->IsResized()) {

        camera->target = raylib::Vector2(window->GetWidth() / 2.0f, window->GetHeight() / 2.0f);
        camera->offset = raylib::Vector2(window->GetWidth() / 2.0f, window->GetHeight() / 2.0f);

    }

    camera->BeginMode();
    window->ClearBackground(raylib::Color(0, 0, 0, 255));

    for (int x = 0; x < MAP_WIDTH; x++) {

        for (int y = 0; y < MAP_WIDTH; y++) {

            raylib::Color color = raylib::Color(0, 0, 0, 255);

            switch (tiles[x][y]) {

                case TileType::GRASS:
                    color = GRASS_COLOR; // TODO: Replace with grass texture
                    break;

                case TileType::DIRT:
                    color = DIRT_COLOR;
                    break;

                case TileType::WATER:
                    color = WATER_COLOR;    
                    break;

            }

            DrawRectangle(x * 16, y * 16, 16, 16, color);

        }

    }

    // Draw the position of the player
    raylib::DrawText(std::to_string(player->getPosition2D().x), 10, 10, 20, raylib::Color(255, 255, 255, 255));
    raylib::DrawText(std::to_string(player->getPosition2D().y), 10, 30, 20, raylib::Color(255, 255, 255, 255));

    // Smooth camera towards player
    camera->target = (player->getPosition2D() - camera->target) * 0.1 + camera->target;

    // Sort entities by z
    std::sort(entities.begin(), entities.end(), [](Entity* a, Entity* b) { return a->getZIndex() < b->getZIndex(); });

    for (Entity* entity : entities) {

        entity->render();

    }

    window->EndDrawing();

}

Vector2 Game::getMousePosition()
{

    return camera->GetScreenToWorld(GetMousePosition());

}

bool Game::shouldClose()
{

    return window->ShouldClose();

}

void Game::removeEntity(Entity* entity)
{

    for (int i = 0; i < entities.size(); i++) {

        if (entities[i] == entity) {

            entities.erase(entities.begin() + i);
            return;

        }

    }

}