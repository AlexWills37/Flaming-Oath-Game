/* Time.cpp
 * 
 * Implementation of the singleton Time class, used for recording the time in between frames.
 * 
 * @author Alex Wills
 */

#include "Time.h"
#include <iostream> 

// Make sure that the singleton starts out empty
Time* Time::singleton = nullptr;
Time::Time()
{
    this->clock = sf::Clock();
}

/*  STATIC
 * Gets a pointer to the single, global instance of the Time object.
 */
Time* Time::GetInstance(){
    if (singleton == nullptr) 
    {
        singleton = new Time();
        std::cout << "Creating new time " << std::endl;
    }
    return singleton;
}

/*
 * Gets the sf::Clock object used by the Time object.
 */
sf::Clock* Time::GetClock()
{
    return &(this->clock);
}

/*
 * Returns the time (in seconds) since the last time ResetTime() was called.
 */
float Time::DeltaTime()
{
    return deltaTime;
}

/*
 * Record the current elapsed time (in delta time) and 
 * reset the clock to record the next frame. Call this method before doing
 * any frame logic, but only call this method once per frame (so that you do not
 * lose time)
 */
void Time::ResetTime() {
    deltaTime = clock.restart().asSeconds();
}