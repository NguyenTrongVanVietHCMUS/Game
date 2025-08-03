#include <Book/AdvancedWeaponComponent.hpp>
#include <Book/Weapon2.hpp>

AdvancedWeaponComponent::AdvancedWeaponComponent(Weapon2* weapon, Entity* owner)
    : weapon(weapon), owner(owner)
{
    // Constructor logic if needed
}


void AdvancedWeaponComponent::loadFromJson(const nlohmann::json& data, State* map, Entity* owner)
{
    // Load the component from JSON data
    // This could include loading combo nodes, behaviors, animations, etc.
}

void AdvancedWeaponComponent::update(sf::Time dt)
{
    // Update the current combo node if it exists
    if (currentComboNode != comboNodes.end()) {
        if(currentComboNode->animationFinished())
        {
            if(currentComboNode->continueMode == ContinueMode::WAITING_INPUT) {
                currentComboNode->inputTimer += dt.asSeconds();
                if (currentComboNode->inputTimer > currentComboNode->inputWindow) {
                    resetCombo();
                }
                return;
            } else {
                advanceToNext();
            }
        } else {
            // Update the current combo node's animation and behavior
            currentComboNode->animation->update(*weapon, dt);
            currentComboNode->behavior->activate(*weapon, owner);
            
            // Handle input window and timing logic
            currentComboNode->inputTimer += dt.asSeconds();
            if (currentComboNode->inputTimer > currentComboNode->inputWindow) {
                // If input window is exceeded, reset or advance
                advanceToNext();
            }
        }
    }

    // Update the weapon and owner if needed
    weapon->update(dt);
    owner->update(dt);
}

void AdvancedWeaponComponent::signalInput()
{
    // Signal input to the current combo node
    if (currentComboNode != comboNodes.end()) {
        currentComboNode->inputActive(); // Reset input window
        currentComboNode->started = true; // Mark the combo as started
    }
}
void AdvancedWeaponComponent::resetCombo()
{
    // Reset the combo to the first node
    currentComboNode = comboNodes.begin();
    if (currentComboNode != comboNodes.end()) {
        currentComboNode->inputTimer = 0.0f; // Reset input timer
        currentComboNode->started = false; // Reset started state
        currentComboNode->isInputActive = false; // Reset input active state
    }
}

void AdvancedWeaponComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Draw the current combo node's animation if it exists
    if (currentComboNode != comboNodes.end() && currentComboNode->animation) {
        currentComboNode->animation->draw(target, states);
    }
}

void AdvancedWeaponComponent::advanceToNext()
{
    // Move to the next combo node
    if (currentComboNode != comboNodes.end()) {
        ++currentComboNode; // Advance to the next node
    }

    // If we reach the end of the combo, reset or handle accordingly
    if (currentComboNode == comboNodes.end()) {
        resetCombo(); // Reset to the beginning or handle end of combo logic
    }
}