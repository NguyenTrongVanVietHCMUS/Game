#include<Screens/Dungeon/Jungle.hpp>

Jungle::Jungle(StateStack& stack, Context context)
: State(stack, context)
{
    map = new TileMap(context.maps->get(Map::ID::Jungle));
    entities.push_back(new Character("Knight", context.textures->get(Textures::ID::Knight), sf::Vector2u(8, 3), 0.05f, map->startingPoint));
}
Jungle::~Jungle()
{
    delete map;
}
void Jungle::draw()
{
    sf::View view(entities[0]->getPosition(), sf::Vector2f(1216, 672));
    getContext().window->setView(view); // Set the view for the window
    getContext().window->draw(*map);

    for (auto& entity : entities)
    {
        getContext().window->draw(*entity);
    }
}
bool Jungle::update(sf::Time dt)
{
    map->update(dt);
    for (auto entity : entities)
    {
        entity->update(dt);
    }
    return 0;
}
bool Jungle::handleEvent(const sf::Event& event)
{
    for (auto entity : entities)
    {
        entity->handleEvent(event, getContext().window);
    }
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            requestStackPop(); // Pop the current state when Escape is pressed
            requestStackPush(States::Lobby); // Push the Lobby state
        }
    }
    return 0;
}
