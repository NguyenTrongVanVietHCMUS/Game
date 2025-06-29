#include <Book/AIState.hpp>


void AIState::ChangeState(const std::string& newStateName)
{
    if (stateHolder)
    {
        stateHolder->changeState(newStateName); // Change the state in the state holder
    }
}