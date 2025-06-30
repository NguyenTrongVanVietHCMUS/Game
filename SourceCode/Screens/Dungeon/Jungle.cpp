#include <Screens/Dungeon/Jungle.hpp>
#include<Object/Character/Knight.hpp>
#include<Object/Mob/Boar.hpp> 

Jungle::Jungle(StateStack& stack,Context context):
    State(stack,context) 
{         
    map = new TileMap(context.maps->get(Map::ID::Jungle));
    map->entities.push_back(new Knight(&context.textures->get(Textures::ID::Knight),map->startingPoint)); // Assuming Texture::ID::Knight is defined in your TextureHolder
    for (int i = 1; i <= 50; i++)
    {
        map->entities.push_back(new Boar(&context.textures->get(Textures::ID::Boar), map->startingPoint)); // Add a Boar entity to the map
    }

}

Jungle::~Jungle()
{
    delete map;
}   

void Jungle::draw() 
{
    getContext().window->draw(*map);
}

bool Jungle::update(const sf::Time& dt)
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
