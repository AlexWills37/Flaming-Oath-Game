/* MouseButton.cpp
 *
 * Implementation of the MouseButton class used for progressing levels with menu items.
 *
 * @author Alex Wills
 */

#include "MouseButton.h"
#include "InputManager.h"

#include <iostream>

/*
 * Constructs a button with text to display.
 *
 * @param window - the game window
 * @param font - the font of the button
 * @param text - the text to display in the button
 * @param level - the level to control with the button
 */
MouseButton::MouseButton(sf::RenderWindow * window, sf::Font* font, std::string buttonText, Level * level) {
    this->font = font;
    text = new sf::Text();
    text->setString(buttonText);
    text->setFont(*font);
    text->setCharacterSize(60);
    buttonBox.setFillColor(sf::Color(50, 50, 50, 255));
    this->ResizeButtonBox();    // Fit the button to the text
    this->window = window;
    this->level = level;
}


/*
 * Returns if the button has been clicked.
 */
bool MouseButton::IsClicked() {
    return clicked;
}

/*
 * Resets the button's data to be clicked again.
 */
void MouseButton::ResetButton() {
    clicked = false;
}

/*
 * Draws the button.
 */
void MouseButton::Draw() {
    window->draw(buttonBox);
    window->draw(*text);
}

/*
 * Updates the button and level status depending on if the user is hovering over the button
 * and if they click the button.
 */
void MouseButton::Update() {
    InputManager * input = InputManager::GetInputManager();

    sf::Vector2i mousePos = input->GetMousePosition();

    // If the mouse is currently over the button...
    if (buttonBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        buttonBox.setFillColor(sf::Color(200, 200, 200, 255));
        
        // If the mouse was pressed last frame, and it is released when hovering over the box, click!
        if (mouseClicking && !input->IsMousePressed()) {
            clicked = true;
            mouseClicking = false;

            // Complete the "level" to move to the next action
            level->SetGameOver(restartOnClick); // To restart on click, we handle it as a game over. In the main game loop, this game over is processed as a restart.
            level->CompleteLevel();


        // ...if the mouse is pressd, we should toggle mouseClicing
        } else if (input->IsMousePressed()) {
            mouseClicking = true;
        }

    } else {
        buttonBox.setFillColor(sf::Color(100, 100, 100, 255));
        // If the mouse goes out of the button, stop any current click from activating it
        mouseClicking = false;
    }

}

/*
 * Changes the button's sprite size to fit with the text.
 */
void MouseButton::ResizeButtonBox() {
    sf::FloatRect textBounds = text->getGlobalBounds();

    this->buttonBox.setSize(sf::Vector2f(textBounds.width + 30, textBounds.height + 30));
}

/*
 * Sets the position of the button on the screen.
 */
void MouseButton::SetPosition(float x, float y) {
    text->setPosition(x, y);
    buttonBox.setPosition(x - 15, y);
}

/*
 * Sets the button to cause the level to game over or not when clicked.
 *
 * @param restartOnClick - whether the level should "game over" when the button is clicked.
 *      Either way, the level will "complete" when the button is clicked.
 */
void MouseButton::SetBehaivor(bool restartOnClick) {
    this->restartOnClick = restartOnClick;
}