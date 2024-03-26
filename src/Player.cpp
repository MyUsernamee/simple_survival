#include "Player.hpp"

void Player::update(Game* game) {

    Vector2 movement_vector = {0, 0};
    movement_vector.x = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
    movement_vector.y = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);

    velocity.x = movement_vector.x * this->movementSpeed;
    velocity.y = movement_vector.y * this->movementSpeed;

}

void Player::render() {

    // Draw a rectangle at the players position
    this->getBoundingBox().Draw(RED);

}

Player::Player()
{
    inventory = Inventory(8, 1);
    health = 100;
    size = Vector2{32, 32};
    frozen = false;
}