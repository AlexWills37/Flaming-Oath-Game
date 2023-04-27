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
#include<iostream>
#include<SFML/Audio.hpp>

#include <vector>

#include "dragon.h"
#include "player.h"
#include "PauseScreen.h"
#include "HealthBar.h"
#include "Time.h"



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
    if( !music.openFromFile("./assets/music/Goliath's Foe.ogg")){
        std::cout<<"ERROR"<<std::endl;
    }
    music.play();

    // Set up Player
    sf::Texture playerTexture;
    playerTexture.loadFromFile("./assets/sprites/WizardSprite.png");
    Player wizard = Player(&window, &playerTexture);
    bool movingLeft = false;
    bool movingRight = false;

    // Set up health bar
    sf::Texture emptyHearts;
    emptyHearts.loadFromFile("./assets/sprites/Empty Hearts.png");
    sf::Texture filledHearts;
    filledHearts.loadFromFile("./assets/sprites/Filled Hearts.png");
    HealthBar playerHealth = HealthBar(&window, &emptyHearts, &filledHearts);

    // Create dragon
    sf::Texture dragonTexture, fireTexture;
    dragonTexture.loadFromFile("./assets/sprites/0001.png");
    fireTexture.loadFromFile("./assets/sprites/dragon-fire.png");
    Dragon dragon = Dragon(&window, &dragonTexture, &fireTexture);


    // Create pause screen
    sf::Texture pauseTexture;
    pauseTexture.loadFromFile("./assets/sprites/paused.png");
    PauseScreen pauseScreen = PauseScreen(&window, &pauseTexture);

    
    // Objects for keeping track of time
    float timeBtwnFrames = 1.0 / fps;
    sf::Clock* frameClock = Time::GetInstance()->GetClock();
    sf::Event event;
    int frameCount = 0;
    float deltaTime;

    // Things for pausing the game
    bool paused = false;
    bool escape_pressed = false;
    bool mouseClicked = false;
    sf::Vector2i mousePosition;

    std::cout << "! Game loaded." << std::endl;
    // Keep window open
    while (window.isOpen())
    {

        // Do frames by time
        if (frameClock->getElapsedTime().asSeconds() >= timeBtwnFrames) {
            // When it is time for a frame, reset the clock and "do" the frame
            deltaTime = frameClock->getElapsedTime().asSeconds();
            frameCount++;

            // Process user input
            while (window.pollEvent(event))
            {
                // Register if the window is closed
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                    // Register if a key is pressed
                else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::A) {
                        movingLeft = true;
                    }
                    else if (event.key.code == sf::Keyboard::D) {
                        movingRight = true;
                    }
                    else if (event.key.code == sf::Keyboard::Escape) {
                        if (!escape_pressed) {
                            paused = !paused;
                            escape_pressed = true;
                            mouseClicked = false;   // On escape, unclick the mouse to start
                                                    // This is to make sure that there is no immediate click
                        }
                    }
                }
                    // Register if a key is released
                else if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::A) {
                        movingLeft = false;
                    }
                    else if (event.key.code == sf::Keyboard::D) {
                        movingRight = false;
                    }
                    else if (event.key.code == sf::Keyboard::Escape) {
                        escape_pressed = false;
                    }
                }
                    // Register the end of a mouse click
                else if (event.type == sf::Event::MouseButtonReleased) {
                    mouseClicked = true;
                    mousePosition = sf::Mouse::getPosition(window);
                }   

            }   // Input has been handled

            // Game is paused! Handle possible mouse clicks
            if (paused) {

                if (mouseClicked)
                {
                    PauseScreen::Button command = pauseScreen.click(mousePosition);
                    switch (command)
                    {
                        case PauseScreen::Button::QUIT:
                            window.close();
                            break;
                        deafult:
                            break;
                    }
                    // Once the click has been handled, reset the flag
                    mouseClicked = false;
                }

                window.clear();
                pauseScreen.Draw();
                window.display();
            }
            else {

                // Move characters
                if (movingLeft && !movingRight) {
                    wizard.Move(-movementSpeed * deltaTime, 0);
                } else if (movingRight && !movingLeft) {
                    wizard.Move(movementSpeed * deltaTime, 0);
                }

                // Move the dragon and fire
                dragon.Move();


                // Update the game states
                wizard.FrameUpdate();


                // Check collisions
                dragon.CheckCollision(&wizard);

            
                // Show the score
                text.setString("Health: " + std::to_string(wizard.GetHealth()));
                playerHealth.setHealth(wizard.GetHealth());
                

                // Move the background
                sf::Vector2f pos = spaceBackground.getPosition();
                pos.x -= 5;
                // Once the upper left corner is 1 Window to the left of the screen, move it back
                if (pos.x <= -float(window.getSize().x)) {
                    pos.x += window.getSize().x;
                }
                spaceBackground.setPosition(pos);

                // Render the frame
                window.clear();
                // ******** Draw the frame here ********
                // **---------------------------------**
                window.draw(spaceBackground);
                window.draw(text);
                wizard.Draw();
                dragon.Draw();
                playerHealth.Draw();
                // **---------------------------------**
                // *************************************
                window.display();

                // Reset clock for next frame
                frameClock->restart();

                // See if the game is over
                if (wizard.GetHealth() <= 0)
                {
                    window.close();
                }
            }
        }

        
    }




    std::cout << "! Game closed." << std::endl;
    return 0;
}