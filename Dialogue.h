/* Dialogue.h
 *
 * Defines the classes needed for creating dialogue (TextObject, Dialogue).
 * 
 * To create a dialogue level, you need a Dialogue entity, which stores TextObjects.
 *  - Create the Dialogue entity with 
 *          Dialogue(sf::RenderWindow * window, sf::Texture * dialogueBox, Level * associatedLevel);
 * 
 *  - Create the dialogue itself as a vector of TextObject*s:
 *          std::vector<TextObject*> dialogue = {
 *              (new TextObject("Speaker1", "Text1")),
 *              (new TextObject("Speaker2", "Text2"))
 *          };
 * 
 *  - Add any features to the text objects during initialization:
 *          std::vector<TextObject*> dialogue = {
 *              (new TextObject("Speaker1", "Text1"))->RequireAction(sf::Keyboard::J),
 *              (new TextObject("Speaker2", "Text2"))->ChangeBackground("coolbackground.png")
 *          };
 * 
 *  - (Note: you can also chain multiple features together):
 *          std::vector<TextObject*> dialogue = {
 *              (new TextObject("Speaker1", "Text1"))
 *                  ->RequireAction(sf::Keyboard::J)->ChangeBackground("coolbackground.png"),
 *              (new TextObject("Speaker2", "Text2"))
 *          };
 * 
 *  - Add the dialogue to the Dialogue entity with
 *          InitializeDialogue(std::vector<TextObject*>);
 * 
 *  - Add any avatars for speakers with
 *          AddAvatar(string name, sf::Texture* avatar)
 * 
 *  - Add the Dialogue entity to the Level object, which you can now load to do the dialogue level!
 * 
 * @author Alex Wills
 */

#ifndef _DIALOGUE_H
#define _DIALOGUE_H
#include "entity.h"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Level.h"

/* This is a single unit of dialogue for the Dialogue class. It
 * specifies the name of the person speaking, the text being spoken,
 * and any modifications (requiring the user to press a certain key,
 * changing the background). 
 */
class TextObject {
    friend class Dialogue;

    // Static variables
    private:
        static const int charactersPerLine = 65;    // How many characters at most before a line break

    // Private member variables (visible to the Dialogue class)
    private:    
        std::string speaker;    // The character speaking
        std::string speech;     // The thing the character says

        bool isActionRequired = false;  // Whether this TextObject should require special input before continuing
        sf::Keyboard::Key actionRequired;   // The special input this TextObject may require

        bool changeBackground = false;  // Whether the background should change when this text is laoded
        sf::Texture * background;       // The background to change to
        

    // Public constructors/methods
    public:
        /*
         * Default constructor. Initializes an empty text object.
         */
        TextObject();

        /*
         * Constructs a TextObject for the Dialogue system.
         *
         * @param speaker (string) - the name of the speaker
         * @param speech (string) - the text that the speaker says
         */        
        TextObject(std::string speaker, std::string speech);

        /*
         * Adds a requirement for the player to press a certain key before this TextObject is finished.
         *
         * @param action - the key that the player must press to continue the dialogue
         * @return - a pointer to this object (used for chaining additions to this object on initialization)
         */
        TextObject* RequireAction(sf::Keyboard::Key action);

        /*
         * Adds a rule for the Dialogue system to change the background when this TextObject is first loaded.
         *
         * @param backgroundFilepath (string) - the filepath of the background texture to load
         * @return - a pointer to this object (used for chaining additions to this object on initialization)
         */
        TextObject* ChangeBackground(std::string backgroundImagePath);

    // Private helper methods
    private:
        /*
         * Adds line breaks to the text so that everything fits in the text box.
         */
        void FitTextbox();
};

/* 
 * A dialogue system is a single entity that allows the player to click through text.
 * See the header comment in Dialogue.h for detailed usage information.
 */
class Dialogue: public Entity {

    // Member variables
    private:

        // Screen background
        sf::Sprite backgroundSprite;

        std::string displayedText;  // Currently displayed text
        sf::Text * text;    // Text object with current text
        sf::Font * font;    // Font for text
        sf::Text * name;    // The speaker's name

        std::vector<TextObject*> dialogue;  // List of all dialogue TextObjects
        int currentSpeech;  // The current index in the dialogue we are at

        bool spacePressed;  // True if space is pressed

        float elapsedTime = 0;  // Cumulative time across multiple frames

        // Avatars
        std::map<std::string, Entity*> avatars; // Map of character names to avatars
        sf::Texture * avatarBoxTexture; // Avatar GUI texture
        sf::Sprite * avatarBoxSprite;   // Avatar GUI sprite

        // Progress text infographics
        sf::Texture * pressSpaceTexture;    
        sf::Sprite pressSpaceSprite;    // Sprite that shows when the current dialogue is complete
        sf::Texture * toContinueTexture;    
        sf::Sprite toContinueSprite;    // Sprite that toggles on and off when the current dialogue is complete
        bool displayInfo = false;
        float infoTimer = 0;

        Level * level;  // The level this dialogue is attached to (that we can complete when the dialogue is finished)

    public:
        Dialogue();
        /*
         * Constructs a Dialouge entity, capable of managing dialogue between many characters.
         *
         * @param window - pointer to the game window
         * @param dialogueBox - pointer to the texture used for the dialogue box
         * @param associatedLevel - pointer to the level this dialogue will be added to (used for progressing the level)
         * @return a Dialogue entity ready to accept dialogue with the InitializeDialogue() method.
         */
        Dialogue(sf::RenderWindow * window, sf::Texture * dialogueBox, Level * associatedLevel);

    public:
        /*
         * Adds dialogue to this system. Also fits the dialogue to the class's line width limit.
         * 
         * @param dialogue - vector of TextObject pointers with every line of dialogue in order
         */
        void InitializeDialogue(std::vector<TextObject*> dialogue);
       
        /*
         * Creates a connection between a speaker's name and the texture to display for their avater.
         *
         * @param name (string) - the name of the speaker
         * @param texture (sf::Texture*) - the texture to display when the speaker talks
         */
        void AddAvatar(std::string name, sf::Texture * texture);
        
        void Update();
        void Draw();

    private:
        /*
         * Adds one more character from the currently selected piece of dialogue, to the currently
         * displayed text.
         */
        void ShowOneMoreCharacter();

        /*
         * Move on from the current dialogue to the next one.
         */
        void ProgressDialogue();
};


#endif