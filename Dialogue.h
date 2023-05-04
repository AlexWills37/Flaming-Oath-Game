/* Dialogue.h
 *
 * Defines the classes needed for creating dialogue.
 */

#ifndef _DIALOGUE_H
#define _DIALOGUE_H
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

// This is a single unit of dialogue for the Dialogue class. It
// specifies the name of the person speaking, the text being spoken.
class TextObject {
    friend class Dialogue;

    private:
        std::string speaker;
        std::string speech;
    
    public:
        TextObject();
        TextObject(std::string speaker, std::string speech);

        TextObject* SetPosition(int pos);
};

// A dialogue system is a single entity that allows the player to click through text.
class Dialogue: public Entity {

    // Member variables
    private:
        std::string displayedText;

        sf::Font * font;
        sf::Text * text;

        std::vector<TextObject*> dialogue;
        int currentSpeech;

        bool spacePressed;

    public:
        Dialogue();
        Dialogue(sf::RenderWindow * window);

    public:
        void InitializeDialogue(std::vector<TextObject*> dialogue);
        void Update();
        void Draw();
};


#endif