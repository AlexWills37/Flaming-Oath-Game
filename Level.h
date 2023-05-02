/* Level.h
 *
 * This file outlines a Level class that can be used to create different levels with different
 * game mechanics, input handling, and sprites.
 * 
 * @author Alex Wills
 * @date April 27, 2023
 */
#ifndef _LEVEL_H
#define _LEVEL_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "entity.h"
#include "InputManager.h"

class Level {

    // Member variables
    private:
        InputManager* input;
        std::vector<sf::Sprite*> sprites;   // List of sprites that are not part of entities (like the background)
        std::vector<Entity*> entities;  // List of entities that are dynamic and will update every frame

        sf::RenderWindow* window;

    // Constructors
    public:
        Level();

    // Methods
    public:
        void HandleInputs();
        void UpdateEntities();
        void DrawSprites();
        void AddSprite(sf::Sprite* to_add);
        void AddEntity(Entity* to_add);
        void SetWindow(sf::RenderWindow* window);

};

#endif