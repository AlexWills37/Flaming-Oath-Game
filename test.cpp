#include <SFML/Graphics.hpp>
#include<iostream>
#include<SFML/Audio.hpp>



int main()
{
    float movementSpeed = 2;
    std::cout << "! Starting program..." << std::endl;

    // Open Window
    sf::RenderWindow window(sf::VideoMode(1280, 1024), "Game");


    // Set up texture and sprite
    sf::Texture wizard_texture;
    wizard_texture.loadFromFile("./assets/sprites/WizardSprite.png");
    sf::Sprite wizard(wizard_texture);
    wizard.setPosition(300, 500);
    wizard.setOrigin(38, 132);

    // Set up background
    sf::Texture spaceBGTexture;
    // TODO: Set repeating texture
    spaceBGTexture.setRepeated(true);   
    spaceBGTexture.loadFromFile("./assets/sprites/SpaceBG.png");
    sf::Sprite spaceBackground(spaceBGTexture);
    spaceBackground.setTextureRect();  // TODO: THIS
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
    text.setString("Testing");

    // Load music
    sf::Music music;
    if( !music.openFromFile("./assets/music/hollow_knight.ogg")){
        std::cout<<"ERROR"<<std::endl;
    }
    music.play();



    window.draw(wizard);

    bool movingLeft = false;
    bool movingRight = false;

    // Keep window open
    while (window.isOpen())
    {
        sf::Event event;
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

        // Move the sprite
        if (movingLeft && !movingRight) {
            wizard.move(-movementSpeed, 0);
            wizard.setScale(-1, 1);
            text.setString("Moving Left!");
        } else if (movingRight && !movingLeft) {
            wizard.move(movementSpeed, 0);
            wizard.setScale(1, 1);
            text.setString("Moving Right!");
        }
        else {
            text.setString("Not Moving!");
        }


        // Render the frame
        window.clear();
        // ******** Draw the frame here ********
        // **---------------------------------**
        window.draw(spaceBackground);
        window.draw(wizard);
        window.draw(text);

        // **---------------------------------**
        // *************************************
        window.display();
    }




    std::cout << "! Program finished!" << std::endl;
    return 0;
}