/* Time.h
 *
 * Interface for the game's Time module. This is a singleton class that allows
 * access to the time between frames from any other class.
 * 
 * To use:
 *      In the main loop, access the class's singleton clock with
 *          Time::GetInstance()->GetClock();
 * 
 *      Then wait until the clock passes the threshold for the time between frames.
 *          You can check the time of the clock with
 *              Time::GetInstance()->GetClock()->getElapsedTime().asSeconds()
 * 
 *      When it is time to do a frame, call the following method once to save the time and start counting for the next frame:
 *          Time::GetInstance()->ResetTime();
 * 
 *      Then, anywhere in the code, you can check the time since the last frame with
 *          Time::GetInstance()->DeltaTime();
 *          
 * @author Alex Wills
 */
#ifndef _GAMETIME_H
#define _GAMETIME_H


#include <SFML/Graphics.hpp>
class Time {
    protected:
        Time();
        sf::Clock clock;    // Clock responsible for keeping track of time
        float deltaTime;    // Storage for the time since the last ResetTime() was called
        static Time* singleton; // The single time object, accessible with Time::GetInstance();

    public:
        /*  STATIC
         * Gets a pointer to the single, global instance of the Time object.
         */
        static Time* GetInstance();

        /*
         * Gets the sf::Clock object used by the Time object.
         */
        sf::Clock* GetClock();

        /*
         * Returns the time (in seconds) since the last time ResetTime() was called.
         */
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


#endif