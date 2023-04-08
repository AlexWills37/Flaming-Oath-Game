/* entity.h
 *
 * Base class for all entities (player, enemies, sprites that move around).
 * To create an entity, first extend this class by creating a new class
 *      class Character: public Entity {
 *      
 *      };
 * Entity must be public so that the main function can call the object's Draw() method.
 * 
 * Override the class's constructor to initialize the sprite and texture. You can also call
 * this class's constructor like this:
 *      Character(sf::RenderWindow * window) : Entity(window) {
 *      
 *      }
 * This way, you don't need to worry about setting the window. You could also pass in starting coordinates here,
 * like: Entity(window, x, y) {}
 * 
 * 
 */
#ifndef _ENTITY_H
#define _ENTITY_H

#include <SFML/Graphics.hpp>

class Entity {
    public:
        /*
         * Construct an entity.
         * @param window - a pointer to the RenderWindow to draw this entity to
         * @param texture - a pointer to the texture this entity will use
         *      (the texture object itself must stay in-scope, so create the textures before the 
         *       main game loop, and pass in pointers to the Entities)
         * @param x, y - the starting coordinates for the Entity
         */
        Entity(sf::RenderWindow * window, sf::Texture * texture, float x, float y);
        Entity(sf::RenderWindow * window, sf::Texture * texture);
        Entity();

        /*
         * Moves this sprite on the screen.
         */
        void Move(float deltaX, float deltaY);

        /*
         * Draw this entity's sprite(s) to the screen.
         */
        void Draw();

    protected:
        // These variables can be accessed by children classes
        sf::Sprite sprite;
        sf::Texture * texture;
        sf::RenderWindow * window;
};

#endif