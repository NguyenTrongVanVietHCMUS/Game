#include "Book/Game.hpp"

// Constructor
Game::Game()
: isRunning(true), width(800), height(600), window(sf::VideoMode(800, 600), "Game Window",sf::Style::Titlebar|sf::Style::Close)
{
    window.setFramerateLimit(60);
    sf::Texture texture; 
    if(!texture.loadFromFile("Media/Textures/player.png"))
    {
        abort() 
    }
}

// Destructor
Game::~Game()
{

}

void Game::Run()
{
    while (isRunning && window.isOpen())
    {
        PollEvents();
        UpdateMousePosition() ; 
        Update();
        Render();
    }
    window.close();
}
// Poll events
void Game::PollEvents()
{
    player.PollEvents(window);
}

void Game::UpdateMousePosition()
{
    // Get the mouse position in the window
    // mousePosWindow = sf::Mouse::getPosition(window);
    mousePosWindow = sf::Vector2f(static_cast<float>(mousePosWindow.x), static_cast<float>(mousePosWindow.y));
    // mousePosView = window.mapPixelToCoords(mousePosWindow);
    // std::cout<<mousePosView.x<<" "<<mousePosView.y<<std::endl
}
// Update game logic
void Game::Update()
{
    // Add game update logic here
}

// Render the game
void Game::Render()
{
    window.clear();
    window.display();
}

// Main game loop