#include <Screens/Dungeon/Jungle.hpp>
#include<Control/ResourceManager.hpp>
#include<Object/Character/Knight.hpp>
#include<Object/Mob/Boar.hpp> 
#include<Object/Mob/GoblinShooter.hpp>
#include<Object/Mob/GoblinMageRoyal.hpp>
#include<Object/Mob/GoblinMageSorcerer.hpp>
#include<Object/Mob/GoblinSupport.hpp>
#include<Object/Mob/GoblinWarrior.hpp>
#include<Object/Mob/GoblinExecutor.hpp>
#include<Object/Mob/MadScientist.hpp>
#include<Object/Mob/SwordMinion.hpp>
#include<Object/Mob/BlunderbussPistolMinion.hpp>
#include<Object/Mob/RifleMinion.hpp>
#include<Object/Chest/Chest.hpp>
#include <Object/Chest/ExplosiveBarrel.hpp>
Jungle::Jungle(StateStack& stack,Context context):
    State(stack,context)
{         
    map = new TileMap(ResourceManager::getInstance().get<TileMap>(Map::ID::Jungle)); 
    map->entities.push_back(new Knight(map->startingPoint, this, &map->camera)); 
    
 //   map->entities.push_back(new Boar(map->startingPoint,this)); // Add a Boar entity to the 
    map->entities.push_back(new GoblinShooter(map->startingPoint,this)); 
    //map->entities.push_back(new SwordMinion(map->startingPoint, this));
	//map->entities.push_back(new BlunderbussPistolMinion(map->startingPoint, this));
	//map->entities.push_back(new RifleMinion(map->startingPoint, this));

	//map->entities.push_back(new GoblinMageRoyal(map->startingPoint, this));
	//map->entities.push_back(new GoblinMageSorcerer(map->startingPoint, this));
	//map->entities.push_back(new GoblinSupport(map->startingPoint, this));
	//map->entities.push_back(new GoblinWarrior(map->startingPoint, this));
	//map->entities.push_back(new GoblinExecutor(map->startingPoint, this));
	//map->entities.push_back(new MadScientist(map->startingPoint, this));
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
}   

void Jungle::draw() 
{
    getContext().window->draw(*map);
    getContext().window->draw(statPlayer); 
}

bool Jungle::update(sf::Time dt)
{
    map->update(dt);
    return 0; 
}
bool Jungle::handleEvent(const sf::Event& event)
{
    sf::RenderWindow*window = getContext().window;
    map->handleEvent(event, window); // Handle events for the map and entities
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            requestStackPop(); 
            requestStackPush(States::Title); // Push the Title state when Escape is pressed
        }
        if(event.key.code==sf::Keyboard::Enter)    
        {
            requestStackPop() ; 
            requestStackPush(States::Lobby) ; 
        }
    }
    if (event.type == sf::Event::Closed)
    {
        requestStackPop(); // Pop the current state when the window is closed
    }
    return 0;
}
