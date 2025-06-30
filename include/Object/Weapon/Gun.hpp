#pragma once
#include "Book/Weapon.hpp"
#include <Object/SkillLibraryUtility.hpp>
#include <Control/SkillHolder.hpp>
#include <Control/SkillLoader.hpp>
class Gun : public Weapon
{
public:
    Gun(Entity* holder, float cooldownTime = 0.0f, float damage = 10.0f, float speed = 100.0f);
    //Gun(const Gun& other) = default; // Copy constructor
    ~Gun();

    // Override methods from Weapon interface
    void draw(sf::RenderTarget& target, sf::RenderStates states) override;
    void handleEvent(const sf::Event& event,sf::RenderWindow* window) override;
    void update(const sf::Time& deltaTime) override;

    Weapon* clone() override{
        std::cerr << "Cloning Gun with cooldown : " << cooldownTime << std::endl;
        return new Gun(holder, cooldownTime, damage, speed); // Create a new instance of Gun
    };
};