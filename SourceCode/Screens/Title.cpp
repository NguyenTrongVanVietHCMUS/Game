#include"Screens/Title.hpp"

Title::Title(StateStack& stack,Context context):
    State(stack,context)
{       
        // std::cout<<map.File<<std::endl;
    map = TileMap(context.maps->get(Map::ID::Title));
    std::cout << "Title map loaded from: " << map.File << std::endl;
}
Title::~Title()
{
    // Destructor
}
void Title::draw()
{
    getContext().window->draw(map);
}
bool Title::update(sf::Time dt)
{
    map.update(dt);
    return false ; 
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
    return false ; 
}
