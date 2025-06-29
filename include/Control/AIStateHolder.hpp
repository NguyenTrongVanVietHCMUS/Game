#pragma once
#include <Book/Utility.hpp>
#include <Book/AIState.hpp>

class AIStateHolder
{
private:
    std::map<std::string, std::shared_ptr<AIState>> states; // Map to hold AI states by name
    EntityAI* owner; // Pointer to the owner entity AI
    AIState* currentState; // Pointer to the current AI state
public:
    AIStateHolder(EntityAI* owner) : owner(owner), currentState(nullptr) {}
    void addState(const std::string& name, std::shared_ptr<AIState> state);
    void removeState(const std::string& name);
    void update(const sf::Time& deltaTime);
    void changeState(const std::string& newStateName);
};