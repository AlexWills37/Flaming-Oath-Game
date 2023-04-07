#include <SFML/Graphics.hpp>
#include<iostream>
#include<SFML/Audio.hpp>

#include <vector>

#include "dragon.h"
#include "player.h"


int main()
{
    float movementSpeed = 10;
    std::cout << "! Starting program..." << std::endl;

    // Open Window
    sf::RenderWindow window(sf::VideoMode(1280, 1024), "Game");


    // Set up Player
    Player wizard = Player();
    std::cout << "Starting score: " << wizard.GetScore() << std::endl;

    // Set up background
    sf::Texture spaceBGTexture;
    // TODO: Set repeating texture
    spaceBGTexture.setRepeated(true);   
    spaceBGTexture.loadFromFile("./assets/sprites/SpaceBG.png");
    sf::Sprite spaceBackground(spaceBGTexture);
    // spaceBackground.setTextureRect();  // TODO: THIS
    spaceBackground.setScale(3, 3);
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
    if( !music.openFromFile("./assets/music/hollow_knight.ogg")){
        std::cout<<"ERROR"<<std::endl;
    }
    // music.play();

    // Create dragon
    Dragon enemy1 = Dragon();



    bool movingLeft = false;
    bool movingRight = false;


    float fps = 60;

    float timeBtwnFrames = 1.0 / fps;
    sf::Clock frameClock;
    sf::Event event;
    
    std::vector<DragonFire> fires;

    int frameCount = 0;


    // Keep window open
    while (window.isOpen())
    {

        // Do frames by time
        if (frameClock.getElapsedTime().asSeconds() >= timeBtwnFrames) {
            // When it is time for a frame, reset the clock and "do" the frame
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
                }
                    // Register if a key is released
                else if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::A) {
                        movingLeft = false;
                    }
                    else if (event.key.code == sf::Keyboard::D) {
                        movingRight = false;
                    }
                }

            }   // Input has been handled





            // Move characters
            if (movingLeft && !movingRight) {
                wizard.MovePlayer(-movementSpeed, 0);
            } else if (movingRight && !movingLeft) {
                wizard.MovePlayer(movementSpeed, 0);
            }

            // Move the dragon and fire
            enemy1.MoveRandomly();


            // Update the game states
            wizard.FrameUpdate();

            // Show the score
        
            text.setString("Score: " + std::to_string(wizard.GetScore()));
            

            // Render the frame
            window.clear();
            // ******** Draw the frame here ********
            // **---------------------------------**
            window.draw(spaceBackground);
            window.draw(wizard.sprite);
            window.draw(text);
            window.draw(enemy1.sprite);

            fires = enemy1.GetFires();
            for (int i = 0; i < fires.size(); i++) {
                window.draw(fires[i].sprite);
            }

            // **---------------------------------**
            // *************************************
            window.display();

            // Reset clock for next frame
            frameClock.restart();
        }

        
    }




    std::cout << "! Program finished!" << std::endl;
    return 0;
}