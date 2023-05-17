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
#include "Level.h"
#include "InputManager.h"
#include <iostream>
//#pragma once

class Dragon;
// FIX ADD FIRE TEXTURE
Player::Player(sf::RenderWindow * window, sf::Texture * texture, HealthBar * healthBar, sf::Texture * fireTexture1, sf::Texture * healSpell)
    : LivingEntity(window, texture, 300, 1000, healthBar) {
    // Set the origin to the middle of the sprite's feet
    sprite.setOrigin(38, 132);

    // Set initial score and speed
    

    // Initialize spells
    if (CastSpell(), true) {
        std::cout<< "fire";
        for (int i = 0; i < Player::maxSpells; ++i)
    {
        this->spells[i] = WizardSpells(this->window, fireTexture1);
    }
    }
    if (CastHeal(), true) {
        std::cout<< "heal";
        for (int i = 0; i < Player::maxSpells2; ++i)
    {
        this->spells2[i] = WizardSpells(this->window, healSpell);
    }    
    }
    
    /*
    This makes a dragon pointer in the player so that we can do the collision.
    */
    this->dragon = dragon;

    /*
    Here are the frame counter for spell cooldown, the player speed, and a pointer for the healthbar to follow the player
    */
    score = 10;
    frameCounter = 0;
    counter = 0;
    speed = 850;
    this->EnableFollowingHealthBar(sf::Vector2f(-75, -200));
}

/*
*A function to give the player a dragon object for the collision without depedency.
*/
void Player::setDragon(Dragon * dragon) {
    this->dragon = dragon;
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
void Player::CastSpell()
{
    // Find the first fire that is off screen and put it where the player is
    
    WizardSpells* newFire1 = nullptr;
    bool foundFire1 = false;
    for (int i = 0; i < Player::maxSpells && !foundFire1; ++i)
    {
        // If fire is off screen, we can use it as a new fire
        if (this->spells[i].offScreen1) {
            newFire1 = &(this->spells[i]);
            foundFire1 = true;
        }
    }
    // If we found a fire that is off screen, we can have the player shoot it out (move it to the dragon)
    if (foundFire1) {
        newFire1->offScreen1 = false;
        newFire1->sprite.setPosition(this->sprite.getPosition());    // Set the fire to the players's current position
    //delete firesound;
    //delete buffer1;

    // If we did not find a fire, then there are currently this->maxFires fires on screen, so we will not shoot fire.
    }
};

void Player:: CastHeal()
{
    // Find the first heal that is off screen and put it where the player is
    
    WizardSpells* newHeal = nullptr;
    bool foundHeal = false;
    for (int i = 0; i < Player::maxSpells2 && !foundHeal; ++i)
    {
        // If heal is off screen, we can use it as a new heal
        if (this->spells2[i].offScreen1) {
            newHeal = &(this->spells2[i]);
            foundHeal = true;
        }
    }
    // If we found a heal that is off screen, we can have the player shoot it out (move it to the dragon)
    if (foundHeal) {
        newHeal->offScreen1 = false;
        newHeal->sprite.setPosition(this->sprite.getPosition());    // Set the heal to the players's current position

    // If we did not find a heal, then there are currently this->maxFires fires on screen, so we will not shoot heal.
    }
}


void Player::Draw()
{
    // Draw the fires first
    for (int i = 0; i < this->maxSpells; ++i)
    {
        if (!this->spells[i].offScreen1)  // Only draw fires that are on screen
        {
            this->spells[i].Draw();
        }
    }
    // Draw the heals next
    for (int i = 0; i < this->maxSpells2; ++i) {
    if (!this->spells2[i].offScreen1)   // Only draw the heals that are on screen
        {
            this->spells2[i].Draw();           
        }
    }

    
    
    
    // Draw the player and health last, so that it is on top of any fire or heals
    LivingEntity::Draw();
}

int Player::GetScore() {
    return this->score;
}

/*
*A Function to keep spell cooldown separate from game frame rate
*/
int Player::FrameUpdate() {
    frameCounter++;
return frameCounter;
}

void Player::DecreaseScore(int change)
{
    this->score -= change;
}

/*
*Updates the player with delta time. Takes user input and moves player. Also shoots spells
*/
void Player::Update() {
    float deltaTime = Time::GetInstance()->DeltaTime();
    InputManager* input = InputManager::GetInputManager();
    bool movingLeft, movingRight;

    
    // Handle user inputs
    // Movement
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

    // Casting spells
    if ((FrameUpdate() % 10 == 0) && input->IsKeyPressed(sf::Keyboard::J)) {
        this->CastSpell();
    }
    if (input->IsKeyPressed(sf::Keyboard::K)) {
        this->CastHeal();
    }

    // Move all spells up
    for (int i = 0; i < Player::maxSpells; i++) {
        if (!this->spells[i].offScreen1) {
            this->spells[i].MoveUp();
        }
    }
    for (int i = 0; i < Player::maxSpells2; i++) {
        if (!this->spells2[i].offScreen1) {
            this->spells2[i].MoveUp();
        }
    }
    
    /*
    This check collision with a dragon object and see if any of the spell sprites intersects with the dragon sprite.
    */
    for (int i = 0; i < this->maxSpells; i++){
        if (!(this->spells[i].offScreen1) && this->spells[i].getGlobalBounds().intersects(dragon->getGlobalBounds()))
        {
            dragon->ChangeHealth(-1);
            this->spells[i].offScreen1 = true;
          
        }
    }

    for (int i = 0; i < this->maxSpells; i++){
        if (!(this->spells2[i].offScreen1) && this->spells2[i].getGlobalBounds().intersects(dragon->getGlobalBounds()))
        {
            this->ChangeHealth(1);
            dragon->ChangeHealth(-1);
            this->spells2[i].offScreen1 = true;
             
        }
    }

    /*
    Is dragon health is zero or less than 0, then level complete and show win screen.
    */
    if (dragon->GetHealth() <= 0) {
        level->CompleteLevel();

    }
    /*
    If your health is less than or equal to 0, then game over
    */
    if (this->GetHealth() <= 0) {
        level->CompleteLevel();
        level->SetGameOver(true);
    }
    // Move player
    if (movingLeft && !movingRight)
    {
        this->Move(-speed * deltaTime, 0);
    } else if (movingRight && !movingLeft) {
        this->Move(speed * deltaTime, 0);
    }


}