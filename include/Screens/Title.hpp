#pragma once 
#include<Book/Utility.hpp>
#include"Control/State.hpp"
#include"Book/Character.hpp"
// #include"Book/TileMap.hpp"
#include"Book/World.hpp"
#include "Control/ResourceHolder.hpp"
class Title : public State , public World
{
public:
    Title(StateStack&stack ,Context context);
    ~Title(); 

    void draw(); 
    bool update(sf::Time dt);
    bool handleEvent(const sf::Event& event);
};