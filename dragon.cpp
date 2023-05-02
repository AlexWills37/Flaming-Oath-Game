/* dragon.cpp
 *
 * Implementations for the Dragon class.
 * 
 * @author Alex Wills
 * @date April 7, 2023
 */
#include "dragon.h"
#include<cstdlib>
#include <iostream>

/*
 * Creates a Dragon.
 * @param window - pointer to the window used for rendering
 * @param dragonTexture - pointer to the texture for the dragon that moves and spits fire
 * @param fireTexture - pointer to the texture for the fire that the dragon spits
 */
Dragon::Dragon(sf::RenderWindow * window, sf::Texture * dragonTexture, 
    sf::Texture * fireTexture, Player * player, HealthBar * healthBar): LivingEntity(window, dragonTexture, 500, 200, healthBar)
{
    // Providing a seed value for the dragon's random behavior
    srand((unsigned) time(NULL));

    // Create the DragonFire objects that this dragon will use
    for (int i = 0; i < Dragon::maxFires; ++i)
    {
        this->fires[i] = DragonFire(this->window, fireTexture);
    }   

    currentMovement = Movement::NONE;
    movementCounter = 0;
    this->player = player;

    this->EnableFollowingHealthBar(sf::Vector2f(-10, -50));
}

/*
 * Moves the Dragon randomly, occasionally spitting fire as well.
 */
void Dragon::Update()
{
    // Move based on current action    
    switch (currentMovement)
    {
        case Movement::RIGHT:
            Entity::Move(7, 0);
            movementCounter++;
            break;
        case Movement::LEFT:
            Entity::Move(-7, 0);
            movementCounter++;
            break;
        case Movement::NONE:

            movementCounter++;

            break;
        default: 
            break;
        
    }

    // After acting for 30 frames, choose a new action to take
    if (movementCounter > 30)
    {
        int random = rand() % 3;
        switch (random)
        {
            case 0:
                currentMovement = Movement::RIGHT;
                break;
            case 1:
                currentMovement = Movement::LEFT;
                break;
            case 2:
                currentMovement = Movement::NONE;
                break;
            default:
                break;
        }

        movementCounter = 0;
    }


    // Randomly spit fire
    int random = rand() % 60;
    switch (random) 
    {
        // Spit fire!
        case 0:
            this->SpitFire();
            break;
        default:
            break;
    }

    // Move all on-screen fires down
    for (int i = 0; i < Dragon::maxFires; i++) {
        if (!fires[i].offScreen) {
            fires[i].MoveDown();
        }
    }

    // Check for collisions
    this->CheckCollision(player);
}

/*
 * Creates a DragonFire object where the dragon currently is, so that the fire
 * falls on to the player.
 */
void Dragon::SpitFire()
{
    // Find the first fire that is off screen and put it where the dragon is
    DragonFire * newFire = nullptr;
    bool foundFire = false;
    for (int i = 0; i < Dragon::maxFires && !foundFire; ++i)
    {
        // If fire is off screen, we can use it as a new fire
        if (this->fires[i].offScreen) {
            newFire = &(this->fires[i]);
            foundFire = true;
        }
    }

    // If we found a fire that is off screen, we can have the dragon spit it out (move it to the dragon)
    if (foundFire) {
        newFire->offScreen = false;
        newFire->sprite.setPosition(this->sprite.getPosition());    // Set the fire to the dragon's current position
    }

    // If we did not find a fire, then there are currently this->maxFires fires on screen, so we will not spit fire.
}

/*
 * Draws the dragon, and any on-screen fire, to the window.
 */
void Dragon::Draw()
{
    // Draw the fires first
    for (int i = 0; i < this->maxFires; ++i)
    {
        if (!this->fires[i].offScreen)  // Only draw fires that are on screen
        {
            this->fires[i].Draw();
        }
    }
    
    // Draw the dragon last, so that it is on top of any fire
    LivingEntity::Draw();
}


/*
 * Detect collision with the player and damage the player if they are hit.
 * Specifically checks for collision with the DragonFire objects that are on-screen
 */
bool Dragon::CheckCollision(Player * player)
{
    bool hit = false;

    for (int i = 0; i < this->maxFires; i++)
    {
        // Detect a collision
        if (!(this->fires[i].offScreen) && this->fires[i].getGlobalBounds().intersects(player->getGlobalBounds()))
        {
            hit = true;
            this->fires[i].offScreen = true;
            player->ChangeHealth(-1);
        }
    }

    return hit;
}