/* player.cpp
 * 
 * Implements the player class.
 */
#include "player.h"


Player::Player(sf::RenderWindow * window, sf::Texture * texture): Entity(window, texture, 300, 1000) {
    // Set the origin to the middle of the sprite's feet
    sprite.setOrigin(38, 132);

    // Set initial score and health
    score = 10;
    health = 10;
    frameCounter = 0;
}

void Player::Move(float x, float y) {

    // Flip player to face the direction they are moving
    if (x > 0) {
        sprite.setScale(1, 1);
    } else {
        sprite.setScale(-1, 1);
    }

    // Move player
    Entity::Move(x, y);
}

int Player::GetScore() {
    return this->score;
}

void Player::FrameUpdate() {
    frameCounter++;

    // Every 60 frames, increase the score by 1
    if (frameCounter >= 60) {
        this->score++;
        frameCounter = 0;
    }
}