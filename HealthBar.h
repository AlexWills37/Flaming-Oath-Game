/* HealthBar.h
 *
 * An entity representation of a character's health.
 * 
 * @author Alex Wills
 */
#ifndef _HEALTHBAR_H
#define _HEALTHBAR_H

#include <SFML/Graphics.hpp>
#include "entity.h"

class HealthBar: public Entity {

    // Member variables
    private:
        sf::Texture * emptyHeartTexture;    // The empty health meter
        sf::Texture * filledHeartTexture;   // The filled health meter
        sf::Sprite backgroundSprite;    
        sf::Sprite heartsSprite;

        int health; // The number of health points the entity has

        int heartWidth; // The number of pixels in a single "heart" on the heart meter

    // Constructors
    public:

        /*
         * Constructs a health bar to be used by an entity.
         *
         * @param window - the game window
         * @param emptyHearts - texture of the empty hearts
         * @param filledHearts - texture of a full heart meter
         */
        HealthBar(sf::RenderWindow* window, sf::Texture* emptyHearts, sf::Texture* filledHearts);


    // Methods
    public:
        /*
         * Gets the health from this health bar.
         */
        int getHealth();

        /*
         * Replaces the health of this health bar and updates it visually.
         *
         * @param newHealth (int) - the new value of the health
         */
        void setHealth(int newHealth);

        /*
         * Changes the health of this health bar and updates it visually.
         *
         * @param difference (int) - the change in health (example: -1 = lose 1 health)
         */
        void changeHealth(int difference);

        /*
         * Draws the health bar.
         */
        void Draw();

        /*
         * Sets the position of the health bar on the screen.
         */
        void SetPosition(float x, float y);

    // Helper functions
    private:
        /*
         * Draws the empty heart meter for the background.
         */
        void drawBackground();

        /*
         * Draws the filled hearts.
         *
         * @param numHearts - the number of hearts to draw
         */
        void drawHearts(int numHearts);

};

#endif