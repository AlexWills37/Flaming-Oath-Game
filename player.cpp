/* player.cpp
 * 
 * Implements the player class.
 * 
 * @author Alex Wills
 * @author Jhonder Abreus
 * @date April 7, 2023
 */
#include "player.h"
#include <cstdlib>
#include <iostream>


Player::Player(sf::RenderWindow * window, sf::Texture * texture, sf::Texture * fireTexture1): Entity(window, texture, 300, 1000) {
    // Set the origin to the middle of the sprite's feet
    sprite.setOrigin(38, 132);


    for (int i = 0; i < Player::maxFires1; ++i)
    {
        this->fires1[i] = WizardSpells(this->window, fireTexture1);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
        this->ShootFire();
    } 
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
void Player::ShootFire()
{
    // Find the first fire that is off screen and put it where the dragon is
    
    WizardSpells* newFire1 = nullptr;
    //DragonFire * firesound = nullptr;
    bool foundFire1 = false;
    for (int i = 0; i < Player::maxFires1 && !foundFire1; ++i)
    {
        // If fire is off screen, we can use it as a new fire
        if (this->fires1[i].offScreen1) {
            newFire1 = &(this->fires1[i]);
            foundFire1 = true;
        }
    }
    // If we found a fire that is off screen, we can have the dragon spit it out (move it to the dragon)
    if (foundFire1) {
        newFire1->offScreen1 = false;
        newFire1->sprite.setPosition(this->sprite.getPosition());    // Set the fire to the dragon's current position
    //delete firesound;
    //delete buffer1;

    // If we did not find a fire, then there are currently this->maxFires fires on screen, so we will not spit fire.
}
};

void Player::Draw1()
{
    // Draw the fires first
    for (int i = 0; i < this->maxFires1; ++i)
    {
        if (!this->fires1[i].offScreen1)  // Only draw fires that are on screen
        {
            this->fires1[i].Draw();
        }
    }
    
    // Draw the dragon last, so that it is on top of any fire
    //Entity::Draw();
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
/*
bool Player::CheckCollision1(Dragon * player1)
{
    //sf::SoundBuffer* buffer2 = new sf::SoundBuffer;
    //if (!buffer2->loadFromFile("./assets/music/hit sfx.wav"))
    //{
    //    std::cout<< "ERROR LOADING HIT"<<std::endl;
    //}
    //sf::Sound* hitsound = new sf::Sound;
    //hitsound->setBuffer(*buffer2);
    bool hit1 = false;
    int draghealth = 0;
    for (int i = 0; i < this->maxFires1; i++)
    {
        // Detect a collision
        if (!(this->fires1[i].offScreen1) && this->fires1[i].getGlobalBounds().intersects(Dragon->getGlobalBounds()))
        {
            hit1 = true;
            this->fires1[i].offScreen1 = true;
            //hitsound->play();
            //delete hitsound;
            //delete buffer2;
            draghealth = draghealth - 1;
        }
        std::cout<< draghealth;
    }
    return hit1;
}
*/
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