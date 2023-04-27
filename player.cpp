/* player.cpp
 * 
 * Implements the player class.
 * 
 * @author Alex Wills
 * @author Jhonder Abreus
 * @date April 7, 2023
 */
#include "player.h"
#include "Time.h"


Player::Player(sf::RenderWindow * window, sf::Texture * texture): Entity(window, texture, 300, 1000) {
    // Set the origin to the middle of the sprite's feet
    sprite.setOrigin(38, 132);

    // Set initial score and health
    score = 10;
    health = 5;
    frameCounter = 0;
    speed = 50;
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

void Player::DecreaseScore(int change)
{
    this->score -= change;
}

int Player::GetHealth()
{
    return this->health;
}

void Player::ChangeHealth(int change)
{
    this->health += change;
}