/* InputManager.h
 *
 * Interface for all of the input in the game.
 * To use:
 *  (FIRST TIME IN CODE, SETTING UP THE MANAGER)
 *      - Get a reference to the InputManager object with:
 *          InputManager* input = InpnutManager::GetInputManager();
 * 
 *      - Connect the input manager to the graphics window with:
 *          input->SetGraphicsWindow( <pointer to sf::RenderWindow> );
 * 
 *      NOTE: You only have to set up the graphics window once in the program. Do this before the
 *      main gameplay loop.
 * 
 *  (ONCE PER FRAME, UPDATING THE INPUT STATES)
 *      - Get a reference to the InputManager object with:
 *          InputManager* input = InpnutManager::GetInputManager();
 * 
 *      - Update the input one time every frame with:
 *          input->UpdateInput();
 * 
 *  (ANYWHERE IN CODE, ACCESSING THE INPUT STATES)
 *      - Get a reference to the InputManager object with:
 *          InputManager* input = InpnutManager::GetInputManager();
 *      
 *      - Access whether or not a key is pressed down with:
 *          input->IsKeyPressed(sf::Keyboard::Key key)
 *      
 *      - Access whether or not the left mouse button is pressed down with:
 *          input->IsMousePressed();
 * 
 *      - Get the current position of the mouse in the window with:
 *          input->GetMousePosition();
 * 
 * 
 * @author ALex Wills
 */

#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H

#include <map>
#include <SFML/Graphics.hpp>

class InputManager {

    protected:
        // Hide the constructor from other classes
        InputManager();

        // Hide the single instance of the input manager
        static InputManager* instance;

        // Variables that the instance will have

        sf::Event event;    // Event variable for processing key/button events
        sf::RenderWindow* window;   // Pointer to main graphics window

        
        std::map<sf::Keyboard::Key, bool> keyStates; // Map the keyboard keys to booleans (pressed or not pressed)

        // Mouse information
        sf::Vector2i mousePosition;
        bool mouseClicked;

    public:
        /*
         * Returns a pointer to the single input manager.
         */
        static InputManager* GetInputManager();

        // Delete the copy constructor
        InputManager(const InputManager& to_copy) = delete;


        /*
         * Sets the render window to listen for events.
         */
        void SetGraphicsWindow(sf::RenderWindow* window);

        /*
         * Looks through all the events to update the state of the inputs.
         */
        void UpdateInput();

        /*
         * Returns the state of a keyboard key, if it is pressed (true) or unpressed (false).
         */
        bool IsKeyPressed(sf::Keyboard::Key key);

        /*
         * Returns true if the mouse is currently being pressed down.
         */
        bool IsMousePressed();

        /*
         * Returns the position of the mouse in the window.
         */
        sf::Vector2i GetMousePosition();

};

#endif