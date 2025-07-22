#include<Screens/HUD/StatPlayer.hpp>
#include<Control/ResourceManager.hpp>

StatPlayer::StatPlayer()
{
	player = nullptr; 
}
void StatPlayer::setPlayer(Character* player)
{
	if (this->player) delete this->player; // Delete the old player if it exists
	this->player = player; // Set the new player	
}
StatPlayer::~StatPlayer()
{
	delete player; 
}
void StatPlayer::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	sf::View view = target.getView(); // Get the current view of the target
	target.setView(target.getDefaultView()); // Set the view to the default view
	
	sf::Sprite HUDBar; 
	states.texture = &ResourceManager::getInstance().get < sf::Texture>(Textures::ID::HUDBar); // Set the texture for the player stats
	HUDBar.setTexture(*states.texture); // Set the texture for the player stats
	//HUDBar.setOrigin(HUDBar.getLocalBounds().width / 2.f, HUDBar.getLocalBounds().height / 2.f); // Set the origin to the center of the HUD bar
	HUDBar.scale(0.71, 0.8); 
	HUDBar.setPosition(15, 10); 
	target.draw(HUDBar, states);

	sf::Sprite heart;
	states.texture = &ResourceManager::getInstance().get < sf::Texture>(Textures::ID::HeartIcon);
	heart.setTexture(*states.texture); // Set the texture for the player heart	
	heart.scale(2.5f, 2.5f);
	heart.setOrigin(heart.getLocalBounds().width / 2.f, heart.getLocalBounds().height / 2.f); // Set the origin to the center of the heart
	heart.setPosition(sf::Vector2f(35,30)); 
	target.draw(heart,states); 
	
	sf::Sprite shield; 
	states.texture = &ResourceManager::getInstance().get < sf::Texture>(Textures::ID::ShieldIcon); // Set the texture for the player stats
	shield.setTexture(*states.texture);
	shield.scale(2.5f, 2.5f); // Scale the shield icon	
	shield.setOrigin(shield.getLocalBounds().width / 2.f, shield.getLocalBounds().height / 2.f);
	shield.setPosition(sf::Vector2f(35, 60)); // Set the position for the shield shield
	target.draw(shield, states);

	sf::Sprite mana; 
	states.texture = &ResourceManager::getInstance().get < sf::Texture>(Textures::ID::ManaIcon); // Set the texture for the player icon
	mana.setTexture(*states.texture);
	mana.scale(2.5f, 2.5f); // Scale the mana icon
	mana.setOrigin(mana.getLocalBounds().width / 2.f, mana.getLocalBounds().height / 2.f);
	mana.setPosition(sf::Vector2f(35, 90));
	target.draw(mana, states); 

	sf::Sprite emptybar; 
	states.texture = &ResourceManager::getInstance().get < sf::Texture>(Textures::ID::EmptyBar); // Set the texture for the player icon
	emptybar.setTexture(*states.texture);
	emptybar.scale(2.5f, 2.5f); // Scale the empty health bar
	emptybar.setOrigin(0, emptybar.getLocalBounds().height / 2.f);
	emptybar.setPosition(sf::Vector2f(50, 30)); // Set the position for the health bar
	target.draw(emptybar, states); 
	emptybar.setPosition(sf::Vector2f(50, 60)); // Set the position for the shield bar
	target.draw(emptybar, states);
	emptybar.setPosition(sf::Vector2f(50, 90)); // Set the position for the mana bar
	target.draw(emptybar, states);

	sf::Sprite heartbar; 
	states.texture = &ResourceManager::getInstance().get < sf::Texture>(Textures::ID::HeartBar); // Set the texture for the player icon
	heartbar.setTexture(*states.texture);
	//heartbar.setTextureRect(sf::IntRect(0, 0, heartbar.getLocalBounds().width*player->getHealth()/player->getMaxHealth(), heartbar.getLocalBounds().height)); // Set the texture rect based on the player's health
	heartbar.scale(2.5f*player->getHealth() / player->getMaxHealth(), 2.5f); // Scale the health bar
	heartbar.setOrigin(0, heartbar.getLocalBounds().height / 2.f);
	heartbar.setPosition(sf::Vector2f(50, 30)); // Set the position for the health bar
	target.draw(heartbar, states);

	sf::Sprite shieldbar;
	states.texture = &ResourceManager::getInstance().get < sf::Texture>(Textures::ID::ShieldBar); // Set the texture for the player icon
	shieldbar.setTexture(*states.texture);
	shieldbar.scale(2.5f * player->getShield() / player->getMaxShield(), 2.5f); // Scale the mana bar
	shieldbar.setOrigin(0, shieldbar.getLocalBounds().height / 2.f);
	shieldbar.setPosition(sf::Vector2f(50, 60)); // Set the position for the mana bar
	target.draw(shieldbar, states);

	sf::Sprite manabar;
	states.texture = &ResourceManager::getInstance().get < sf::Texture>(Textures::ID::ManaBar); // Set the texture for the player icon
	manabar.setTexture(*states.texture);
	manabar.scale(2.5f * player->getMana() / player->getMaxMana(), 2.5f); // Scale the mana bar
	manabar.setOrigin(0, manabar.getLocalBounds().height / 2.f);
	manabar.setPosition(sf::Vector2f(50, 90)); // Set the position for the mana bar
	target.draw(manabar, states);




	target.setView(view);
}
//states.texture = &tilesets[i].texture; // Set the texture for the current tileset
//target.draw(vertices[i], states);
