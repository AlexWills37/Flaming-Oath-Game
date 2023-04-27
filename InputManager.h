/* InputManager.h
 *
 * Interface for all of the input
 */

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
        // Delete the copy constructor
        InputManager(const InputManager& to_copy) = delete;

        /*
         * Returns a pointer to the single input manager.
         */
        static InputManager* GetInputManager();

        /*
         * Sets the render window to listen for events.
         */
        void SetGraphicsWindow(sf::RenderWindow* window);

        /*
         * Looks through all the events to update the state of the inputs.
         */
        void UpdateInput();

        /*
         * Returns the state of a keyboard, if it is pressed (true) or unpressed (false).
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