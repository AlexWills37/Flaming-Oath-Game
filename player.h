#ifndef _PLAYER_H
#define _PLAYER_H

#include <SFML/Graphics.hpp>

class Player {

    public:
        Player();
        sf::Sprite sprite;

        void MovePlayer(float x, float y);

        int GetScore();

        void FrameUpdate();

    private:
        int frameCounter;
        int score;
        int health;
        sf::Texture texture;

};



#endif