/* LivingEntity.cpp
 *
 * Definitions for the LivingEntity class.
 *  
 * @author Alex Wills
 */

#include "LivingEntity.h"

LivingEntity::LivingEntity(sf::RenderWindow * window, sf::Texture * texture, float x,
    float y, HealthBar * healthBar): Entity(window, texture, x, y) {

    this->healthBar = healthBar;
    healthMovement = FIXED;
}

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

void LivingEntity::ChangeHealth(int change) {
    healthBar->changeHealth(change);
}

int LivingEntity::GetHealth() {
    return healthBar->getHealth();
}

void LivingEntity::EnableFollowingHealthBar(sf::Vector2f offset) {
    healthMovement = FOLLOW;
    healthbarOffset = offset;
}