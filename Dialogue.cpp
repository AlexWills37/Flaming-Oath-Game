/* Dialogue.cpp
 *
 * Implementation of the Dialogue system used to tell the player story.
 * This includes the Dialogue class and the TextObject class.
 * 
 * @author Alex Wills
 */
#include "Dialogue.h"
#include "InputManager.h"
#include "Time.h"

#include <iostream>


/*
 * Default constructor for dialogue, which should not be called.
 */
Dialogue::Dialogue() {
    std::cout << "This constructor for dialogue should not be called." << std::endl;

}

/*
 * Constructs a Dialouge entity, capable of managing dialogue between many characters.
 *
 * @param window - pointer to the game window
 * @param dialogueBox - pointer to the texture used for the dialogue box
 * @param associatedLevel - pointer to the level this dialogue will be added to (used for progressing the level)
 * @return a Dialogue entity ready to accept dialogue with the InitializeDialogue() method.
 */
Dialogue::Dialogue(sf::RenderWindow * window, sf::Texture * dialogueBox, Level * associatedLevel): Entity(window, dialogueBox) { // We should add Entity superclass things
    
    this->level = associatedLevel;
    currentSpeech = 0;
    
    // Load the font
    font = new sf::Font();
    font->loadFromFile("./assets/fonts/Cabin-Regular.ttf");
    text = new sf::Text();
    text->setFont(*font);
    name = new sf::Text();
    name->setFont(*font);

    // Put the name in the right place
    name->setPosition(75, 920);
    text->setPosition(325, 750);

    // Load avatar box
    avatarBoxTexture = new sf::Texture();
    avatarBoxTexture->loadFromFile("./assets/sprites/avatar_box.png");
    avatarBoxSprite = new sf::Sprite(*avatarBoxTexture);
    avatarBoxSprite->setPosition(59, 738);

    // Set up background
    backgroundSprite = sf::Sprite();

    // Set up graphic to prompt user to continue text
    toContinueTexture = new sf::Texture();
    toContinueTexture->loadFromFile("./assets/sprites/to_continue.png");
    toContinueSprite = sf::Sprite(*toContinueTexture);

    pressSpaceTexture = new sf::Texture();
    pressSpaceTexture->loadFromFile("./assets/sprites/to_continue_text.png");
    pressSpaceSprite = sf::Sprite(*pressSpaceTexture);
}

/*
 * Adds dialogue to this system. Also fits the dialogue to the class's line width limit.
 * 
 * @param dialogue - vector of TextObject pointers with every line of dialogue in order
 */
void Dialogue::InitializeDialogue(std::vector<TextObject*> dialogue) {
    // Fit all of the lines to the textbox based on the class's character limit
    for (TextObject * line : dialogue) {
        line->FitTextbox();
    }
    // Save the dialogue and load the first TextObject
    this->dialogue = dialogue;
    currentSpeech = -1;
    this->ProgressDialogue();
}

/*
 * Adds one character from the current TextObject to the currently displayed text.
 */
void Dialogue::ShowOneMoreCharacter() {

    // Make sure we do not access outside of the array
    if (displayedText.size() >= dialogue[currentSpeech]->speech.size()) {
        std::cout << "all text displayed. we should not call this method" << std::endl;
    } else {
        // If we can, add the next character to the string and update the sf::Text object
        displayedText += dialogue[currentSpeech]->speech[displayedText.size()];
        text->setString(displayedText);
    }
}

/*
 * Erases the current text and begins to show the next TextObject.
 */
void Dialogue::ProgressDialogue() {
    currentSpeech += 1;
    if (currentSpeech >= dialogue.size()) {
        // We have gone through all of the dialogue! Go to the next level.

        level->CompleteLevel();
        currentSpeech = dialogue.size() - 1;

    } else {
        // Next dialogue can be loaded. Reset the displayed text and update the speaker.
        displayedText = "";
        name->setString(dialogue[currentSpeech]->speaker);

        if (dialogue[currentSpeech]->changeBackground) {
            backgroundSprite.setTexture(*(dialogue[currentSpeech]->background), true);
        }
    }
}

/*
 * Creates a connection between a speaker's name and the texture to display for their avater.
 *
 * @param name (string) - the name of the speaker
 * @param texture (sf::Texture*) - the texture to display when the speaker talks
 */
void Dialogue::AddAvatar(std::string name, sf::Texture * texture) {
    Entity * newAvatar = new Entity(window, texture);
    newAvatar->SetPosition(72, 748);
    avatars[name] = newAvatar;  // Add the avatar to the name-texture map
}

/*
 * Overridden Update method to continue text based on time and user input.
 */
void Dialogue::Update() {

    // Get the time since last frame and the status of the Space key
    float deltaTime = Time::GetInstance()->DeltaTime();
    bool space = InputManager::GetInputManager()->IsKeyPressed(sf::Keyboard::Space);
    float characterTime = space ? 0.005 : 0.03;

    elapsedTime += deltaTime;   // Add to a running total between frames to determine when to progress text

    // When it is time to load the next character, do so
    if (elapsedTime > characterTime && displayedText.size() < dialogue[currentSpeech]->speech.size()) {
        this->ShowOneMoreCharacter();
        elapsedTime = 0;
    }

    // Once all text has been loaded, allow the player to continue to the next part
    if (displayedText.size() >= dialogue[currentSpeech]->speech.size()) {
        
        // Update timer for displaying text to move on, to toggle the visual periodically
        infoTimer += deltaTime;
        if (infoTimer > 0.5) {
            displayInfo = !displayInfo; // This info is the little arrow next to "Press [SPACE] to continue"
            infoTimer = 0;
        }

        // Detect a custom action requirement for progressing the text
        if (dialogue[currentSpeech]->isActionRequired) {
            // If the user is pressing the required action...
            if (InputManager::GetInputManager()->IsKeyPressed(dialogue[currentSpeech]->actionRequired)) {
                // ...progress the dialogue!
                this->ProgressDialogue();
            }
        }
        // Otherwise, we will progress dialogue like normal
        // When the player first hits space, progress the dialogue
        else if (!spacePressed && space) { 
            spacePressed = true;
            this->ProgressDialogue();
        // When the player first releases space, allow them to press space later again
        } else if (spacePressed && !space) {
            spacePressed = false;
        } // End of input handling


    // ...If text is still coming in, do not display info for player to move on
    } else {
        displayInfo = false;
        infoTimer = 0;
    } 
}

/*
 * Draws the current text on top of a GUI, including the speaker's name and avatar.
 */
void Dialogue::Draw() {

    // Draw background
    window->draw(backgroundSprite);

    // Draw dialogue
    Entity::Draw();
    window->draw(*avatarBoxSprite);
    window->draw(*text);
    window->draw(*name);

    // Draw avatar if it exists
    if (avatars.count(dialogue[currentSpeech]->speaker) == 0) {
        
    } else {
        avatars[dialogue[currentSpeech]->speaker]->Draw();
    }

    // Display info if needed
    if (!dialogue[currentSpeech]->isActionRequired && displayedText.size() >= dialogue[currentSpeech]->speech.size()) {
        window->draw(pressSpaceSprite);
        if (displayInfo) {
            window->draw(toContinueSprite);
        }
    }
}

/*
 * Default constructor. Initializes an empty text object.
 */
TextObject::TextObject() {
    this->speaker = "none";
    this->speech = "ERROR: Text not found";
}

/*
 * Constructs a TextObject for the Dialogue system.
 *
 * @param speaker (string) - the name of the speaker
 * @param speech (string) - the text that the speaker says
 */
TextObject::TextObject(std::string speaker, std::string speech) {
    this->speaker = speaker;
    this->speech = speech;
}

/*
 * Adds line breaks to the text so that everything fits in the text box.
 */
void TextObject::FitTextbox() {
    std::string newText = "";
    int charactersOnLine = 0;
    bool tooManyChars = false;

    // Process the entire speech
    for (int i = 0; i < speech.size(); ++i)
    {
        // Add the next character to this line
        charactersOnLine++;
        newText += speech[i];


        // If we are past the character limit for the line, replace the last space with a new line
        if (charactersOnLine > TextObject::charactersPerLine) {
            tooManyChars = true;

            // Start working backwards to make a line break
            for (int j = i; j >= 0 && tooManyChars; --j) {
                // If we find a space, replace it with a new line and finish
                if (newText[j] == ' ') {
                    newText[j] = '\n';
                    charactersOnLine = i - j;
                    tooManyChars = false;
                }
            }
        }   // End of backtracking to add a new line character

    }   // End of processing speech

    speech = newText;   // Update the text
}

/*
 * Adds a requirement for the player to press a certain key before this TextObject is finished.
 *
 * @param action - the key that the player must press to continue the dialogue
 * @return - a pointer to this object (used for chaining additions to this object on initialization)
 */
TextObject* TextObject::RequireAction(sf::Keyboard::Key action) {
    isActionRequired = true;
    actionRequired = action;
    return this;
}

/*
 * Adds a rule for the Dialogue system to change the background when this TextObject is first loaded.
 *
 * @param backgroundFilepath (string) - the filepath of the background texture to load
 * @return - a pointer to this object (used for chaining additions to this object on initialization)
 */
TextObject* TextObject::ChangeBackground(std::string backgroundFilepath) {
    changeBackground = true;
    background = new sf::Texture();
    background->loadFromFile(backgroundFilepath);

    return this;
}