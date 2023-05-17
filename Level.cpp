/* Level.cpp
 *
 * Defines the basic level class, which can be extended to do multiple things
 * 
 * @author Alex Wills
 */


#include "Level.h"
#include <iostream>
Level::Level() {
    input = InputManager::GetInputManager();
}

/*
 * Updates the input manager to process new inputs.
 */
void Level::HandleInputs() {
    input->UpdateInput();
}

/*
 * Updates the entities by calling their Update() functions.
 */
void Level::UpdateEntities() {
    // Update all of the entities
    for (Entity* entity : entities) {
        entity->Update();
    }
}

/*
 * Draws the level to the screen by drawing the sprites, then the entities.
 */
void Level::DrawSprites() {
    // Draw any static sprites first (like the background)
    for (sf::Sprite * staticSprite : sprites) {
        window->draw(*staticSprite);
    }

    // Draw all of the entities
    for (Entity* entity : entities) {
        entity->Draw();
    }
}

/*
 * Adds a sprite to draw in the level.
 */
void Level::AddSprite(sf::Sprite* to_add) {
    sprites.push_back(to_add);
}

/* 
 * Adds an entity to update and draw in the level.
 */
void Level::AddEntity(Entity* to_add) {
    entities.push_back(to_add);
}

/*
 * Sets the render window for drawing the level's sprites.
 */
void Level::SetWindow(sf::RenderWindow* window) {
    this->window = window;
}

/*
 * Returns true if the level is won or lost.
 */
bool Level::IsComplete() {
    return levelComplete;
}

/*
 * Marks the level as complete, either won or lost.
 */
void Level::CompleteLevel() {
    levelComplete = true;
}

/*
 * This function, in addition to IsComplete(), marks the level as lost.
 */
void Level::SetGameOver(bool isGameOver) {
    gameOver = isGameOver;
}

/*
 * Returns true if the flag for losing the level is set to true.
 */
bool Level::IsGameOver() {
    return gameOver;
}

/*
 * Resets the level's copmletion status so that it can be played again.
 */
void Level::ResetLevel() {
    levelComplete = false;
    gameOver = false;
}

/*
 * Attaches background music to this level and starts to play it.
 * The music will continue to play on loop until the level object is destroyed.
 * 
 * @param filepath - the relative filepath to the song (.ogg recommended) to play
 */
void Level::AddBackgroundMusic(std::string filepath) {
    backgroundMusic = new sf::Music();
    if (!backgroundMusic->openFromFile(filepath) ) {
        std::cout << "ERROR: Could not open music at " << filepath << std::endl;
    } else {
        backgroundMusic->play();
        backgroundMusic->setLoop(true);
    }
    
}

/*
 * Level destructor - stops the background music attached to the level.
 */
Level::~Level() {
    if (backgroundMusic != nullptr) {
        backgroundMusic->stop();
    }
}