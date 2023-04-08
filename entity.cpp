/* entity.cpp
 *
 * Implementation of some functions that are common to all entities (objects with sprites to render)
 */
#include "entity.h"

/*
 * Constructs an entity without a starting point (it will start with the sprite at (0, 0))
 * @param window - a pointer to the window to draw the sprite to
 * @param texture - a pointer to the texture this sprite will use
 */
Entity::Entity(sf::RenderWindow * window, sf::Texture * texture)
{
    this->texture = texture;
    this->window = window;
    this->sprite.setTexture(*texture, true);
}

/*
 * Cosntructs an entity with a starting position.
 * @param window - a pointer to the window to draw the sprite to
 * @param texture - a pointer to the texture this sprite will use
 * @param startX, startY - the starting position of the sprite
 */
Entity::Entity(sf::RenderWindow * window, sf::Texture * texture, float startX, float startY): Entity(window, texture)   // Call the constructor above first
{
    this->sprite.setPosition(startX, startY);
}

/*
 * Default constructor. Leaves all fields empty.
 */
Entity::Entity()
{
    
}

/*
 * Moves the entity in the specified direction, keeping the sprite in the window.
 *
 * @param deltaX - the change in x value to move
 * @param deltaY - the change in y value to move
 */
void Entity::Move(float deltaX, float deltaY)
{
    // Move the sprite's vector
    sf::Vector2f position = this->sprite.getPosition();
    position += sf::Vector2f(deltaX, deltaY);

    // Make sure the sprite is in bounds
    sf::Vector2u windowSize = this->window->getSize();
    position.x = std::clamp(position.x, float(0), float(windowSize.x));
    position.y = std::clamp(position.y, float(0), float(windowSize.y));

    // Update the position
    this->sprite.setPosition(position);
}

/*
 * Draws the sprite to the window.
 */
void Entity::Draw()
{
    window->draw(sprite);
}
