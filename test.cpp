/* test.cpp
 *
 * The main source file for our game!
 *
 * Music credit to https://patrickdearteaga.com
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
#include "PauseScreen.h"
#include "HealthBar.h"
#include "Time.h"
#include "InputManager.h"
#include "Level.h"
#include "Dialogue.h"

Level * LoadStory1(sf::RenderWindow * window) {
    Level * level = new Level();
    
    Dialogue * dialogueSystem = new Dialogue(window);
    std::vector<TextObject*> dialogue = {
        new TextObject("???", ""),
        new TextObject("Villager", "Why... Why.. are the dragons attacking...")
    };
    dialogueSystem->InitializeDialogue(dialogue);
    level->AddEntity(dialogueSystem);

    return level;
}



int main()
{
    // ****** Variables to configure the game ******* //
    float movementSpeed = 1000;
    float fps = 60;

    // ********************************************** //
    std::cout << "! Loading game..." << std::endl;

    // Open Window
    sf::RenderWindow window(sf::VideoMode(1280, 1024), "Game");

    // Set up background
    sf::Texture spaceBGTexture;
    spaceBGTexture.setRepeated(true);
    spaceBGTexture.loadFromFile("./assets/sprites/SpaceBG.png");
    sf::Sprite spaceBackground;
    spaceBackground.setTextureRect(sf::IntRect(0, 0, 1280 * 2, 1024));
    spaceBackground.setTexture(spaceBGTexture);
    window.draw(spaceBackground);

    // Set up text
    sf::Font font;
    font.loadFromFile("./assets/fonts/ShadowsIntoLight-Regular.ttf");
    sf::Text text;
    text.setFont(font);
    text.setPosition(window.getSize().x / 2 - 140, 0);
    text.setCharacterSize(60);
    text.setFillColor(sf::Color(0, 200, 123));
    text.setString("Score: undefined");

    // Load music
    sf::Music music;
    if (!music.openFromFile("./assets/music/Goliath's Foe.ogg"))
    {
        std::cout << "ERROR" << std::endl;
    }
    music.play();

    // Set up health bar
    sf::Texture emptyHearts;
    emptyHearts.loadFromFile("./assets/sprites/Empty Hearts.png");
    sf::Texture filledHearts;
    filledHearts.loadFromFile("./assets/sprites/Filled Hearts.png");
    HealthBar playerHealth = HealthBar(&window, &emptyHearts, &filledHearts);


    // Set up Player
    sf::Texture playerTexture;
    sf::Texture spellTexture;
    sf::Texture healTexture;
    spellTexture.loadFromFile("./assets/sprites/wizard-fire.png");
    healTexture.loadFromFile("./assets/sprites/3/1.png");
    playerTexture.loadFromFile("./assets/sprites/WizardSprite.png");
    Player wizard = Player(&window, &playerTexture, &playerHealth, &spellTexture, &healTexture);


    // Create dragon
    HealthBar dragonHealth = playerHealth;
    sf::Texture dragonTexture, fireTexture;
    dragonTexture.loadFromFile("./assets/sprites/0001.png");
    fireTexture.loadFromFile("./assets/sprites/dragon-fire.png");
    Dragon dragon = Dragon(&window, &dragonTexture, &fireTexture, &wizard, &dragonHealth);

    // Create pause screen
    sf::Texture pauseTexture;
    pauseTexture.loadFromFile("./assets/sprites/paused.png");
    PauseScreen pauseScreen = PauseScreen(&window, &pauseTexture);

    // Objects for keeping track of time
    float timeBtwnFrames = 1.0 / fps;
    sf::Clock *frameClock = Time::GetInstance()->GetClock();

    // Configure input
    InputManager * input = InputManager::GetInputManager();
    input->SetGraphicsWindow(&window);

    // Level 1: First dragon fight
    Level easyFightLevel = Level();
    easyFightLevel.SetWindow(&window);
    std::vector<Entity*> easyEntities = {&wizard, &dragon};
    std::vector<sf::Sprite*> easySprites = {&spaceBackground};
    for (Entity * e : easyEntities) {
        easyFightLevel.AddEntity(e);
    }
    for (sf::Sprite * s : easySprites) {
        easyFightLevel.AddSprite(s);
    }


    Level* intro = LoadStory1(&window);

    int draghealth = 5;

    std::cout << "! Game loaded." << std::endl;
    // Keep window open
    while (window.isOpen())
    {

        // Do frames by time
        if (frameClock->getElapsedTime().asSeconds() >= timeBtwnFrames)
        {
            // When it is time for a frame, "do" the frame and reset the clock for the next frame
            Time::GetInstance()->ResetTime();
            //Test collision for fire spel;
            for (int i = 0; i < wizard.maxSpells; i++){
                if (!(wizard.spells[i].offScreen1) && wizard.spells[i].getGlobalBounds().intersects(dragon.getGlobalBounds()))
                {
                    draghealth = draghealth - 1;
                    dragon.ChangeHealth(-1);
                    wizard.spells[i].offScreen1 = true;
                    //std::cout<< "Collision\n";
                    //std::cout<< "Dragon Health: "<< draghealth<<std::endl;
                }
            }
            //Test collitison for heal spell
            for (int i = 0; i < wizard.maxSpells; i++){
                if (!(wizard.spells2[i].offScreen1) && wizard.spells2[i].getGlobalBounds().intersects(dragon.getGlobalBounds()))
                {
                    draghealth = draghealth - 1;
                    wizard.ChangeHealth(1);
                    dragon.ChangeHealth(-1);
                    wizard.spells2[i].offScreen1 = true;
                    //std::cout<< "Collision\n";
                    //std::cout<< "Dragon Health: "<< draghealth<<std::endl;
                }
            }

            window.clear();
            wizard.Draw();
    
            easyFightLevel.HandleInputs();
            easyFightLevel.UpdateEntities();
            easyFightLevel.DrawSprites();
            // intro->HandleInputs();
            // intro->UpdateEntities();
            // intro->DrawSprites();

            // Render the frame
            // // ******** Draw the frame here ********
            // // **---------------------------------**
            // window.draw(spaceBackground);
            // window.draw(text);
            // dragon.Draw();
            // playerHealth.Draw();
            // // **---------------------------------**
            // // *************************************
            window.display();


            // See if the game is over
            if (wizard.GetHealth() <= 0 || draghealth <= 0)
            {
                window.close();
            }

            // Reset clock for next frame
            frameClock->restart();
        }   // End of code for 1 frame
    }   // End of game; window is closed

    std::cout << "! Game closed." << std::endl;
    return 0;
}