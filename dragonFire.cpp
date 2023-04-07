#include "dragon.h"

DragonFire::DragonFire(sf::Vector2f startingPos) {
    texture.loadFromFile("./assets/sprites/dragon-fire.png");
    sprite.setTexture(texture, true);
    sprite.setPosition(startingPos);
    offScreen = false;
}

void DragonFire::MoveDown()
{
    sprite.move(0, -5);
    if (sprite.getPosition().y < 0) {
        offScreen = true;
    }
}