#pragma once
#include<Book/Utility.hpp> 
#include<Book/Entity.hpp>
#include<Object/Skills/TestSkill.hpp>
#include<Book/MovingAnimation.hpp>
class Character : public Entity
{
private :


public : 
// Constructor and Destructor   
Character();
Character(std::string name , sf::Texture& texture,sf::Vector2u imageCount, float switchTime);
~Character(); 
public : 
// Functions
    MovingAnimation movingAnimation ; 
	SkillManager skillManager;
	void operator=(const Character& other); // Disable assignment operator
    bool handleEvent(const sf::Event& event) ; 
    bool update(sf::Time deltaTime) ; 
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        movingAnimation.draw(target, states);
        skillManager.draw(target, states); // Draw the skill manager
    }
    // Draw the Character
};