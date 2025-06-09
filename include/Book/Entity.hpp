#pragma once 
#include <Book/Utility.hpp>
#include<Control/Hitbox.hpp>
#include<Control/SkillHolder.hpp>
#include<Book/Skill.hpp>
#include<memory>


class Entity:public sf::Drawable
{
protected :
    int HP = 6; // Health Points
    int maxHP = 6; // Maximum Health Points
    int Energy = 3; // Energy Points
    int maxEnergy = 3; // Maximum Energy Points
    int shield = 2; // Shield Points
    int maxShield = 2; // Maximum Shield Points

public :

    enum class type { Ally, Enemy };

    Entity(); // Constructor with default position
    virtual ~Entity();

public :

    
    std::string name ; 
    sf::Vector2f position; // Position of the entity
    Hitbox hitbox ;  
    virtual bool handleEvent(const sf::Event& event,sf::RenderWindow* window);
    virtual bool update(sf::Time dt); // Update the entity
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const ; // Draw the entity

public :
	bool isAlive() const; // Check if the entity is alive
	void takeDamage(int damage); // Apply damage to the entity
	void restoreHealth(int amount); // Restore health points

public : 
    // Getters and Setters
    sf::Vector2f getPosition() const { std::cerr << "Get position : " << position.x << ", " << position.y << std::endl; return position; }
    sf::Vector2f getDirection() const { return sf::Vector2f(0.45f, 0.45f); } // Placeholder for direction
};