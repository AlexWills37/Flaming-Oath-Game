/* player.cpp
 * 
 * Implements the player class.
 * 
 * @author Alex Wills
 * @author Jhonder Abreus
 * @date April 7, 2023
 */
#include "player.h"

#include "Time.h"
#include "InputManager.h"
#include <iostream>

// FIX ADD FIRE TEXTURE
Player::Player(sf::RenderWindow * window, sf::Texture * texture, HealthBar * healthBar, sf::Texture * fireTexture1, sf::Texture * healSpell)
    : LivingEntity(window, texture, 300, 1000, healthBar) {
    // Set the origin to the middle of the sprite's feet
    sprite.setOrigin(38, 132);
    InputManager* input = InputManager::GetInputManager();


    // Set initial score and speed


    // Initialize spells
    /*
    for (int i = 0; i < Player::maxSpells; ++i)
    {
        this->spells[i] = WizardSpells(this->window, fireTexture1);
        
    }
    */
    if (CastSpell(), true) {
        std::cout<< "fire";
        for (int i = 0; i < Player::maxSpells; ++i)
    {
        this->spells[i] = WizardSpells(this->window, fireTexture1);
    }
    }
    if (CastHeal(), true) {
        std::cout<< "heal";
        for (int i = 0; i < Player::maxSpells2; ++i)
    {
        this->spells2[i] = WizardSpells(this->window, healSpell);
    }    
    }
    


    /*
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
        this->CastSpell();
    } 
    // Set initial score and health
    */
   

    score = 10;
    frameCounter = 0;
    counter = 0;
    speed = 850;
    this->EnableFollowingHealthBar(sf::Vector2f(-75, -200));
}

void Player::Move(float x, float y) {

    // Flip player to face the direction they are moving
    if (x > 0) {
        sprite.setScale(1, 1);
    } else {
        sprite.setScale(-1, 1);
    }

    // Move player
    Entity::Move(x, y);
}
void Player::CastSpell()
{
    // Find the first fire that is off screen and put it where the dragon is
    
    WizardSpells* newFire1 = nullptr;
    //DragonFire * firesound = nullptr;
    bool foundFire1 = false;
    for (int i = 0; i < Player::maxSpells && !foundFire1; ++i)
    {
        // If fire is off screen, we can use it as a new fire
        if (this->spells[i].offScreen1) {
            newFire1 = &(this->spells[i]);
            foundFire1 = true;
        }
    }
    // If we found a fire that is off screen, we can have the dragon spit it out (move it to the dragon)
    if (foundFire1) {
        newFire1->offScreen1 = false;
        newFire1->sprite.setPosition(this->sprite.getPosition());    // Set the fire to the dragon's current position
    //delete firesound;
    //delete buffer1;

    // If we did not find a fire, then there are currently this->maxFires fires on screen, so we will not spit fire.
    }
};

void Player:: CastHeal()
{
    // Find the first fire that is off screen and put it where the dragon is
    
    WizardSpells* newHeal = nullptr;
    //DragonFire * firesound = nullptr;
    bool foundHeal = false;
    for (int i = 0; i < Player::maxSpells2 && !foundHeal; ++i)
    {
        // If fire is off screen, we can use it as a new fire
        if (this->spells2[i].offScreen1) {
            newHeal = &(this->spells2[i]);
            foundHeal = true;
        }
    }
    // If we found a fire that is off screen, we can have the dragon spit it out (move it to the dragon)
    if (foundHeal) {
        newHeal->offScreen1 = false;
        newHeal->sprite.setPosition(this->sprite.getPosition());    // Set the fire to the dragon's current position
    //delete firesound;
    //delete buffer1;

    // If we did not find a fire, then there are currently this->maxFires fires on screen, so we will not spit fire.
    }
}

void Player::Draw()
{
    // Draw the fires first
    for (int i = 0; i < this->maxSpells; ++i)
    {
        if (!this->spells[i].offScreen1)  // Only draw fires that are on screen
        {
            this->spells[i].Draw();
        }
    }
    for (int i = 0; i < this->maxSpells2; ++i) {
    if (!this->spells2[i].offScreen1)
        {
            this->spells2[i].Draw();           
        }
    }
    
    // Draw the player and health last, so that it is on top of any fire
    LivingEntity::Draw();
}

int Player::GetScore() {
    return this->score;
}

int Player::FrameUpdate() {
    frameCounter++;
return frameCounter;
}
/*
bool Player::CheckCollision1() {
    int dragonhealth = 5;
    bool hit = false;
    for (int i = 0; i < this->maxSpells; i++){
        if (!(this->spells[i].offScreen1) && this->spells[i].getGlobalBounds().intersects(dragon.getGlobalBounds()))
        {
            dragonhealth = dragonhealth - 1;
            this->spells[i].offScreen1 = true;
            std::cout<< "Collision";
            std::cout<< "Dragon Health: "<< dragonhealth;
        }
    }
    return hit;
}
*/

/*
bool Player::CheckCollision1(Dragon * player1)
{
    //sf::SoundBuffer* buffer2 = new sf::SoundBuffer;
    //if (!buffer2->loadFromFile("./assets/music/hit sfx.wav"))
    //{
    //    std::cout<< "ERROR LOADING HIT"<<std::endl;
    //}
    //sf::Sound* hitsound = new sf::Sound;
    //hitsound->setBuffer(*buffer2);
    bool hit1 = false;
    int draghealth = 0;
    for (int i = 0; i < this->maxSpells; i++)
    {
        // Detect a collision
        if (!(this->spells[i].offScreen1) && this->spells[i].getGlobalBounds().intersects(Dragon->getGlobalBounds()))
        {
            hit1 = true;
            this->spells[i].offScreen1 = true;
            //hitsound->play();
            //delete hitsound;
            //delete buffer2;
            draghealth = draghealth - 1;
        }
        std::cout<< draghealth;
    }
    return hit1;
}
*/
void Player::DecreaseScore(int change)
{
    this->score -= change;
}


void Player::Update() {
    float deltaTime = Time::GetInstance()->DeltaTime();
    InputManager* input = InputManager::GetInputManager();
    bool movingLeft, movingRight;

    // Handle user inputs
    // Movement
    if (input->IsKeyPressed(sf::Keyboard::A)) {
        movingLeft = true;
    } else {
        movingLeft = false;
    }

    if (input->IsKeyPressed(sf::Keyboard::D)) {
        movingRight = true;
    } else {
        movingRight = false;
    }

    // Casting spells
    if ((FrameUpdate() % 10 == 0) && input->IsKeyPressed(sf::Keyboard::J)) {
        this->CastSpell();
    }
    if (input->IsKeyPressed(sf::Keyboard::K)) {
        this->CastHeal();
    }

    // Move all spells up
    for (int i = 0; i < Player::maxSpells; i++) {
        if (!this->spells[i].offScreen1) {
            this->spells[i].MoveUp();
        }
    }
    for (int i = 0; i < Player::maxSpells2; i++) {
        if (!this->spells2[i].offScreen1) {
            this->spells2[i].MoveUp();
        }
    }

 


    // Move player
    if (movingLeft && !movingRight)
    {
        this->Move(-speed * deltaTime, 0);
    } else if (movingRight && !movingLeft) {
        this->Move(speed * deltaTime, 0);
    }

}