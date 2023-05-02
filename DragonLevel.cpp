
#include "Level.h"
#include "player.h"
#include "dragon.h"


class DragonLevel : public Level {

    private:
        Player * player;
        Dragon * dragon;

    public:
        DragonLevel(sf::RenderWindow * window, Entity * player) {

        }
};