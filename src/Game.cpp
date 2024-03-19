#include "Game.hpp"

Game::Game()
{

    window = new raylib::Window(800, 450, "Game");
    window->SetTargetFPS(60);
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

    player->update(this);

    for (Entity* entity : entities) {

        entity->update(this);

    }

}

void Game::render()
{

    camera->BeginMode();
    window->ClearBackground(raylib::Color(0, 0, 0, 255));

    for (int x = 0; x < MAP_WIDTH; x++) {

        for (int y = 0; y < MAP_WIDTH; y++) {

            raylib::Color color = raylib::Color(0, 0, 0, 255);

            switch (tiles[x][y]) {

                case TileType::GRASS:
                    color = raylib::Color(0, 255, 0, 255);
                    break;

                case TileType::DIRT:
                    color = raylib::Color(255, 255, 0, 255);
                    break;

                case TileType::WATER:
                    color = raylib::Color(0, 0, 255, 255);
                    break;

            }

            DrawRectangle(x * 16, y * 16, 16, 16, color);

        }

    }
    player->render(this);

    // Draw the position of the player
    raylib::DrawText(std::to_string(player->getPosition2D().x), 10, 10, 20, raylib::Color(255, 255, 255, 255));
    raylib::DrawText(std::to_string(player->getPosition2D().y), 10, 30, 20, raylib::Color(255, 255, 255, 255));

    // Smooth camera towards player
    camera->target = (player->getPosition2D() - camera->target) * 0.1 + camera->target;

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
