#include"Screens/Title.hpp"
#include<iostream> 
Title::Title(StateStack& stack,Context context):
    State(stack,context)
{     
    map = new TileMap(context.maps->get(Map::ID::Title)); // Assuming Map::ID::Title is defined in your MapHolder
}
Title::~Title()
{
    delete map ; 
}
void Title::draw()
{
    getContext().window->draw(*map);
}
bool Title::update(const sf::Time& dt)
{
    map->update(dt);
    return 0;
}
bool Title::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Enter)
        {
            requestStackPop();
            requestStackPush(States::Lobby);
        }
    }   
    if(event.type == sf::Event::Closed)
    {
        requestStackPop();
    }
    return 0;
}
