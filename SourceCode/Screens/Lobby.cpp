#include <Screens/Lobby.hpp>
Lobby::Lobby(StateStack& stack,Context context):
    State(stack,context) 
{         
    map = new TileMap(context.maps->get(Map::ID::Lobby));
    entities.push_back(new Character("Knight",context.textures->get(Textures::ID::Knight),sf::Vector2u(8,3),0.05f,map->startingPoint)) ; 
}

Lobby::~Lobby()
{
    delete map;
}

void Lobby::draw() 
{
    sf::View view(entities[0]->getPosition(),sf::Vector2f(1216,672)); 
    // view.setViewport(sf::FloatRect({0.5f, 0.5}, {1.0f, 1.0f}));
    getContext().window->setView(view); // Set the view for the window
    getContext().window->draw(*map);

    for(auto&entity: entities)
    {
        getContext().window->draw(*entity);
    }
}

bool Lobby::update(sf::Time dt)
{
    map->update(dt);
    for(auto entity : entities)
    {
        entity->update(dt); 
    }
    return 0; 
}
bool Lobby::handleEvent(const sf::Event& event)
{
    for(auto entity : entities)
    {
        // if(static_cast<Character*>(entity) != nullptr)
        //     static_cast<Character*>(entity)->handleEvent(event,getContext().window);
        entity->handleEvent(event,getContext().window); 
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
