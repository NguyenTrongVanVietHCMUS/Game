#pragma once 

// Class for game engine where combines all game components 
#include<Book/Utility.hpp>
#include<Book/TileMap.hpp>
#include<Book/Character.hpp>
#include<Control/StateStack.hpp>
#include<Control/StateIdentifiers.hpp>

#include<Control/ResourceHolder.hpp>
#include<Control/ResourceIdentifiers.hpp>

#include<Control/ResourceManager.hpp>


#include<Control/SoundPlayer.hpp>
#include<Control/MusicPlayer.hpp>


class Game : public sf::NonCopyable
{
public:
    Game();
    ~Game();

    void Run();
    
private:
    const sf::Time TimePerFrame = sf::seconds(1.0f/ 60.f); // 60 FPS   
    void PollEvents();
    void Update(sf::Time dt);
    void Render();
    void registerStates();
    template <typename ResourceType, typename Identifier>
        void load(Identifier id, const std::string& path);
private :
    sf::RenderWindow window;
    
    TextureHolder textures;
    FontHolder fonts;
    MusicPlayer music ; 
    SoundPlayer sounds ; 
    MapHolder maps;
    StateStack stateStack;
};
