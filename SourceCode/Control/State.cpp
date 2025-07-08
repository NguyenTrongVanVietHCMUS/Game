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
		map->PushQueueEntities.push_back(entity);
	}
}

void State::popEntity(Entity* entity)
{
	if (map)
	{
		if (entity && std::find(map->PopQueueEntities.begin(), map->PopQueueEntities.end(), entity) == map->PopQueueEntities.end())
		{
			map->PopQueueEntities.push_back(entity);
		} else 
		{
			std::cerr << "Entity already in PopQueueEntities or is null." << std::endl;
		}
	}
}