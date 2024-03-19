#include "Player.hpp"

void Player::update() {

    // Update side to side velocity
    velocity.x = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
    velocity.y = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);


    // TODO: Replace with player speed.
    velocity.x *= 3;
    velocity.y *= 3;

    if (position.z == 0.0 && IsKeyDown(KEY_SPACE)) {

        // Gravity TODO: Replace with player jump height
        velocity.z = -3;

    }

    // Update position
    position.x += velocity.x;
    position.y += velocity.y;
    position.z += velocity.z;

    velocity.z += 0.4;

    // Collision detection
    if (position.z > 0.0) {

        position.z = 0.0;
        velocity.z = 0.0;

    }

}

void Player::render()
{

    DrawRectangle(position.x - 20,
        position.y + position.z - 20,
        40,
        40,
        raylib::Color(255, 0, 0, 255)); // TODO: Replace with sprite and add animation

}

Player::Player()
{
    position = raylib::Vector3(0, 0, 0);
    velocity = raylib::Vector3(0, 0, 0);
}