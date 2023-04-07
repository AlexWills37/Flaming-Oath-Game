#include "dragon.h"
#include<cstdlib>
#include <iostream>
/*
 * Create a Dragon
 */
Dragon::Dragon()
{
    // Providing a seed value
    srand((unsigned) time(NULL));
    this->texture.loadFromFile("./assets/sprites/0001.png");
    this->sprite.setTexture(this->texture, true);
    this->sprite.setPosition(1000, 200);
}


void Dragon::MoveRandomly()
{
    

    // Get a random number
    int random = rand() % 3;

    switch(random)
    {
        
        // Move left
        case 0:
            this->sprite.move(-20, 0);
            break;

        // Move right
        case 1:
            this->sprite.move(20, 0);
            break;


        default:
            break;
    }
    

    // Make sure dragon is on the screen
    sf::Vector2f currentPos = sprite.getPosition();
    
    if (currentPos.x > 1080) {
        currentPos.x = 1080;
    } else if (currentPos.x < 0) {
        currentPos.x = 0;
    }

    if (currentPos.y > 900) {
        currentPos.y = 900;
    } else if (currentPos.y < 0) {
        currentPos.y = 0;
    }

    sprite.setPosition(currentPos);

    // Randomly spit fire
    random = rand() % 50;
    switch (random) 
    {
        // Spit fire!
        case 0:
            std::cout << "Spitting fire!" <<  std::endl;
            this->SpitFire();
            break;
        default:
            break;
    }

    // Move all fires down
    for (int i = 0; i < fires.size(); i++) {
        fires[0].MoveDown();
    }

}

std::vector<DragonFire> Dragon::GetFires(){
    return fires;
}

void Dragon::SpitFire()
{
    DragonFire newFire = DragonFire(this->sprite.getPosition());
    this->fires.push_back(newFire);
}


