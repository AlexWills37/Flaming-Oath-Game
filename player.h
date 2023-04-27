/* player.h
 *
 * Defines the Player's character that they control.
 * 
 * @author Alex Wills
 * @author Jhonder Abreus
 * @date April 7, 2023
 */
#ifndef _PLAYER_H
#define _PLAYER_H

#include <SFML/Graphics.hpp>
#include "entity.h"
#include "dragon.h"

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

        int GetHealth();

        void ChangeHealth(int change);

        void DecreaseScore(int change);

    private:
        int frameCounter;   // A counter to increase the player's score over time
        int score;          // The player's score
        int health;         // The player's health
        float speed;

};



#endif