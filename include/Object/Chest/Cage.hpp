#pragma once 
#include<Book/Utility.hpp> 
#include<Object/Object.hpp>	
#include<Book/Weapon2.hpp>
#include<Control/WeaponLoader.hpp>
class Cage :public Object
{
private:
	std::shared_ptr<Weapon2> items = nullptr;
	bool itemAdded = false;
	bool activated; 
public:
	Cage(sf::Vector2f position, Hitbox hibox, float scalex, float scaley);
	~Cage();
	virtual Hitbox getBodyHitbox() const override;
	virtual void activate();
	virtual void deactivate();
	virtual void collide(Entity* entity);
	virtual void update(Entity* player);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; 
};