/* dragonFire.cpp
 * 
 * Implementation of the DragonFire class.
 */
#include "dragon.h"

/*
 * Creates a DragonFire object.
 */
DragonFire::DragonFire(sf::RenderWindow * window, sf::Texture * texture)
: Entity(window, texture) {
    // Start all fires off screen
    this->offScreen = true;
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