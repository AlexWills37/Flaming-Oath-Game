
#include "HealthBar.h"

HealthBar::HealthBar(sf::RenderWindow* window, sf::Texture* emptyHearts, sf::Texture* filledHearts)
{
    this->window = window;
    this->emptyHeartTexture = emptyHearts;
    this->filledHeartTexture = filledHearts;
    

    // build sprites
    this->backgroundSprite.setTexture(*emptyHeartTexture, true);
    this->heartsSprite.setTexture(*filledHeartTexture, true);
    this->heartWidth = 33;

    // Initial health
    this->health = 5;
}
/*
    * Gets the health from this health bar.
    */
int HealthBar::getHealth()
{
    return this->health;
}

/*
    * Replaces the health of this health bar and updates it visually.
    *
    * @param newHealth (int) - the new value of the health
    */
void HealthBar::setHealth(int newHealth)
{
    this->health = newHealth;
}

/*
    * Changes the health of this health bar and updates it visually.
    *
    * @param difference (int) - the change in health (example: -1 = lose 1 health)
    */
void HealthBar::changeHealth(int difference)
{
    this->health += difference;
}


void HealthBar::drawBackground()
{
    this->window->draw(backgroundSprite);  
}
void HealthBar::drawHearts(int numHearts)
{
    // Reshape the sprite rectangle to cut off missing hearts
    sf::IntRect size;
    size.top = 0;
    size.left = 0;
    size.height = this->heartsSprite.getLocalBounds().height;
    size.width = this->heartWidth * numHearts;
    this->heartsSprite.setTextureRect(size);
    this->window->draw(heartsSprite);
}

void HealthBar::Draw()
{
    this->drawBackground();
    this->drawHearts(this->health);
}

void HealthBar::SetPosition(float x, float y) {
    heartsSprite.setPosition(x, y);
    backgroundSprite.setPosition(x, y);
}