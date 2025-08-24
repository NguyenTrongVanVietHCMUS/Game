#pragma once 
#include<Book/Utility.hpp> 
#include<Object/Object.hpp>	
#include<Book/Weapon2.hpp>
#include<Control/WeaponLoader.hpp>
#include <Book/InteractingAnimation/BarrelAnimation.hpp>
#include<Control/ProjectileLoader.hpp>
class State;

class Barrel :public Object
{
private:
	std::shared_ptr<Weapon2> items = nullptr;
	State* CurrentMap = nullptr;

	bool itemAdded = false;
	bool isActive = false;
public: 
	Barrel(sf::Vector2f position,Hitbox hibox ,float scalex , float scaley); 
    void setMap(State* map);
	void collide(Entity* entity) override;
	bool update(sf::Time dt) override;
public:
};