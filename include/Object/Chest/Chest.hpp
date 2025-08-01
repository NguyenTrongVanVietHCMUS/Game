#pragma once 
#include<Book/Utility.hpp> 
#include<Object/Object.hpp>	
#include<Book/Weapon2.hpp>
#include<Control/WeaponLoader.hpp>
class Chest :public Object
{
private:
	std::shared_ptr<Weapon2> items = nullptr;
	bool itemAdded = false;
public: 
	Chest(sf::Vector2f position,Hitbox hibox ,float scalex , float scaley); 
	Chest(sf::Vector2f position, Hitbox hitbox, float scalex, float scaley, WeaponLoader& weaponLoader);

	// I need weapon loader to load random weapon
	virtual void collide(Entity* entity);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	std::shared_ptr<Weapon2> getItems(); // Get the items from the chest
	void takeItem(std::shared_ptr<Weapon2> &item); // Take the item away from the chest
	void setItems(std::shared_ptr<Weapon2> newItems);
	bool isItemAdded() const { return itemAdded; }
};