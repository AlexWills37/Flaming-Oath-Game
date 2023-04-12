/* dragonFire.cpp
 * 
 * Implementation of the DragonFire class.
 * 
 * @author Alex Wills
 * @date April 7, 2023
 */
#include "dragon.h"

/*
 * Creates a DragonFire object.
 */
DragonFire::DragonFire(sf::RenderWindow * window, sf::Texture * texture)
: Entity(window, texture) {
    // Start all fires off screen
    this->offScreen = true;

    // this->sprite.setTextureRect(sf::IntRect(0, 0, this->textureWidth, this->textureHeight));
}


DragonFire::DragonFire()
{
    this->offScreen = true;
}

void DragonFire::MoveDown()
{
    sprite.move(0, 5);
    if (sprite.getPosition().y > this->window->getSize().y) {
        offScreen = true;
    }
}