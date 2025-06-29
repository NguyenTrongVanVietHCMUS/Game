#include <Book/EntityAI.hpp>

bool EntityAI::update(const sf::Time& deltaTime)
{
    // Update the AI state holder
    stateHolder.update(deltaTime);
    
    // Call the AI update logic
    AIUpdate(deltaTime);
    
    // Update the character's moving animation
    movingAnimation.update(deltaTime);
    
    // Update the weapon holder
    weaponHolder.update(deltaTime);
    
    // Update the hitbox position based on the entity's current position
    updateHitboxOnPosition(deltaTime);
    
    return false; // Return false to indicate no event handling
}