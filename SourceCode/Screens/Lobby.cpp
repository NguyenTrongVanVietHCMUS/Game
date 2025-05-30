#include <Screens/Lobby.hpp>
Lobby::Lobby(StateStack& stack,Context context):
    State(stack,context) 
{         
    map = new TileMap(context.maps->get(Map::ID::Lobby));
}

Lobby::~Lobby()
{
    delete map;
}
void Lobby::draw()
{
    getContext().window->draw(*map);
}
bool Lobby::update(sf::Time dt)
{
    map->update(dt);
    return 0; 
}
bool Lobby::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Event::Closed)
        {
            requestStackPop(); // Pop the current state when the window is closed
        }
        else if (event.key.code == sf::Keyboard::Escape)
        {
            requestStackPop(); 
            requestStackPush(States::Title); // Push the Title state when Escape is pressed
        }

    }
    return 0;
}
