#include <Screens/Dungeon/Jungle.hpp>
#include<Control/ResourceManager.hpp>
#include<Object/Character/Knight.hpp>
#include<Object/Chest/Chest.hpp>
#include <Object/Chest/ExplosiveBarrel.hpp>
Jungle::Jungle(StateStack& stack,Context context):
    State(stack,context)
{         
    map = new TileMap(ResourceManager::getInstance().get<TileMap>(Map::ID::Jungle)); 
    map->entities.push_back(new Knight(map->startingPoint, this, &map->camera)); 
    
    map->initEntities(this); 
    context.music->play(Music::Jungle);
    map->setWeaponLoader(weaponLoader); // Set the weapon loader for the map

    statPlayer.setPlayer(map->getPlayer()); 
    if (map){
		for (auto& x : map->entities)
		{
			if (auto chest = dynamic_cast<Chest*>(x))
			{
				std::cerr << "Chest found in state: " << this << std::endl;
				chest->setItems(weaponLoader->LoadRandomWeapon()); // Set a random weapon for the chest
			} else if (auto explosiveBarrel = dynamic_cast<ExplosiveBarrel*>(x))
            {
                explosiveBarrel->setMap(this); // Set the current map for the explosive barrel
            }
		}
	}
}

Jungle::~Jungle()
{
    delete map;
    delete weaponLoader;
}   

void Jungle::draw() 
{
    getContext().window->draw(*map);
    getContext().window->draw(statPlayer); 
}

bool Jungle::update(sf::Time dt)
{
    map->update(dt);
    if (map->getPlayer()->isDeath())
    {
        requestStackPop();
        requestStackPush(States::GameOver);
        getContext().music->stop();
    }
    return 0; 
}
bool Jungle::handleEvent(const sf::Event& event)
{
    sf::RenderWindow*window = getContext().window;
    map->handleEvent(event, window); // Handle events for the map and entities 

    if (event.type == sf::Event::Closed)
    {
        requestStackPop(); // Pop the current state when the window is closed
        return 0;
    }
    return 1; 
}
