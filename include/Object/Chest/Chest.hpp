#pragma once 
#include<Book/Utility.hpp> 
#include<Object/Object.hpp>
#include<Book/Weapon2.hpp>
#include<Control/WeaponLoader.hpp>
class Chest :public Object
{
private:
	std::shared_ptr<Weapon2> items = nullptr;
public: 
	Chest(sf::Vector2f position,Hitbox hibox ,float scalex , float scaley); 
	Chest(sf::Vector2f position, Hitbox hitbox, float scalex, float scaley, WeaponLoader& weaponLoader);

	// I need weapon loader to load random weapon
	virtual void collide(Entity* entity);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	std::shared_ptr<Weapon2> getItems();
};