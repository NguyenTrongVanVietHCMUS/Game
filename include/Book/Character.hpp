#pragma once
#include<Book/Utility.hpp> 

#include<Control/ResourceManager.hpp>
#include<Control/State.hpp>
#include<Book/Inventory.hpp>
#include<Book/StrategyClass.hpp>
#include<Control/CameraManager.hpp>
#include<Book/EntityComponent.hpp>
#include<Book/Strategy/StatusEffect/CameraEffect.hpp>
class MovingAnimation;


class Character : public Entity
{
protected:
    float pickupRange = 150.0f;

protected:
    

    EntityAttributeActionComponent attributes;

protected: 
    virtual sf::Vector2f getHandPosition()const; 
protected : 
    std::unique_ptr<MovingAnimation> movingAnimation ; 
    std::shared_ptr<Inventory> inventory;
    std::vector<std::shared_ptr<IStatusEffect> > statusEffect; // Status effect for the character
    State *map;
    CameraManager* cameraManager; // Pointer to the camera manager for camera effects
public : 
    Character(std::string name , sf::Vector2f position, State *state =nullptr, CameraManager* cameraManager = nullptr);
    ~Character(); 
public : 
    //SkillHolder skillHolder;
    virtual void collide(const Entity*other); 
    virtual bool handleEvent(const sf::Event& event,sf::RenderWindow* window) ;  
    virtual bool update(sf::Time dt) ; 
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; 


	virtual int getMaxHealth() const;
	virtual int getMaxMana() const;
    virtual int getMaxShield() const;
    virtual int getHealth(); 
    virtual int getMana(); 
    virtual int getShield();

public:
    void setAttribute(CharacterResourceType type, float current, float max);
};