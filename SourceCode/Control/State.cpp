#include "Control/State.hpp"
#include "Control/StateStack.hpp"

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, MusicPlayer& music, SoundPlayer& sounds, MapHolder& maps)
: window(&window)
, textures(&textures)
, fonts(&fonts)
, music(&music)
, sounds(&sounds)
, maps(&maps)
{
	
}

State::State(StateStack& stack, Context context)
: mStack(&stack)
, mContext(context)
{
}

State::~State()
{
}

void State::requestStackPush(States::ID stateID)
{
	mStack->pushState(stateID);
}

void State::requestStackPop()
{
	mStack->popState();
}

void State::requestStateClear()
{
	mStack->clearStates();
}

State::Context State::getContext() const
{
	return mContext;
}
void State::handleCollision()
{
	// Handle collision logic here
	// This is a placeholder function and should be implemented in derived classes
	map->handleCollision() ; 
} 

void State::pushEntity(Entity* entity)
{
	if (map)
	{
		map->entities.push_back(entity);
	}
}

void State::popEntity(Entity* entity)
{
	if (map)
	{
		auto it = std::find(map->entities.begin(), map->entities.end(), entity);
		while (it != map->entities.end())
		{
			std::cerr << "Removing entity: " << entity->name << std::endl;
			map->entities.erase(it); // Remove the entity from the map's entity list
			it = std::find(map->entities.begin(), map->entities.end(), entity); // Find the next occurrence
		}
	} else
	{
		std::cerr << "Entity not found in map's entity list." << std::endl;
	}
}