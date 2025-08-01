#pragma once
#include <Book/StrategyClass.hpp>

struct AdvancedWeaponComponent : public WeaponComponent
{
    virtual void play() override;
    virtual void update(Weapon2& weapon, sf::Time dt) override;
};
