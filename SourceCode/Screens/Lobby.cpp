#include <Screens/Lobby.hpp>
Lobby::Lobby(StateStack& stack,Context context):
    State(stack,context) 
{         
    map = new TileMap(context.maps->get(Map::ID::Lobby));
    entities.push_back(new Character()) ; 
    auto knight = static_cast<Character*>(entities.back());  
    *knight = Character("Knight",context.textures->get(Textures::ID::Knight),sf::Vector2u(8,2),0.05f); // Add the map to the entities vector
}

Lobby::~Lobby()
{
    delete map;
}
void Lobby::draw() 
{
    getContext().window->draw(*map); // Draw the map
    // for(auto layer : map->layers)
    // {
    //     if (layer->visible&&layer->type==Layer::Type::ImageLayer) // Check if the layer is visible
    //     {
    //         getContext().window->draw(*layer); // Draw the layer
    //     }
    // }
    for(auto entity: entities)
    {
        getContext().window->draw(*entity) ;
    }
}
bool Lobby::update(sf::Time dt)
{
    std::cout<<"Updating Lobby" << std::endl;
    map->update(dt);
    for(auto entity : entities)
    {
        entity->update(dt); // Update each entity
    }
    return 0; 
}
bool Lobby::handleEvent(const sf::Event& event)
{
    for(auto entity : entities)
    {
        entity->handleEvent(event); // Handle events for each entity
    }  
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
