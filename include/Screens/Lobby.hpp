#pragma once 
#include<Book/Utility.hpp>
#include"Control/State.hpp"
#include"Book/TileMap.hpp"
#include"Book/Character.hpp"
#include "Control/ResourceHolder.hpp"
#include "Control/ResourceIdentifiers.hpp"
#include "Control/StateIdentifiers.hpp"
#include<Screens/HUD/StatPlayer.hpp>    
// Forward declaration to avoid circular dependency
class Lobby : public State 
{
private : 
    StatPlayer statPlayer;
public:
    Lobby(StateStack&stack ,Context context);
    ~Lobby(); 
    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);
};  
