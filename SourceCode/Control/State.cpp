#include "Control/State.hpp"
#include "Control/StateStack.hpp"
#include "Control/WeaponLoader.hpp"
#include "Object/Chest/Chest.hpp"
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
	weaponLoader = new WeaponLoader(this); // Initialize the weapon loader with the current state
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
	//map->handleCollision() ; 
} 

void State::pushEntity(Entity* entity)
{
	if (map)
	{
		map->PushQueueEntities.push_back(entity);
	}
}

void State::pushEntity(std::shared_ptr<Entity> entity)
{
	if (map)
	{
		map->PushQueueEntities.push_back(entity.get());
		_OwnershipReference.push_back(entity);
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

void State::popEntityNoDelete(Entity* entity)
{
	if (map)
	{
		std::cerr << entity->name << " pop no delete\n";
		if (entity && std::find(map->PopQueueEntitiesNoDelete.begin(), map->PopQueueEntitiesNoDelete.end(), entity) == map->PopQueueEntitiesNoDelete.end())
		{
			map->PopQueueEntitiesNoDelete.push_back(entity);
		} else 
		{
			std::cerr << "Entity already in PopQueueEntitiesNoDelete or is null." << std::endl;
		}
	}
}

Entity* State::GetClosestEntity(Entity::Type type, sf::Vector2f position) const
{
	float ClosestDistance = 10000.0f; // Define a distance threshold for "closest"
	Entity* closestEntity = nullptr;
	if(map)
	{
		
		for(const auto& entity : map->entities)
		{
			sf::Vector2f entityPosition = entity->getPosition();
			float distance = std::sqrt(std::pow(entityPosition.x - position.x, 2) + std::pow(entityPosition.y - position.y, 2));
			if(distance < ClosestDistance && entity->type == type)
			{
				// If this entity is closer than the current closest, update closestEntity
				ClosestDistance = distance;
				closestEntity = entity;
			} 
		
		}
	}
	return closestEntity;
}

Entity* State::GetClosestItem(sf::Vector2f position) const
{
	float ClosestDistance = 10000.0f; // Define a distance threshold for "closest"
	Entity* closestEntity = nullptr;
	if(map)
	{
		for(const auto& entity : map->entities)
		{
			sf::Vector2f entityPosition = entity->getPosition();
			float distance = std::sqrt(std::pow(entityPosition.x - position.x, 2) + std::pow(entityPosition.y - position.y, 2));
			if(distance < ClosestDistance && entity->type == Entity::Type::Weapon)
			{
				// If this entity is closer than the current closest, update closestEntity
				ClosestDistance = distance;
				closestEntity = entity;
			} 
			if(auto chest = dynamic_cast<Chest*>(entity)) // Check if the entity is a Chest
			{
				
				if(chest->getItems() != nullptr)
				{
					float itemDistance = std::sqrt(std::pow(chest->getItems()->getPosition().x - position.x, 2) + std::pow(chest->getItems()->getPosition().y - position.y, 2));
					if(itemDistance < ClosestDistance)
					{
						ClosestDistance = itemDistance;
						closestEntity = entity;
					}
				}
			}
		}
	}
	return closestEntity;
}

std::vector<Entity*> State::GetEntities() const
{
	if (map)
	{
		return map->entities;
	}
	return {};
}

std::vector<Entity*> State::GetEntities(Entity::Type type) const
{
	std::vector<Entity*> filteredEntities;
	if (map)
	{
		for (const auto& entity : map->entities)
		{
			if (entity->type == type)
			{
				filteredEntities.push_back(entity);
			}
		}
	}
	return filteredEntities;
}