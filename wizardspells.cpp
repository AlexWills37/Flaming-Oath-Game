/* dragonFire.cpp
 * 
 * Implementation of the WizardSpells class.
 * 
 * @author Alex Wills
 * @date April 7, 2023
 */
#include "player.h"

/*
 * Creates a WizardSpells object.
 */
WizardSpells::WizardSpells(sf::RenderWindow * window, sf::Texture * texture)
: Entity(window, texture) {
    // Start all fires off screen
    this->offScreen1 = true;

    // this->sprite.setTextureRect(sf::IntRect(0, 0, this->textureWidth, this->textureHeight));
}


WizardSpells::WizardSpells()
{
    this->offScreen1 = true;
}

void WizardSpells::MoveUp()
{
    sprite.move(0, -10);
    if (sprite.getPosition().y > 0) {
        offScreen1 = true;
    }
}