/* dragon.cpp
 *
 * Implementations for the Dragon class.
 */
#include "dragon.h"
#include<cstdlib>

/*
 * Creates a Dragon.
 * @param window - pointer to the window used for rendering
 * @param dragonTexture - pointer to the texture for the dragon that moves and spits fire
 * @param fireTexture - pointer to the texture for the fire that the dragon spits
 */
Dragon::Dragon(sf::RenderWindow * window, sf::Texture * dragonTexture, sf::Texture * fireTexture): Entity(window, dragonTexture, 500, 200)
{
    // Providing a seed value for the dragon's random behavior
    srand((unsigned) time(NULL));

    // Create the DragonFire objects that this dragon will use
    for (int i = 0; i < Dragon::maxFires; ++i)
    {
        this->fires[i] = DragonFire(this->window, fireTexture);
    }   
}

/*
 * Moves the Dragon randomly, occasionally spitting fire as well.
 */
void Dragon::Move()
{
    // Get a random number
    int random = rand() % 5;

    switch(random)
    {
        // Move left
        case 0:
            Entity::Move(-50, 0);
            break;

        // Move right
        case 1:
            Entity::Move(50, 0);
            break;

        default:
            break;
    }
    


    // Randomly spit fire
    random = rand() % 60;
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
    Entity::Draw();
}