/* entity.cpp
 *
 * Implementation of some functions that are common to all entities (objects with sprites to render)
 * 
 * @author Alex Wills
 * @author Jhonder Abreus
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
    // sf::Vector2f position = this->sprite.getPosition();
    // position += sf::Vector2f(deltaX, deltaY);
    // this->sprite.setPosition(position);
    this->sprite.move(deltaX, deltaY);

    // Make sure the sprite is in bounds
    sf::Vector2u windowSize = this->window->getSize();
    sf::Vector2f position = sprite.getPosition();
    sf::FloatRect bounds = sprite.getGlobalBounds();
    if (bounds.left < 0) {
        position.x -= bounds.left;
    }
    else if (bounds.left + bounds.width > windowSize.x){
        position.x -= bounds.left + bounds.width - windowSize.x;
    }
    if (bounds.top < 0) {
        position.y -= bounds.top;
    }
    else if (bounds.top + bounds.height > windowSize.y){
        position.y -= bounds.top + bounds.height - windowSize.y;
    }

    sprite.setPosition(position);


}

/*
 * Draws the sprite to the window.
 */
void Entity::Draw()
{
    window->draw(sprite);
}

sf::FloatRect Entity::getGlobalBounds()
{
    return this->sprite.getGlobalBounds();
}

void Entity::SetPosition(float x, float y) {
    sprite.setPosition(x, y);
}