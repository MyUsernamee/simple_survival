#include "Zombie.hpp"
#include "Mob.hpp"
#include "Game.hpp"
#include "Player.hpp"

Zombie::Zombie(raylib::Vector2 position) : Mob(position, raylib::Vector2(32, 32), 1.0) {
    
    this->health = 100;

}

void Zombie::update_movement(Game* game) {
    // Move towards the player
    Player* player = game->getPlayer();
    raylib::Vector2 player_position = player->getPosition();
    raylib::Vector2 direction = player_position - this->getPosition();
    direction = direction.Normalize();
    this->move(direction);
}

void Zombie::render() {
    this->getBoundingBox().Draw(RED);

    // Draw the health
    raylib::Vector2 position = this->getPosition();
    raylib::Vector2 size = this->getSize();
    raylib::Vector2 health_position = position + raylib::Vector2(0, size.y + 5);
    DrawText(std::to_string(this->getHealth()).c_str(), health_position.x, health_position.y, 10, WHITE);



}

void Zombie::onDeath(Game* game) {
    game->removeEntity(this);
}