#include <Book/StrategyClass.hpp>


class BasicCooldownBehavior : public ICooldownBehavior
{
public:
    BasicCooldownBehavior(float cooldownTime) : ICooldownBehavior(cooldownTime) {std::cout << "BasicCooldownBehavior created with cooldown time: " << cooldownTime << std::endl;}

    void update(const sf::Time& dt) override {
        if (currentCooldown < cooldownTime) {
            currentCooldown += dt.asSeconds();
        }
    }
};