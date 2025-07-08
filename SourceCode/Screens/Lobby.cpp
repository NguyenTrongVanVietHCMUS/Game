#include <Screens/Lobby.hpp>
#include<Object/Character/Knight.hpp>
#include<Object/Mob/Boar.hpp> 
Lobby::Lobby(StateStack& stack,Context context):
    State(stack,context) 
{         
    map = new TileMap(context.maps->get(Map::ID::Lobby)); 
    map->entities.push_back(new Knight(&context.textures->get(Textures::ID::Knight),map->startingPoint,this)); // Assuming Texture::ID::Knight is defined in your TextureHolder
}

Lobby::~Lobby()
{
    delete map;
}

void Lobby::draw() 
{
    getContext().window->draw(*map);
}

bool Lobby::update(const sf::Time& dt)
{
    map->update(dt);
    return 0; 
}
bool Lobby::handleEvent(const sf::Event& event)
{
    std::cerr << "Lobby::handleEvent called\n";
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
    std::cerr << "Lobby::handleEvent finished\n";
    return 0;
}
