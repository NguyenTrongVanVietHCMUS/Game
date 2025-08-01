#include <Screens/Lobby.hpp>
#include<Object/Character/Knight.hpp>
#include<Control/ResourceManager.hpp> 
Lobby::Lobby(StateStack& stack,Context context):
    State(stack,context) 
{         
    map = new TileMap(ResourceManager::getInstance().get<TileMap>(Map::ID::Lobby)); 
    map->entities.push_back(new Knight(map->startingPoint, this, &map->camera)); // Adjusted to match the new Knight constructor
    map->setWeaponLoader(weaponLoader); // Set the weapon loader for the map
    statPlayer.setPlayer(map->getPlayer()); 
}

Lobby::~Lobby()
{
    delete map;
    delete weaponLoader;
}

void Lobby::draw() 
{
    getContext().window->draw(*map);
    getContext().window->draw(statPlayer); 
}

bool Lobby::update(sf::Time dt)
{
    map->update(dt);
    return 0; 
}
bool Lobby::handleEvent(const sf::Event& event)
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
            requestStackPush(States::Jungle) ; 
        }
    }
    if (event.type == sf::Event::Closed)
    {
        requestStackPop(); // Pop the current state when the window is closed
    }
    return 0;
}
