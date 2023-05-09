/* dragon.h
 *
 * Defines the Dragon and the DragonFire classes.
 * 
 * @author Alex Wills
 * @date April 7, 2023
 */
#ifndef _DRAGON_H
#define _DRAGON_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "entity.h"
#include "player.h"

/*
 * DragonFire represents the fire that a dragon breaths to attack the player.
 */
class DragonFire: private Entity {  // Since this is private, only DragonFire and the friend class Dragon can call the entity methods
    friend class Dragon; // Allow Dragon class to access the DragonFire's private methods/fields (such as .Draw())
    public:
        /*
         * Constructor for DragonFire.
         * @param window - a pointer to the window to draw to
         * @param startingPos - the initial position of the fire
         */
        DragonFire(sf::RenderWindow * window, sf::Texture * texture);
        /*
         * Default constructor. Initializes offScreen to true.
         */
        DragonFire();
        
        
        /*
         * Moves the fire towards the ground.
         */
        void MoveDown();


    protected:

    private:
        bool offScreen; // If this is true, the sprite is off screen and we can re-use it

        // const int textureWidth = 46;
        // const int textureHeight = 163;

};

class Player;

enum class Movement {
    NONE, LEFT, RIGHT, UP, DOWN
};

/*
 * Dragon is an enemy that attacks the player.
 */
class Dragon: public LivingEntity {
    public:

        /*
         * Constructor
         * @param window - the window to draw the dragon to
         */
        Dragon(sf::RenderWindow * window, sf::Texture * dragonTexture, sf::Texture * fireTexture, 
            Player * player, HealthBar * healthBar);

        /*
         * Moves the dragon randomly.
         */
        void Update();

        /*
         * Create a DragonFire and send it towards the player.
         */
        void SpitFire();


        /*
         * Draws the dragon, and any on-screen fire, to the window.
         */
        void Draw();

        bool CheckCollision(Player * player);

    private:
        static const int maxFires = 5;  // How many fires can be on screen at once      
        DragonFire fires[maxFires];  // A list of the DragonFire objects that belong to this dragon.
        Movement currentMovement;
        int movementCounter;
        Player* player;
        

};
#endif