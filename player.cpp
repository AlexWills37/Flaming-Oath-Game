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
#include "InputManager.h"
#include <iostream>


Player::Player(sf::RenderWindow * window, sf::Texture * texture, HealthBar * healthBar)
    : LivingEntity(window, texture, 300, 1000, healthBar) {
    // Set the origin to the middle of the sprite's feet
    sprite.setOrigin(38, 132);

    // Set initial score and speed
    score = 10;
    frameCounter = 0;
    speed = 850;
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


void Player::Update() {
    float deltaTime = Time::GetInstance()->DeltaTime();
    InputManager* input = InputManager::GetInputManager();
    bool movingLeft, movingRight;

    
    // Handle user inputs
    if (input->IsKeyPressed(sf::Keyboard::A)) {
        movingLeft = true;
    } else {
        movingLeft = false;
    }

    if (input->IsKeyPressed(sf::Keyboard::D)) {
        movingRight = true;
    } else {
        movingRight = false;
    }

    if (movingLeft && !movingRight)
    {
        this->Move(-speed * deltaTime, 0);
    } else if (movingRight && !movingLeft) {
        this->Move(speed * deltaTime, 0);
    }


}