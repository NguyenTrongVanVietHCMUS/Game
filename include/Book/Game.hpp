#pragma once 

// Class for game engine where combines all game components 
#include "Utility.hpp"
#include"Book/TileMap.hpp"
#include"Book/Character.hpp"   
#include"Control/StateStack.hpp"  
#include"Control/StateIdentifiers.hpp"

#include"Control/ResourceHolder.hpp" 
#include"Control/ResourceIdentifiers.hpp"

#include"Control/SoundPlayer.hpp"
#include"Control/MusicPlayer.hpp"
#include "Screens/Lobby.hpp"
#include "Screens/Title.hpp"
#include<Book/TileMap.hpp> 
class Game 
{
public:
    Game();
    ~Game();

    void Run();
    
private:
    const sf::Time TimePerFrame = sf::seconds(1.0f/ 60.f); // 60 FPS   
    void PollEvents();
    void Update(sf::Time);
    void Render();
    void registerStates();
private :
    sf::RenderWindow window;
    
    TextureHolder textures;
    FontHolder fonts;
    MusicPlayer music ; 
    SoundPlayer sounds ; 
    MapHolder maps;
    StateStack stateStack;
};
