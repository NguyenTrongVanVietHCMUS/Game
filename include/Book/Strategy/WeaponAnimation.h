#pragma once
#include <Book/Utility.hpp>
#include <Book/StrategyClass.hpp>
#include <Book/Entity.hpp>
class SwordAnimation : public IWeaponAnimation
{
private:
    float startAngle, endAngle;
    Entity* owner = nullptr; // Owner of the sword animation, if needed
public:
    SwordAnimation(float TotalTime, float scale, sf::Texture* texture, 
                    const sf::Vector2f& position, float startAngle = 0.0f, float endAngle = 0.0f,
                    Entity* owner = nullptr,
                    const sf::Vector2f& middlePosition = sf::Vector2f(0, 0));
    void update(Weapon2& weapon, const sf::Time& dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) override;
};

class GunAnimation : public IWeaponAnimation
{
private:
    float startAngle, endAngle;
    float recoilOffset;
    float scale; // Scale of the gun animation
    Entity* owner = nullptr; // Owner of the gun animation, if needed
public:
    GunAnimation(float TotalTime, float scale, sf::Texture* texture, 
                 const sf::Vector2f& position, float startAngle = 0.0f, float endAngle = 0.0f,float recoilOffset = 10.0f,
                 Entity* owner = nullptr,
                 const sf::Vector2f& middlePosition = sf::Vector2f(0, 0));
    void update(Weapon2& weapon, const sf::Time& dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) override;
};