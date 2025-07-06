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

void Weapon2::activate(Entity*target)
{
    if (behavior) {
        behavior->activate(*this, target);
    }
}
