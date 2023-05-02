
#include "Dialogue.h"
#include "InputManager.h"


Dialogue::Dialogue() {
    font = new sf::Font();
    font->loadFromFile("./assets/fonts/ShadowsIntoLight-Regular.ttf");
    text = new sf::Text();
    text->setFont(*font);
    currentSpeech = 0;

}

Dialogue::Dialogue(sf::RenderWindow * window) { // We should add Entity superclass things
    this->window = window;
    font = new sf::Font();
    font->loadFromFile("./assets/fonts/ShadowsIntoLight-Regular.ttf");
    text = new sf::Text();
    text->setFont(*font);
    currentSpeech = 0;
}

void Dialogue::InitializeDialogue(std::vector<TextObject*> dialogue) {
    this->dialogue = dialogue;
    text->setString(dialogue[0]->speech);
}

void Dialogue::Update() {

    if (!spacePressed && InputManager::GetInputManager()->IsKeyPressed(sf::Keyboard::Space)) {
        spacePressed = true;
        currentSpeech += 1;
        text->setString(dialogue[currentSpeech]->speech);
    } else if (spacePressed && !InputManager::GetInputManager()->IsKeyPressed(sf::Keyboard::Space)) {
        spacePressed = false;
    }
    
}

void Dialogue::Draw() {
    window->draw(*text);
}


TextObject::TextObject() {
    this->speaker = "none";
    this->speech = "ERROR: Text not found";
}
TextObject::TextObject(std::string speaker, std::string speech) {
    this->speaker = speaker;
    this->speech = speech;
}
