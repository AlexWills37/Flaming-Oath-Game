/* PauseScreen.h
 *
 * Definitions for creating a pause screen
 * 
 */
#include <SFML/Graphics.hpp>
#include <vector>

class PauseScreen {

    public:
        enum Button {
            NONE, QUIT, CONTINUE
        };
    private:
        struct Clickable {
            sf::RectangleShape background;
            PauseScreen::Button event;
        };

    private:
        sf::Texture * pauseTexture;
        sf::Sprite pauseSprite;
        sf::RenderWindow * window;

        std::vector<Clickable> buttons;

    public:
        PauseScreen(sf::RenderWindow * window, sf::Texture * texture);

    public:


        void Draw();

        Button click(sf::Vector2i mousePosition);


};