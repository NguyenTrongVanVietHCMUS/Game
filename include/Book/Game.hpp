#pragma once 

// Class for game engine where combines all game components 
#include <Utility.hpp>

class Game
{
    private : 
        bool isRunning;  
        sf::RenderWindow window; // Window object
        int width, height; // Window size
    public:
        // Window object
        Game(int width=600, int height=800) ; 
        ~Game();
        
        // Statistics   
        bool Running()const { return isRunning; }
        
        // Game loop
        void Run() ; 
        void PollEvents() ; 
        void Update() ; 
        void Draw() ; 
}; 

