#pragma once 

// Class for game engine where combines all game components 
#include "Utility.hpp"
#include<Book/Character.hpp>   

const int width = 1920;
const int height = 1080;
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
    const sf::Time TimePerFrame = sf::seconds(1.0f/ 60.f); // 60 FPS   
    void PollEvents();
    void UpdateMousePosition();
    void Update(sf::Time);
    void Render();
    bool isRunning;
    Character player ; // Character object

};
