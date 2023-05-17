/* Level.h
 *
 * This file outlines a Level class that can be used to create different levels with different
 * game mechanics, input handling, and sprites.
 * 
 * To use:
 *  (CREATING A LEVEL)
 *      - Create a new level object
 *          example: Level* level1 = new Level();
 * 
 *      - Connect the level to the game's Render Window:
 *          example: level1->SetWindow(&window);
 * 
 *      - Add Entities, which will update every frame, with
 *          AddEntity(Entity*);
 * 
 *      - Add sprites, which will not update in the level functions, and will be drawn before the entities with
 *          AddSprite(sf::Sprite*);
 * 
 *  (RUNNING A LEVEL)
 *      - Clear the graphics window
 *      
 *      - Update the inputes with:
 *          level->HandleInputs();
 * 
 *      - Update the entities with:
 *          level->UpdateEntities();
 *      
 *      - Draw the level with
 *          level->DrawSprites();
 *      
 *      - Display the graphics window
 * 
 * (FINISHING A LEVEL)
 *      Every frame, you can check the current level status.
 *      When 
 *          level->IsComplete()
 *      is true, the level has either been won or lost.
 *      If
 *          Level->IsGameOver()
 *      is true, the level has been lost.
 *      If it is false, then the level has been won!
 * 
 *      You can use these checks in the main game loop to determine when to change levels, and
 *      to determine what level to go to next.
 *  
 * @author Alex Wills
 * @date April 27, 2023
 */
#ifndef _LEVEL_H
#define _LEVEL_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "entity.h"
#include "InputManager.h"

class Level {


    // Member variables
    private:
        InputManager* input;    // Pointer to the single input manager
        std::vector<sf::Sprite*> sprites;   // List of sprites that are not part of entities (like the background)
        std::vector<Entity*> entities;  // List of entities that are dynamic and will update every frame

        sf::RenderWindow* window;

        // Information about the level state
        bool levelComplete = false;     // When this is true, it is time to move to the next level
        bool gameOver = false;          // When this is true, moving on from the level counts as a game over

        sf::Music * backgroundMusic = nullptr;  // Music attached to this level


    // Constructors
    public:
        Level();
        ~Level();

    // Methods
    public:
        /*
         * Updates the input manager to process any new inputs.
         */
        void HandleInputs();

        /*
         * Goes through the list of entities and calls the Update() function on all of them.
         */
        void UpdateEntities();

        /*
         * Draws all of the sprites in this level, then draws all of the entities.
         */
        void DrawSprites();

        /*
         * Adds a sprite for this level to draw.
         */
        void AddSprite(sf::Sprite* to_add);

        /*
         * Adds an entity for this level to update and draw.
         */
        void AddEntity(Entity* to_add);

        /*
         * Assigns a pointer to the game's render window for drawing sprites.
         */
        void SetWindow(sf::RenderWindow* window);

        /*
         * Returns true if the level is flagged complete and ready to move on.
         */
        bool IsComplete();

        /*
         * Sets the level's 'complete' flag to true.
         */
        void CompleteLevel();

        /*
         * Resets the level's 'complete' and game over flags to false.
         */
        void ResetLevel();

        /*
         * Returns true if the level has been lost, and the user should game over.
         */
        bool IsGameOver();

        /*
         * Updates the level's game over status.
         * @param isGameOver - the level's new game over status
         */
        void SetGameOver(bool isGameOver);

        /*
         * Attaches background music to this level and starts to play it.
         * The music will continue to play on loop until the level object is destroyed.
         * 
         * @param filepath - the relative filepath to the song (.ogg recommended) to play
         */
        void AddBackgroundMusic(std::string filepath);
};

#endif