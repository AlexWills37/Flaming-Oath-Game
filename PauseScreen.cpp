
#include "PauseScreen.h"

PauseScreen::PauseScreen(sf::RenderWindow * window, sf::Texture * texture) {
    this->pauseTexture = texture;
    this->pauseSprite.setTexture(*texture, true);
    this->window = window;

    Clickable button1;
    button1.background = sf::RectangleShape(sf::Vector2f(500, 100));
    button1.background.setFillColor(sf::Color::Blue);
    button1.background.setPosition(40, window->getSize().y - 150);
    button1.event = PauseScreen::Button::QUIT;
    
    buttons.push_back(button1);
}

void PauseScreen::Draw()
{
    window->draw(pauseSprite);
    for (Clickable button : buttons)
    {
        window->draw(button.background);
    }
}

PauseScreen::Button PauseScreen::click(sf::Vector2i mousePosition)
{   
    float mouseX = mousePosition.x;
    float mouseY = mousePosition.y;
    for (Clickable button : buttons)
    {
        if(button.background.getGlobalBounds().contains(mouseX, mouseY))
        {
            return button.event;
        }
    }
    return PauseScreen::Button::NONE;
}