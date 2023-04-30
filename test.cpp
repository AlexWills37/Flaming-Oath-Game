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
    playerTexture.loadFromFile("./assets/sprites/WizardSprite.png");
    Player wizard = Player(&window, &playerTexture, &playerHealth);
    bool movingLeft = false;
    bool movingRight = false;
    wizard.EnableFollowingHealthBar(sf::Vector2f(-75, -200));


    // Create dragon
    sf::Texture dragonTexture, fireTexture;
    dragonTexture.loadFromFile("./assets/sprites/0001.png");
    fireTexture.loadFromFile("./assets/sprites/dragon-fire.png");
    Dragon dragon = Dragon(&window, &dragonTexture, &fireTexture, &wizard);

    // Create pause screen
    sf::Texture pauseTexture;
    pauseTexture.loadFromFile("./assets/sprites/paused.png");
    PauseScreen pauseScreen = PauseScreen(&window, &pauseTexture);

    // Objects for keeping track of time
    float timeBtwnFrames = 1.0 / fps;
    sf::Clock *frameClock = Time::GetInstance()->GetClock();
    sf::Event event;
    int frameCount = 0;
    float deltaTime;

    // Things for pausing the game
    bool paused = false;
    bool escape_pressed = false;
    bool mouseClicked = false;
    bool mouseClickComplete = false;
    sf::Vector2i mousePosition;

    // Set up input
    InputManager *input = InputManager::GetInputManager();
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

    float test = 0;
    int test2 = 0;

    std::cout << "! Game loaded." << std::endl;
    // Keep window open
    while (window.isOpen())
    {

        // Do frames by time
        if (frameClock->getElapsedTime().asSeconds() >= timeBtwnFrames)
        {
            // When it is time for a frame, "do" the frame and reset the clock for the next frame
            Time::GetInstance()->ResetTime();
            frameCount++;


            window.clear();
            easyFightLevel.HandleInputs();
            easyFightLevel.UpdateEntities();
            easyFightLevel.DrawSprites();

            // Render the frame
            // // ******** Draw the frame here ********
            // // **---------------------------------**
            // window.draw(spaceBackground);
            // window.draw(text);
            // wizard.Draw();
            // dragon.Draw();
            // playerHealth.Draw();
            // // **---------------------------------**
            // // *************************************
            window.display();


            // See if the game is over
            if (wizard.GetHealth() <= 0)
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