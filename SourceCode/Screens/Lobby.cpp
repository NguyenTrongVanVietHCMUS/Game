#include "Screens/Lobby.hpp"
Lobby::Lobby(StateStack& stack,Context context):
    State(stack,context) 
{      
    map=TileMap(context.maps->get(Map::ID::Lobby));
}

Lobby::~Lobby()
{

}

bool Lobby::handleEvent(const sf::Event&event)
{
    return false ; 
}

bool Lobby::update(sf::Time dt)
{
    return false ; 
    
}

void Lobby::draw()
{
    
}       