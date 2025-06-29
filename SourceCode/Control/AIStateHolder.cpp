#include <Control/AIStateHolder.hpp>
void AIStateHolder::addState(const std::string& name, std::shared_ptr<AIState> state)
{
    states[name] = state; // Add the state to the map
}

void AIStateHolder::removeState(const std::string& name)
{
    states.erase(name);
}

void AIStateHolder::update(const sf::Time& deltaTime)
{
    if(currentState == nullptr)
    {
        // Get the first state if no current state is set
        if (!states.empty())
        {
            currentState = states.begin()->second.get();
        }
    }

    if (currentState)
    {
        currentState->execute(); // Execute the current state logic
    }
}
void AIStateHolder::changeState(const std::string& newStateName)
{
    auto it = states.find(newStateName);
    if (it != states.end())
    {
        currentState = it->second.get(); // Change to the new state
    }
    else
    {
        throw std::runtime_error("State not found: " + newStateName);
    }
}