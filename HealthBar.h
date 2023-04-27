
#include <SFML/Graphics.hpp>

class HealthBar {

    // Member variables
    private:
        sf::RenderWindow * window;
        sf::Texture * emptyHeartTexture;
        sf::Texture * filledHeartTexture;
        sf::Sprite backgroundSprite;
        sf::Sprite heartsSprite;

        int health;

        int heartWidth;

    // Constructors
    public:
        HealthBar();
        HealthBar(sf::RenderWindow* window, sf::Texture* emptyHearts, sf::Texture* filledHearts);


    // Methods
    public:
        /*
         * Gets the health from this health bar.
         */
        int getHealth();

        /*
         * Replaces the health of this health bar and updates it visually.
         *
         * @param newHealth (int) - the new value of the health
         */
        void setHealth(int newHealth);

        /*
         * Changes the health of this health bar and updates it visually.
         *
         * @param difference (int) - the change in health (example: -1 = lose 1 health)
         */
        void changeHealth(int difference);

        void Draw();

    // Helper functions
    private:
        void drawBackground();
        void drawHearts(int numHearts);

};