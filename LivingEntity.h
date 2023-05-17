/* LivingEntity.h
 *
 * An entity that has a health bar and can be damaged.
 * 
 * @author Alex Wills
 */
#ifndef _LIVINGENTITY_H
#define _LIVINGENTITY_H

#include "entity.h"
#include "HealthBar.h"
#include <SFML/Graphics.hpp>

class LivingEntity: public Entity {
    // This class contains everything from the Entity class.
    // Member variables
    private:

        /*
         * Enum for the behavior of the health bar. 
         *  FIXED - health bar stays at the same screen location, regardless of entity location
         *  FOLLOW - the healthbar follows the entity's location at a fixed offset
         */
        enum HealthBarLocation {
            FIXED, FOLLOW
        };

        HealthBar* healthBar;   // The entity's health bar
        HealthBarLocation healthMovement;   // Where the health bar should be drawn
        sf::Vector2f healthbarOffset;   // If the health bar should follow the player, where should it be (relatively)

    // Constructor
    public:

        /*
         * Constructs an entity that has health and a health bar.
         *
         * @param window - the window of the game
         * @param texture - the entity's main texture
         * @param x, y - the starting location of the entity
         * @param healthBar - pointer to the unique health bar this entity will use
         */
        LivingEntity(sf::RenderWindow * window, sf::Texture * texture, float x,
            float y, HealthBar * healthBar);

    // Method overrides
    public:
        /*
         * Draws the entity along with its health bar.
         */
        void Draw();

    // New methods
    public:

        /*
         * Returns the entity's current health.
         */
        int GetHealth();

        /*
         * Changes the amount of health this entity has.
         */
        void ChangeHealth(int change);

        /*
         * Set the health bar to follow the entity.
         * 
         * @param offset - how far from the entity's origin the health bar's origin should be
         */
        void EnableFollowingHealthBar(sf::Vector2f offset);

};

#endif