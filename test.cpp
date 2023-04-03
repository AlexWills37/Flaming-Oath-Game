#include <SFML/Graphics.hpp>
#include<iostream>
#include<SFML/Audio.hpp>



int main()
{
    std::cout << "! Starting program..." << std::endl;

    // Open Window
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Game");


    // Set up texture and sprite
    sf::Texture wizard_texture;
    wizard_texture.loadFromFile("./assets/sprites/WizardSprite.png");
    sf::Sprite wizard(wizard_texture);


    // Set up text
    sf::Font font;
    font.loadFromFile("./assets/fonts/ShadowsIntoLight-Regular.ttf");
    sf::Text text;
    text.setFont(font);
    text.setPosition(window.getSize().x / 2 - 100, 0);
    text.setCharacterSize(60);
    text.setFillColor(sf::Color::Blue);
    text.setString("Testing");


    window.draw(wizard);

    // Keep window open
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }


        // Render the frame
        window.clear();
        // ******** Draw the frame here ********
        // **---------------------------------**
        window.draw(wizard);
        window.draw(text);

        // **---------------------------------**
        // *************************************
        window.display();
    }




    std::cout << "! Program finished!" << std::endl;
    return 0;
}