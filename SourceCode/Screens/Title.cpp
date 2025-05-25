#include"Screens/Title.hpp"
#include<iostream> 
Title::Title(StateStack& stack,Context context):
    State(stack,context)
{       
        // map = TileMap(context.maps->get(Map::ID::Title));  
    map = new TileMap(context.maps->get(Map::ID::Title)); // Assuming Map::ID::Title is defined in your MapHolder
}
Title::~Title()
{
    // Destructor
}
void Title::draw()
{
    std::cout<<"Drawing Title"<<std::endl;
    getContext().window->draw(*map);
}
bool Title::update(sf::Time dt)
{
    // map.update(dt);
    return 0 ; 
}
bool Title::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Event::Closed)
        {
            requestStackPop();
        }
        else if (event.key.code == sf::Keyboard::Escape)
        {
            requestStackPop();
        }
        else if(event.key.code == sf::Keyboard::Enter)
        {
            requestStackPush(States::Lobby);
        }
    }
    return 0 ;
}
