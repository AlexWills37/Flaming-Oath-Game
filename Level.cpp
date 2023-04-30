/* Level.cpp
 *
 * Defines the basic level class, which can be extended to do multiple things
 * 
 * @author Alex Wills
 */


#include "Level.h"


Level::Level() {
    input = InputManager::GetInputManager();
}


void Level::HandleInputs() {
    input->UpdateInput();
}

void Level::UpdateEntities() {
    // Update all of the entities
    for (Entity* entity : entities) {
        entity->Update();
    }
}

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

void Level::AddSprite(sf::Sprite* to_add) {
    sprites.push_back(to_add);
}
void Level::AddEntity(Entity* to_add) {
    entities.push_back(to_add);
}

void Level::SetWindow(sf::RenderWindow* window) {
    this->window = window;
}