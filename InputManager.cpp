/* InputManager.cpp
 *
 * Implementation of the input manager class.
 * 
 * @author Alex WIlls
 * @date April 27, 2023
 */

#include "InputManager.h"
#include <iostream>

// Initialize the single instance to null by default
// (the compiler gets angry if this is not here)
// (if you initialize the pointer in the .h file, it cannot be changed (const))
InputManager* InputManager::instance = nullptr;

/*
 * Default Constructor. Initializes an empty input manager without a
 * RenderWindow.
 */
InputManager::InputManager() {
    // this->event will be set in the update function
    this->window = nullptr;
    this->mousePosition = sf::Vector2i(0, 0);
    this->mouseClicked = false;
    this->keyStates = std::map<sf::Keyboard::Key, bool>();
}

/*
 * Accesses the single InputManager object for input handling
 */
InputManager* InputManager::GetInputManager() {
    // Create input manager if it has not already been made
    if (InputManager::instance == nullptr) {
        InputManager::instance = new InputManager();
    }

    // Return the pointer
    return InputManager::instance;
}

/*
 * Sets the render window to listen for events.
 */
void InputManager::SetGraphicsWindow(sf::RenderWindow* window) {
    this->window = window;
}

/*
 * Checks the keyboard and mouse (input) and updates the state
 * of the InputManager to reflect any changes. This method
 * should be called at the beginning of every frame in the main
 * loop of the program (but only call it once per frame).
 */
void InputManager::UpdateInput() {
    // Make sure the window exists
    if (window == nullptr) {
        std::cout << "ERROR! The window has not been set on the InputManager" << std::endl;
        std::cout << "\tProgram will not update the inputs because there is no window." << std::endl;
    } else {
        // Process any and all events that the window recorded
        while (window->pollEvent(event)) {
            switch (event.type) {
                
                // Closed window
                case sf::Event::Closed:
                    window->close();
                    break;
                
                // Key press
                case sf::Event::KeyPressed:
                    keyStates[event.key.code] = true;   // Set the value of the key to true
                    break;
                
                // Key release
                case sf::Event::KeyReleased:
                    keyStates[event.key.code] = false;  // Set key value to false
                    break;

                // Mouse click
                case sf::Event::MouseButtonPressed:
                    mouseClicked = true;
                    break;

                // Mouse release
                case sf::Event::MouseButtonReleased:
                    mouseClicked = false;
                    break;

                default:
                    break;
            } // This event has been processed
        } // All events have been processed
        mousePosition = sf::Mouse::getPosition(*window);    // Update the mouse position
    } // End of if-else statement checking if the window exists
}

/*
 * Returns the state of a keyboard input. True if the key is pressed,
 * false if the key is unpressed.
 * 
 * This function does not check if the key has been mapped.
 * If you check a key that has not been added to the keyStates map,
 * you may get an undefined value.
 * 
 * @param key (sf::Keyboard::Key) the keyboard key to query
 */
bool InputManager::IsKeyPressed(sf::Keyboard::Key key) {
    return keyStates[key];
}

/*
 * Returns true if the mouse is currently being pressed down.
 */
bool InputManager::IsMousePressed() {
    return mouseClicked;
}

/*
 * Returns the position of the mouse in the window.
 */
sf::Vector2i InputManager::GetMousePosition() {
    return mousePosition;
}