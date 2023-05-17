/* MouseButton.h
 *
 * An entity that the player can click on to progress a level.
 * When the button is clicked, the level will be marked as "complete".
 * The button can be configured to also mark the level as "game over" or not.
 * The width of the button will be determined by the size of the text string.
 * 
 * To use:
 *      First, add a button to the level!
 *      You must connect the level to the button with
 *          the constructor.
 *      Then set the behavior with
 *          button->SetBehavior(bool)
 *          
 *          true = the button will cause the level to "game over" and "complete"
 *          false = the button will cause the level to "complete" but not "game over"
 *  
 *          This can be used to make 2 different buttons whose behavior is processed in the main
 *          game loop.
 *          
 *          Example: If the pause screen "game overs", that means to quit/restart the game
 *                   If the pause screen is commplete but does not game over, that means to unpause the game
 * 
 * @author Alex Wills
 */

#ifndef _MOUSEBUTTON_H
#define _MOUSEBUTTON_H
#include "entity.h"
#include "Level.h"

class MouseButton: public Entity {

    // Member variables
    private:

        bool clicked = false;   // True if the button has been activate
        bool mouseClicking = false; // True if the mouse is currently pressed on the button (waiting for button release)

        sf::Font * font = nullptr;  // The font of the button
        sf::Text * text;            // The text of the button

        sf::RectangleShape buttonBox;   // The box the user will be able to click on

        Level * level;  // The level connected to this button

        bool restartOnClick = false;


    // Constructor
    public:

        /*
         * Constructs a button with text to display.
         *
         * @param window - the game window
         * @param font - the font of the button
         * @param text - the text to display in the button
         * @param level - the level to control with the button
         */
        MouseButton(sf::RenderWindow * window, sf::Font * font, std::string text, Level * level);

    // Public methods
    public:
        /*
         * Returns true if the button has been clicked at all.
         */
        bool IsClicked();

        /*
         * Resets the button to be "unclicked" so that the user can click it 
         * again, and IsClicked() returns false.
         */
        void ResetButton();

        /*
         * Overridden draw method for this button entity.
         */
        void Draw();

        /*
         * Checks if the user is clicking the button and updates the button's status.
         */
        void Update();

        /*
         * Overridden set position method for moving the button.
         */
        void SetPosition(float x, float y);

        /*
         * Sets the button to cause the level to game over or not when clicked.
         *
         * @param restartOnClick - whether the level should "game over" when the button is clicked.
         *      Either way, the level will "complete" when the button is clicked.
         */
        void SetBehaivor(bool restartOnClick);

    // Helper methods
    private:
        /*
         * Changes the size of the button box so that it compeltely fits the text.
         */
        void ResizeButtonBox();

};

#endif