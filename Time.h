
#include <SFML/Graphics.hpp>
class Time {
    protected:
        Time();
        sf::Clock clock;

        static Time* singleton;

    public:
        static Time* GetInstance();

        sf::Clock* GetClock();

        float DeltaTime();

        // Delete copy constructor
        Time(const Time& toCopy) = delete;


};

