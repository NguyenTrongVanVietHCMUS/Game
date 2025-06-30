#pragma once
#include "Book/Weapon.hpp"
#include <Object/SkillLibraryUtility.hpp>
#include <Control/SkillHolder.hpp>
#include <Control/SkillLoader.hpp>
class Gun : public Weapon
{
public:
    Gun(Entity* holder, float cooldownTime = 0.0f);
    //Gun(const Gun& other) = default; // Copy constructor
    ~Gun();

    // Override methods from Weapon interface
    void draw(sf::RenderTarget& target, sf::RenderStates states) override;
    void handleEvent(const sf::Event& event,sf::RenderWindow* window) override;
    void update(const sf::Time& deltaTime) override;

    Weapon* clone() override{
        return new Gun(holder, cooldownTime); // Create a new instance of Gun
    };
};


