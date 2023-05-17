/* LivingEntity.cpp
 *
 * Definitions for the LivingEntity class.
 *  
 * @author Alex Wills
 */

#include "LivingEntity.h"

/*
 * Constructs a LivingEntity with a health bar.
 *
 * @param window - the window of the game
 * @param texture - the entity's main texture
 * @param x, y - the starting location of the entity
 * @param healthBar - pointer to the unique health bar this entity will use
 */
LivingEntity::LivingEntity(sf::RenderWindow * window, sf::Texture * texture, float x,
    float y, HealthBar * healthBar): Entity(window, texture, x, y) {

    this->healthBar = healthBar;
    healthMovement = FIXED;
}

/*
 * Draws the health bar with the current number of hearts.
 */
void LivingEntity::Draw() {
    // Draw the health bar and the entity
    // Move the health bar if that option has been selected
    if (healthMovement == FOLLOW) {
        sf::Vector2f barPosition = this->sprite.getPosition() + healthbarOffset;
        healthBar->SetPosition(barPosition.x, barPosition.y);
    }
    Entity::Draw();
    healthBar->Draw();
}

/*
 * Increments/decrements the current health.
 * 
 * @param change (int) the number of hearts to add to the health bar (use negative numbers to decrease health)
 */
void LivingEntity::ChangeHealth(int change) {
    healthBar->changeHealth(change);
}

int LivingEntity::GetHealth() {
    return healthBar->getHealth();
}

/*
 * Set the health bar to follow the entity.
 * 
 * @param offset - how far from the entity's origin the health bar's origin should be
 */
void LivingEntity::EnableFollowingHealthBar(sf::Vector2f offset) {
    healthMovement = FOLLOW;
    healthbarOffset = offset;
}