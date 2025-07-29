#include<Object/Chest/Chest.hpp> 
#include<Book/InteractingAnimation/ChestAnimation.hpp>

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
	
	items = weaponLoader.LoadRandomWeapon();
	interactingAnimation = std::make_unique<ChestAnimation>(
		this, scalex, scaley, items
	);
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

void Chest::setItems(std::shared_ptr<Weapon2> newItems)
{
	// Cast to ChestAnimation to set items
	itemAdded = true;
	if (auto chestAnim = dynamic_cast<ChestAnimation*>(interactingAnimation.get())) {
		chestAnim->setItems(newItems);
		items = newItems; // Update the items in the chest
	} else {
		std::cerr << "Error: interactingAnimation is not of type ChestAnimation." << std::endl;
	}
}
