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

            tiles[x][y] = new Tile();

        }

    }

}

void Game::update()
{

    player->update();

    for (Entity* entity : entities) {

        entity->update(this);

    }

}

void Game::render()
{

    camera->BeginMode();
    window->ClearBackground(raylib::Color(0, 0, 0, 255));

    player->render();

    // Smooth camera towards player
    camera->target = (player->getPosition2D() - camera->target) * 0.1 + camera->target;

    for (Entity* entity : entities) {

        entity->render();

    }

    window->EndDrawing();

}

bool Game::shouldClose()
{

    return window->ShouldClose();

}
