#include <Screens/Dungeon/Jungle.hpp>
#include<Object/Character/Knight.hpp>
Jungle::Jungle(StateStack& stack,Context context):
    State(stack,context) 
{         
    map = new TileMap(context.maps->get(Map::ID::Jungle));
    map->entities.push_back(new Knight(&context.textures->get(Textures::ID::Knight),sf::Vector2u(8,3),0.1f,map->startingPoint, this)); // Assuming Texture::ID::Knight is defined in your TextureHolder
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
    // for(auto &x : map->layers)
    // {
    //     if(x->type == Layer::ObjectGroup)
    //     {
    //         auto objectLayer = static_cast<ObjectLayer*>(x);
    //         for(auto x : objectLayer->entities)
    //         {
    //             std::cout<<x->getHitbox().hitbox.top+x->getHitbox().hitbox.height<<std::endl; // Debugging output to check entity positions
    //         }
    //     }

    // }
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
