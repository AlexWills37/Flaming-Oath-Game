/* player.h
 *
 * Defines the Player's character that they control.
 */
#ifndef _PLAYER_H
#define _PLAYER_H

#include <SFML/Graphics.hpp>
#include "entity.h"

class Player: public Entity {

    public:
        /*
         * Creates the player as an Entity with a texture.
         */
        Player(sf::RenderWindow * window, sf::Texture * texture);

        /*
         * Moves the player.
         */
        void Move(float deltaX, float deltaY);

        /*
         * Accesses the player's current score.
         */
        int GetScore();

        /*
         * Update's the player's state (score, collision, etc.).
         * Call this method every frame.
         */
        void FrameUpdate();

    private:
        int frameCounter;   // A counter to increase the player's score over time
        int score;          // The player's score
        int health;         // The player's health

};



#endif