#pragma once    
#include <Book/Character.hpp>
#include <Book/Utility.hpp>
#include <Control/AIStateHolder.hpp>
class EntityAI : public Character
{
private:
    AIStateHolder stateHolder; // AI state holder for managing states
public:
    virtual void AIUpdate(const sf::Time& deltaTime) = 0; // Pure virtual function for AI update logic
    bool update(const sf::Time& deltaTime) override;
    bool handleEvent(const sf::Event& event, sf::RenderWindow* window) override {return false; } // Handle events, return false to indicate no event handling;
    EntityAI(std::string name, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position): Character(name, texture, imageCount, switchTime, position), stateHolder(this){}   
};