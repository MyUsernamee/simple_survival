#include "Game.hpp"
#include "Player.hpp"
#include "Entity.hpp"

#include <algorithm>
#include <nlohmann/json.hpp>
#include <fstream>

#define TAU 6.28318530718

Game::Game()
{

    time = 0;
    days = 0;
    window = new raylib::Window(800, 450, "Game", FLAG_WINDOW_RESIZABLE);
    window->SetIcon(LoadImage("assets/dummy.png"));
    window->Maximize();
    window->SetTargetFPS(60);
    camera = new raylib::Camera2D(
        raylib::Vector2(window->GetWidth() / 2.0f, window->GetHeight() / 2.0f),
        raylib::Vector2(0.0f, 0.0f),
        0.0f,
        1.0f
    );

    player = new Player();
    this->addEntity(player);

    loadItems("assets/items.json");
    loadRecipes("assets/recipes.json");

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

            // If the entities to remove vector contains either entity or other, we skip the collision
            if (std::find(entities_to_remove.begin(), entities_to_remove.end(), entity) != entities_to_remove.end() || std::find(entities_to_remove.begin(), entities_to_remove.end(), other) != entities_to_remove.end()) {

                continue;

            }

            if (entity != other) {

                if (entity->collidesWith(other)) {

                    entity->doCollision(other);
                    entity->onCollision(this, other); // This can most likely segfault, it hasn't yet, but it probably will, so yea.
                    other->onCollision(this, entity);

                }

            }

        }

    }

    // We clone entities
    std::vector<Entity*> entities_ = this->entities;

    for (Entity* entity : entities_) {

        // If the entity is in the entities to remove vector, we skip the entity
        if (std::find(entities_to_remove.begin(), entities_to_remove.end(), entity) != entities_to_remove.end()) { // TODO: This is 100%
            // Slow and inefficient, we should definetly use a set or store some data in the entity to make this faster

            continue;

        }

        entity->update(this);

    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

        std::vector<Entity*> entities_at_position = getEntitiesAtMousePosition();

        for (Entity* entity : entities_at_position) {

            entity->onMousePressed(this, MouseButton::MOUSE_BUTTON_LEFT);

        }

    }

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {

        std::vector<Entity*> entities_at_position = getEntitiesAtMousePosition();

        for (Entity* entity : entities_at_position) {

            entity->onMouseReleased(this, MouseButton::MOUSE_BUTTON_LEFT);

        }

    }

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {

        std::vector<Entity*> entities_at_position = getEntitiesAtMousePosition();

        for (Entity* entity : entities_at_position) {

            entity->onMousePressed(this, MouseButton::MOUSE_BUTTON_RIGHT);

        }

    }

    if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON)) {

        std::vector<Entity*> entities_at_position = getEntitiesAtMousePosition();

        for (Entity* entity : entities_at_position) {

            entity->onMouseReleased(this, MouseButton::MOUSE_BUTTON_RIGHT);

        }

    }

    time += getDeltaTime();
    if (time >= 1.0) {

        time = 0;
        days++;

    }

    doEntityVectorModification();

}

void Game::render()
{

    window->BeginDrawing();

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

            DrawRectangle(x * 16 - MAP_WIDTH * 8, y * 16 - MAP_WIDTH * 8, 16, 16, color);

        }

    }

    camera->EndMode();

    DrawFPS(0, 0);

    // Draw a large rectangle to make everything darker based on time of day
    DrawRectangle(0, 0, window->GetWidth(), window->GetHeight(), raylib::Color(0, 0, 0, std::max(std::sin(getDayProgress() * TAU) * 0.5 + 0.5, 0.0) * 255));

    camera->BeginMode();

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

    entities_to_remove.push_back(entity);

}

std::vector<Entity*> Game::getEntitiesAtMousePosition()
{

    std::vector<Entity*> entities_at_position;

    for (Entity* entity : entities) {

        if (entity->contains(this->getMousePosition())) { // TODO: DRY CODE FIX ME

            entities_at_position.push_back(entity);

        }

    }

    return entities_at_position;

}

std::vector<Entity*> Game::getEntitiesAtPosition(raylib::Vector2 position)
{

    std::vector<Entity*> entities_at_position;

    for (Entity* entity : entities) {

        if (entity->contains(position)) {

            entities_at_position.push_back(entity);

        }

    }

    return entities_at_position;

}

void Game::addEntity(Entity* entity)
{

    entities_to_add.push_back(entity);
    entity->setGame(this);

}

void Game::doEntityVectorModification()
{

    // Actually do adds and removes of the entities
    for (Entity* entity : entities_to_add) {

        entities.push_back(entity);

    }

    for (Entity* entity : entities_to_remove) {

        entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());

    }

    entities_to_add.clear();
    entities_to_remove.clear();

}

void Game::loadItems(const char* filename) {

    std::ifstream file(filename);
    nlohmann::json json = nlohmann::json::parse(file);

    TraceLog(LOG_INFO, "Loading items from %s", filename);
    TraceLog(LOG_INFO, "Loaded %d items", json.size());

    for (nlohmann::json item : json) {

        TraceLog(LOG_INFO, "Loading item %s", item["name"].template get<std::string>().c_str());

        Item item_ = Item(item["id"].template get<std::string>(), item["name"].template get<std::string>(), "", item["texture"].template get<std::string>().c_str());
        this->registerItem(item_);

    }

}

void Game::loadRecipes(const char* filename) {

    std::ifstream file(filename);
    nlohmann::json json = nlohmann::json::parse(file);

    TraceLog(LOG_INFO, "Loading recipes from %s", filename);
    TraceLog(LOG_INFO, "Loaded %d recipes", json.size());

    /*
    
        Exmaple recipe json:

        [
            {
                "ingredients": [
                    {"id": "wood", "count": 2}
                ],
                "result": {"id": "stick", "count": 4}
            }
        ]
    
    */

    for (nlohmann::json recipe : json) {

        std::vector<Slot> ingredients;

        for (nlohmann::json ingredient : recipe["ingredients"]) {

            // Find the item by id
            Item& item = this->getItem(ingredient["id"].template get<std::string>());
            Slot slot = Slot(item, ingredient["count"].template get<int>());

            ingredients.push_back(slot);

        }

        Recipe recipe_ = Recipe(ingredients, Slot(this->getItem(recipe["result"]["id"].template get<std::string>()), recipe["result"]["count"].template get<int>()));
        this->registerRecipe(recipe_);

    }

    TraceLog(LOG_INFO, "Loaded %d recipes", this->getRecipes().size());


}