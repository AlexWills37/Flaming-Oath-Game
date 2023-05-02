
#include <SFML/Graphics.hpp>
class Time {
    protected:
        Time();
        sf::Clock clock;
        float deltaTime;
        static Time* singleton;

    public:
        static Time* GetInstance();

        sf::Clock* GetClock();

        float DeltaTime();

        /*
         * Record the current elapsed time (in delta time) and 
         * reset the clock to record the next frame. Call this method before doing
         * any frame logic, but only call this method once per frame (so that you do not
         * lose time)
         */
        void ResetTime();

        // Delete copy constructor
        Time(const Time& toCopy) = delete;


};

