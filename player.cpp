#include "player.h"

#include <iostream>

Player::Player() {
    // Set up texture and sprite
    texture.loadFromFile("./assets/sprites/WizardSprite.png");
    sprite.setTexture(texture, true);
    sprite.setPosition(300, 1000);
    sprite.setOrigin(38, 132);

    score = 10;
    health = 10;
    frameCounter = 0;
}

void Player::MovePlayer(float x, float y) {

    // Flip player to face the direction they are moving
    if (x > 0) {
        sprite.setScale(1, 1);
    } else {
        sprite.setScale(-1, 1);
    }

    // Move player
    sprite.move(x, y);
}

int Player::GetScore() {
    return this->score;
}

void Player::FrameUpdate() {
    frameCounter++;

    if (frameCounter >= 60) {
        this->score++;
        frameCounter = 0;
    }
}