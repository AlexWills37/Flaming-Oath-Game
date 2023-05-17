/* test.cpp
 *
 * The main source file for our game, Flaming Oath!
 * In this game, you are a wizard, and your job is to protect the village from evil dragons who spit fire at you.
 * 
 * Credits, resources, and work distribution can be found in the README.md file.
 * 
 * Prerequisites to compile:
 *      - SFML
 *      - C++ compiler
 * 
 * To compile/run:
 *      from this folder run:
 *          make
 *          ./a.out      
 *
 * @author Jhonder Abreus
 * @author Alex Wills
 * @date April 11, 2023
 */
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>

#include <vector>

#include "dragon.h"
#include "player.h"
#include "HealthBar.h"
#include "Time.h"
#include "InputManager.h"
#include "Level.h"
#include "Dialogue.h"
#include "MouseButton.h"

// !+!+!+!+!+!+!+!+!+!+!+!+!+!+!+!+ //
// ! Functions for loading Levels ! //
// !+!+!+!+!+!+!+!+!+!+!+!+!+!+!+!+ //

/*
 * Builds the first story level with dialogue.
 *
 * @param window - a pointer to the window of the game
 * @return (Level*) - a pointer to the first story level
 */
Level * LoadStory1(sf::RenderWindow * window) {
    
    Level * level = new Level();

    // Set up dialogue system
    sf::Texture * dialogueBox = new sf::Texture();
    dialogueBox->loadFromFile("./assets/sprites/dialogue_box.png");

    Dialogue * dialogueSystem = new Dialogue(window, dialogueBox, level);
    // https://ansimuz.itch.io/country-side-platfformer?download
    std::vector<TextObject*> dialogue = {

        (new TextObject("???", "Nearly 1000 years ago, the Noble King of Heiser led humanity's forces into what he had hoped was the last battle."))
            ->ChangeBackground("./assets/sprites/SpaceBG.png"),
        new TextObject("???", "When the dust had settled, Heiser laid down his magic blade and swore that such a violent conflict would never again disturb the land."),
        new TextObject("???", "This promise was kept until only a month ago, when an army of dragons began to wreak havoc on our Realm."),
        new TextObject("???", "Protected only by a population of pacifist farmers who were incapable of combat and not great with magic, the Realm of Heiser seemed to be falling towards oblivion."),
        new TextObject("???", "Answer my call, great mage. Extinguish these flames of suffering. Defeat the dragons and restore the light of Heiser!"),
        (new TextObject("Villager", "You there! You in the purple robe!"))
            ->ChangeBackground("./assets/sprites/forestBG.png"),
        new TextObject("Villager", "I've never seen such an outfit! Could you perhaps be here to save us?"),
        new TextObject("Player", "Err, maybe? I just got here..."),
        new TextObject("Villager", "......"),
        new TextObject("Villager", "Yes! You must be the great wizard! We are in desperate need of someone with strong magic. The best my village can do with magic is lighting a candle..."),
        new TextObject("Player", "Wizard? I suppose that explains my clothes, but I don't know anything about magic, sorry..."),
        (new TextObject("Villager", "Surely it can't be that different than what I do. Let's see... When I light candles, all I do is press \"J\". Maybe it's the same for you? Try pressing \"J\" now!"))
            ->RequireAction(sf::Keyboard::J),
        (new TextObject("Villager", "Woah!!! Definitely a great mage skill. Be careful where you aim that thing! Hah!"))
            ->ChangeBackground("./assets/sprites/fire background.png"),
        (new TextObject("Villager", "Your power is going to be enough to take down the dragons. I believe in you!!"))
            ->ChangeBackground("./assets/sprites/forestBG.png"),
        (new TextObject("Player", "I guess I will try my best!!")),
        (new TextObject("Villager", "No pressure; we are all counting on you.")),
        (new TextObject("Player", "...")),
        (new TextObject("Villager", "Oh! I almost forgot! Try pressing \"A\" to move to the left!"))
            ->RequireAction(sf::Keyboard::A),
        (new TextObject("Villager", "Now press \"D\" to move right!"))
            ->RequireAction(sf::Keyboard::D),
        (new TextObject("Player", "Woah! It feels great to be moving again! Thank you!!")),
        (new TextObject("Villager", "No, thank you-- here comes the first of the evil dragons. Good luck!"))
    };
    dialogueSystem->InitializeDialogue(dialogue);

    // Add avatars for the characters
    sf::Texture * villagerTexture = new sf::Texture();
    sf::Texture * playerTexture = new sf::Texture();
    playerTexture->loadFromFile("./assets/sprites/avatar_wizard.png");
    villagerTexture->loadFromFile("./assets/sprites/avatar_villager.png");
    dialogueSystem->AddAvatar("Villager", villagerTexture);
    dialogueSystem->AddAvatar("Player", playerTexture);

    // Add assets to the level
    level->AddEntity(dialogueSystem); 

    // Add music
    level->AddBackgroundMusic("./assets/music/Voices From Earth.ogg");

    return level;
}

/*
 * Builds the second story level with dialogue.
 *
 * @param window - a pointer to the window of the game
 * @return (Level*) - a pointer to the first story level
 */
Level * LoadStory2(sf::RenderWindow * window) {
    
    Level * level = new Level();

    // Set up dialogue system
    sf::Texture * dialogueBox = new sf::Texture();
    dialogueBox->loadFromFile("./assets/sprites/dialogue_box.png");

    Dialogue * dialogueSystem = new Dialogue(window, dialogueBox, level);
    // https://ansimuz.itch.io/country-side-platfformer?download
    std::vector<TextObject*> dialogue = {

        (new TextObject("Villager", "Woah... Ha ha! You did it! You actually did it!!"))
            ->ChangeBackground("./assets/sprites/forestBG.png"),
        (new TextObject("Player", "Heh, I guess you're right! I could get used to this whole magic thing.")),
        (new TextObject("Villager", "How do you feel?")),
        (new TextObject("Player", "I feel great! *cough*")),
        (new TextObject("Player", "Okay... maybe I am a bit injured.")),
        (new TextObject("Villager", "You can probably use healing magic, now that you've gained some fighting experience.")),
        (new TextObject("Player", "There is HEALING MAGIC? Why didn't you tell me sooner?")),
        (new TextObject("Villager", "I'm sorry! If you recall, there was a DRAGON coming towards us?")),
        (new TextObject("Player", "...")),
        (new TextObject("Player", "Alright, I forgive you, I guess. So how do I use healing magic? Is it another button I have to press?")),
        (new TextObject("Villager", "Verily. It's like you know my thoughts exactly. Try pressing \"K\"."))
            ->RequireAction(sf::Keyboard::K),
        (new TextObject("Player", "What is this???")),
        (new TextObject("Villager", "Ah yes---I forget, you know nothing of magic. You cannot just heal out of thin air. In order to heal, you must steal.")),
        (new TextObject("Villager", "When your healing spell hits an enemy, it will drain some of their life and bring it to you.")),
        (new TextObject("Player", "That seems... scary...")),
        (new TextObject("Villager", "Think of it this way: you damage the dragons, AND you heal yourself. It's a win-win!")),
        (new TextObject("Player", "Watch out!! Another dragon is coming!")),
        (new TextObject("Villager", "Don't give up! And remember to heal yourself!"))
        
    };
    dialogueSystem->InitializeDialogue(dialogue);

    // Add avatars for the characters
    sf::Texture * villagerTexture = new sf::Texture();
    sf::Texture * playerTexture = new sf::Texture();
    playerTexture->loadFromFile("./assets/sprites/avatar_wizard.png");
    villagerTexture->loadFromFile("./assets/sprites/avatar_villager.png");
    dialogueSystem->AddAvatar("Villager", villagerTexture);
    dialogueSystem->AddAvatar("Player", playerTexture);

    // Add assets to the level
    level->AddEntity(dialogueSystem); 

    // Add music
    level->AddBackgroundMusic("./assets/music/Voices From Earth.ogg");

    return level;
}

/*
 * Builds the first dragon fight level.
 * 
 * @param window - pointer to the game's window
 * @return (Level*) - the first dragon fight level
 */
Level* LoadDragonFight1(sf::RenderWindow * window) {
    Level * level = new Level();

    // Set up background
    sf::Texture * spaceBGTexture = new sf::Texture();
    spaceBGTexture->loadFromFile("./assets/sprites/SpaceBG.png");
    sf::Sprite * spaceBGSprite = new sf::Sprite(*spaceBGTexture);

    // Set up health bars
    sf::Texture * emptyHearts = new sf::Texture();
    emptyHearts->loadFromFile("./assets/sprites/Empty Hearts.png");
    sf::Texture * filledHearts = new sf::Texture();
    filledHearts->loadFromFile("./assets/sprites/Filled Hearts.png");
    HealthBar * playerHealth = new HealthBar(window, emptyHearts, filledHearts);
    HealthBar * dragonHealth = new HealthBar(*playerHealth); // Create a copy  for the dragon health

    // Set up player
    sf::Texture * playerTexture = new sf::Texture();
    sf::Texture * spellTexture = new sf::Texture();
    sf::Texture * healTexture = new sf::Texture();
    spellTexture->loadFromFile("./assets/sprites/wizard-fire.png");
    healTexture->loadFromFile("./assets/sprites/3/Magic Pack 9 files(1)/Magic Pack 9 files/sprites/Lightning/Lightning2.png");
    playerTexture->loadFromFile("./assets/sprites/WizardSprite.png");
    Player * wizard = new Player(window, playerTexture, playerHealth, spellTexture, healTexture);
    wizard->SetLevel(level);

    // Set up dragon
    sf::Texture * dragonTexture = new sf::Texture();
    sf::Texture *  fireTexture = new sf::Texture();
    dragonTexture->loadFromFile("./assets/sprites/0001.png");
    fireTexture->loadFromFile("./assets/sprites/dragon-fire.png");
    Dragon * dragon = new Dragon(window, dragonTexture, fireTexture, wizard, dragonHealth);

    wizard->setDragon(dragon);
    

    // Add assets to the level
    level->AddSprite(spaceBGSprite);
    level->AddEntity(wizard);
    level->AddEntity(dragon);

    level->SetWindow(window);

    return level;
}

/*
 * Builds the pause screen "level".
 * This level is very lightweight and can be quickly swapped with the currently
 * active level to pause the game. From this level, the player can continue or quit the game.
 * "Continue" is represented by "completing the level", and "quit/restart" is represented
 * by causing this level to "Game over". These conditions can be checked by 
 *      level->IsComplete()     // true when any option is chosen
 *      level->IsGameOver()     // true when the quit/restart option is chosen
 * 
 * @param window - pointer to the game window
 * @return (Level*) - the pause screen level
 */
Level* LoadPauseScreen(sf::RenderWindow * window) {
    Level * pauseLevel = new Level();
    pauseLevel->SetWindow(window);

    // Load background
    sf::Texture * bgTexture = new sf::Texture();
    bgTexture->loadFromFile("./assets/sprites/forestPause.png");
    sf::Sprite * bg = new sf::Sprite(*bgTexture);
    pauseLevel->AddSprite(bg);



    // Add buttons
    sf::Font* font = new sf::Font();
    font->loadFromFile("./assets/fonts/Cabin-Regular.ttf");
    MouseButton * quitButton = new MouseButton(window, font, "Return to Title", pauseLevel);
    quitButton->SetPosition(200, 500);
    quitButton->SetBehaivor(true);  // When this button is pressed, the level's Game Over flag will be set to true
    pauseLevel->AddEntity(quitButton);

    MouseButton * continueButton = new MouseButton(window, font, "Continue Game", pauseLevel);
    continueButton->SetBehaivor(false);
    continueButton->SetPosition(700, 500);
    pauseLevel->AddEntity(continueButton);

    return pauseLevel;
}

/*
 * Builds the title screen level.
 *
 * @param window - pointer to the game window
 * @return (Level*) - the title screen level
 */
Level * LoadTitleScreen(sf::RenderWindow* window) {
    Level * level = new Level();
    level->SetWindow(window);

    // Add background
    sf::Texture * background = new sf::Texture();
    background->loadFromFile("./assets/sprites/title.png");
    sf::Sprite * backgroundSprite = new sf::Sprite(*background);
    level->AddSprite(backgroundSprite);
    
    // Add the "start game" button
    sf::Font* font = new sf::Font();
    font->loadFromFile("./assets/fonts/Cabin-Regular.ttf");
    MouseButton * startButton = new MouseButton(window, font, "Start Game!", level);
    startButton->SetPosition(500, 600);
    startButton->SetBehaivor(false);
    level->AddEntity(startButton);

    // Add music
    level->AddBackgroundMusic("./assets/music/Goliath's Foe.ogg");

    return level;
}

/*
 * Builds the game over screen.
 *
 * @param window - pointer to the game window
 * @return (Level*) - the game over screen level
 */
Level * LoadGameOverScreen(sf::RenderWindow* window) {
    Level * level = new Level();
    level->SetWindow(window);

    // Add background
    sf::Texture * background = new sf::Texture();
    background->loadFromFile("./assets/sprites/game over.png");
    sf::Sprite * backgroundSprite = new sf::Sprite(*background);
    level->AddSprite(backgroundSprite);

    // Add the restart button
    sf::Font* font = new sf::Font();
    font->loadFromFile("./assets/fonts/Cabin-Regular.ttf");
    MouseButton * restartButton = new MouseButton(window, font, "Back to Title Screen", level);
    restartButton->SetPosition(400, 500);
    restartButton->SetBehaivor(false);
    level->AddEntity(restartButton);

    // Add music
    level->AddBackgroundMusic("./assets/music/I Miss You.ogg");

    return level;
}

/*
 * Builds the Game complete screen.
 *
 * @param window - pointer to the game window
 * @return (Level*) - the game over screen level
 */
Level * LoadVictoryScreen(sf::RenderWindow* window) {
    Level * level = new Level();
    level->SetWindow(window);

    // Add background
    sf::Texture * background = new sf::Texture();
    background->loadFromFile("./assets/sprites/win.png");
    sf::Sprite * backgroundSprite = new sf::Sprite(*background);
    level->AddSprite(backgroundSprite);

    // Add the restart button
    sf::Font* font = new sf::Font();
    font->loadFromFile("./assets/fonts/Cabin-Regular.ttf");
    MouseButton * restartButton = new MouseButton(window, font, "Back to Title Screen", level);
    restartButton->SetPosition(400, 500);
    restartButton->SetBehaivor(false);
    level->AddEntity(restartButton);

    // Add music
    level->AddBackgroundMusic("./assets/music/No Place For Straw Cowboys.ogg");

    return level;
}


// !+!+!+!+!+!+!+!+!+!+!+!+!+!+!+!+ //
// !      Main gameplay loop      ! //
// !+!+!+!+!+!+!+!+!+!+!+!+!+!+!+!+ //


int main()
{
    // ****** Variables to configure the game ******* //

    float fps = 60;

    // ********************************************** //
    std::cout << "! Loading game..." << std::endl;

    // Open Window
    sf::RenderWindow window(sf::VideoMode(1280, 1024), "Game");

    // Objects for keeping track of time
    float timeBtwnFrames = 1.0 / fps;
    sf::Clock *frameClock = Time::GetInstance()->GetClock();

    // Initialize input manager for detecting input
    InputManager * input = InputManager::GetInputManager();
    input->SetGraphicsWindow(&window);

    // Load the first level
    Level * currentLevel = LoadTitleScreen(&window);
    int levelIndex = 0;


    // Create the pause screen
    bool paused = false;    // True when the game should be paused
    bool gameOver = false;
    bool escapePressed = false; // Used to detect the first escape press (debouncing)
    Level * const pauseScreen = LoadPauseScreen(&window); // The actual pause screen
    Level * pausedLevel = nullptr;  // Stores the level that is paused so it can be quickly swapped


    std::cout << "! Game loaded." << std::endl;
    // Keep window open
    while (window.isOpen())
    {

        // When it is time for a frame, "do" the frame and reset the clock for the next frame
        if (frameClock->getElapsedTime().asSeconds() >= timeBtwnFrames)
        {

            // This stores the time since the last frame in Time::GetInstance()->DeltaTime();
            Time::GetInstance()->ResetTime();


            // Check if the game should be paused by looking at the first time
            // the escape key is pressed down
            if (input->IsKeyPressed(sf::Keyboard::Escape) && !escapePressed) {
                escapePressed = true;
                paused = !paused;

                // Swap the current level and the pause screen
                if (paused) {
                    pausedLevel = currentLevel;
                    currentLevel = pauseScreen;
                } else {
                    currentLevel = pausedLevel;
                }

            } else if (!input->IsKeyPressed(sf::Keyboard::Escape) && escapePressed) {
                escapePressed = false;
            } 

            // See if the level is complete, and move to the next one
            if (currentLevel->IsComplete()) {
                
                // If the pause screen is completed (button press), either continue the current level or go back to the start.
                if (paused && currentLevel->IsGameOver()) {
                    // Restart the game
                    levelIndex = 0;
                    std::cout << "! Restarting to the title screen..." << std::endl;
                    delete pausedLevel;
                    currentLevel = LoadTitleScreen(&window);
                    std::cout << "! Title screen loaded." << std::endl; 
                    paused = false;
                    pauseScreen->ResetLevel();

                } else if (paused) {
                    // Unpause the game
                    currentLevel = pausedLevel;
                    paused = false;
                    pauseScreen->ResetLevel();
                
                // If a regular level is complete, either continue to the next level or go to game over screen
                } else if (currentLevel->IsGameOver()) {
                    
                    // Game over! Go to the game over screen
                    std::cout << "! Game over! Loading game over screen..." << std::endl;
                    delete currentLevel;
                    currentLevel = LoadGameOverScreen(&window);
                    gameOver = true;

                    std::cout << "! Game over screen loaded." << std::endl;
                }
                
                else {
                    // Level is finished, go to next one!
                    levelIndex += 1;
                    // If the player finishes the game over level, return to title screen
                    if (gameOver) {
                        levelIndex = 0;
                        gameOver = false;
                    }
                    std::cout << "! Loading level " << levelIndex << "..." << std::endl;
                    delete currentLevel;

                    // Load the next level
                    switch (levelIndex) {
                        case 0:
                            currentLevel = LoadTitleScreen(&window);
                            break;
                        case 1:
                            // currentLevel = LoadGameOverScreen(&window);
                            currentLevel = LoadStory1(&window);
                            break;
                        case 2:
                            currentLevel = LoadDragonFight1(&window);
                            break;
                        
                        case 3:
                            currentLevel = LoadStory2(&window);
                            break;

                        default:
                            currentLevel = LoadVictoryScreen(&window);
                            gameOver = true;
                            break;
                    }
                    std::cout << "! Level " << levelIndex << " loaded." << std::endl;


                }
            

            }   // End of code for completing a level

            // Update the level
            window.clear();
            currentLevel->HandleInputs();
            currentLevel->UpdateEntities();
            currentLevel->DrawSprites();
            window.display();




        }   // End of code for 1 frame
    }   // End of game; window is closed

    std::cout << "! Game closed." << std::endl;
    return 0;
}