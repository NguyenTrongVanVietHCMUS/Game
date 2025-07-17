#include <Book/Weapon2.hpp>

void Weapon2::setBehavior(std::unique_ptr<IBehavior> newBehavior)
{
    if (newBehavior) {
        behavior = std::move(newBehavior);
    }
}

void Weapon2::setStat(const std::string& statName, float value)
{
    stats[statName] = value;
}

float Weapon2::getStat(const std::string& statName) const
{
    auto it = stats.find(statName);
    if (it != stats.end()) {
        return it->second;
    }
    return 0.0f; // Default value if stat not found
}

void Weapon2::activate(Entity*target)
{
    if (behavior) {
        behavior->activate(*this, target);
    }
    if( animation) {
        animation->play(); // Start the animation when the weapon is activated
    }
}

bool Weapon2::update(const sf::Time& dt)
{
    if( animation) {
        animation->update(*this, dt);
    }
    return true;
}

void Weapon2::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (animation) {
        animation->draw(target, states);
    }
}