#include "Game.hpp"
#include "Player.hpp"
#include "Entity.hpp"

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
    this->addEntity(player);

    for (int x = 0; x < MAP_WIDTH; x++) {

        for (int y = 0; y < MAP_WIDTH; y++) {

            tiles[x][y] = TileType::GRASS;

        }

    }

}

void Game::update()
{

    for (Entity* entity : entities) {

        entity->physics_update(this);

    }

    // Resolve collisions
    for (Entity* entity : entities) {

        for (Entity* other : entities) {

            if (entity != other) {

                if (entity->collidesWith(other)) {

                    entity->doCollision(other);

                }

            }

        }

    }

    for (Entity* entity : entities) {

        entity->update(this);

    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

        std::vector<Entity*> entities_at_position = getEntitiesAtPosition(this);

        for (Entity* entity : entities_at_position) {

            entity->onMousePressed(this, MouseButton::MOUSE_BUTTON_LEFT);

        }

    }

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {

        std::vector<Entity*> entities_at_position = getEntitiesAtPosition(this);

        for (Entity* entity : entities_at_position) {

            entity->onMouseReleased(this, MouseButton::MOUSE_BUTTON_LEFT);

        }

    }

}

void Game::render()
{

    // TODO: Move to new function
    if(window->IsResized()) {

        camera->target = raylib::Vector2(window->GetWidth() / 2.0f, window->GetHeight() / 2.0f);
        camera->offset = raylib::Vector2(window->GetWidth() / 2.0f, window->GetHeight() / 2.0f);

    }

    camera->BeginMode();
    window->ClearBackground(raylib::Color(0, 0, 0, 255));

    for (int x = 0; x < MAP_WIDTH; x++) {

        for (int y = 0; y < MAP_WIDTH; y++) {

            raylib::Color color = raylib::Color(0, 0, 0, 255);
            // TODO: Move drawing tiles to a seperate function
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

    // Smooth camera towards player
    camera->target = (player->getPosition() - camera->target) * 0.1 + camera->target;

    std::vector<Entity*> sort_entities = this->entities;
    // Sort by z index
    std::sort(sort_entities.begin(), sort_entities.end(), [](Entity* a, Entity* b) { return a->getZIndex() < b->getZIndex(); });
    // TODO: Move to new function Maybe?
    for (Entity* entity : sort_entities) {

        entity->render();

    }

    window->EndDrawing();

}

raylib::Vector2 Game::getMousePosition()
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

std::vector<Entity*> Game::getEntitiesAtPosition(Game* game)
{

    std::vector<Entity*> entities_at_position;

    for (Entity* entity : entities) {

        if (entity->contains(game->getMousePosition())) {

            entities_at_position.push_back(entity);

        }

    }

    return entities_at_position;

}