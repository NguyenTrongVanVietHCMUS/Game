#pragma once 

// Class for game engine where combines all game components 
#include "Utility.hpp"
#include<Book/Player.hpp>   

class Game
{
public:
    Game();
    ~Game();

    void Run();

    sf::Vector2f mousePosWindow;
    // sf::Vector2f mousePosView;
    sf::RenderWindow window;

private:

    void PollEvents();
    void UpdateMousePosition();
    void Update();
    void Render();
    bool isRunning;
    int width;
    int height;
    Player player ;  
};
