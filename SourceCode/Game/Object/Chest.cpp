#include<Object/Chest/Chest.hpp> 
#include<Book/InteractingAnimation/ChestAnimation.hpp>
#include<Control/WeaponLoader.hpp>
Chest::Chest(sf::Vector2f position, Hitbox hitbox , float scalex, float scaley) : Object("Chest", position , hitbox , scalex, scaley)
{
	type = Entity::Type::Object; 
	interactingAnimation = std::make_unique<ChestAnimation>(
		this, scalex, scaley
	);
}
Chest::Chest(sf::Vector2f position, Hitbox hitbox , float scalex, float scaley, WeaponLoader& weaponLoader) : Object("Chest", position , hitbox , scalex, scaley)
{
	type = Entity::Type::Object; 
	interactingAnimation = std::make_unique<ChestAnimation>(
		this, scalex, scaley
	);
	items = weaponLoader.LoadRandomWeapon();
}
void Chest::draw(sf::RenderTarget& target, sf::RenderStates states) const
{	
	interactingAnimation->draw(target, states);
	//Entity::draw(target, states); // Call the base class draw method
	// Draw the chest sprite or any other visual representation here
}
void Chest::collide(Entity* other)
{

}

std::shared_ptr<Weapon2> Chest::getItems()
{
	std::shared_ptr<Weapon2> result = items;
	items = nullptr;
	return result;
}