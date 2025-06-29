#pragma once
#include <Book/EntityAI.hpp>
class EntityAI; 
class AIStateHolder;

class AIState
{
private:
    std::string name; // Name of the AI state
    AIStateHolder* stateHolder; // Pointer to the AI state holder managing this state
public:
    AIState(std::string name, AIStateHolder* stateHolder) : name(name), stateHolder(stateHolder) {}

    virtual void execute() = 0;
    virtual ~AIState() = default;

public: 
    void ChangeState(const std::string& newStateName);
};