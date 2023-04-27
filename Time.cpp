#include "Time.h"
#include <iostream> 

// Make sure that the singleton starts out empty
Time* Time::singleton = nullptr;
Time::Time()
{
    this->clock = sf::Clock();
}

Time* Time::GetInstance(){
    if (singleton == nullptr) 
    {
        singleton = new Time();
        std::cout << "Creating new time " << std::endl;
    }
    return singleton;
}

sf::Clock* Time::GetClock()
{
    return &(this->clock);
}

float Time::DeltaTime()
{
    return this->clock.getElapsedTime().asSeconds();
}