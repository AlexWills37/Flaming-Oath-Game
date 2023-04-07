#ifndef _DRAGON_H
#define _DRAGON_H

#include <SFML/Graphics.hpp>
#include <vector>



class DragonFire {
    public:
        DragonFire(sf::Vector2f startingPos);

        void MoveDown();
        sf::Sprite sprite;
    private:
        sf::Texture texture;
        bool offScreen;
};

class Dragon {
    public:
        Dragon();

        void MoveRandomly();

        std::vector<DragonFire> GetFires();

        void SpitFire();

        sf::Sprite sprite;

    private:
        // Private variables
        sf::Texture texture;
        std::vector<DragonFire> fires;

};
#endif