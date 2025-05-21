#include "Book/Game.hpp"
// Constructor
Game::Game()
: 
    window(sf::VideoMode(width, height), "SFML Game", sf::Style::Close | sf::Style::Titlebar),
    player("Knight", "Media/Assets/Characters/Knight/MovingKnightLeftRight.png",sf::Vector2u(8,2), 0.3f)
{
    // Create the window
    window.setFramerateLimit(60);
    
    if(!map.load("Media/Assets/Maps/Lobby/lobby.json"))
    {
        std::cerr << "Failed to load map" << std::endl;
        exit(EXIT_FAILURE);
    }
    // Load the tile map
}

// Destructor
Game::~Game()   
{

}

void Game::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (window.isOpen())
    {       
        PollEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            PollEvents();
            Update(TimePerFrame); 
        }
        Render(); 
    }
}
// Poll events
void Game::PollEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        if(event.type==sf::Event::KeyPressed)
        {
            if(event.key.code==sf::Keyboard::Escape)
                window.close();
        }
        player.PollEvents(event) ; 
    }

}

// void Game::UpdateMousePosition()
// {
//     // Get the mouse position in the window
//     // mousePosWindow = sf::Mouse::getPosition(window);
//     mousePosWindow = sf::Vector2f(static_cast<float>(mousePosWindow.x), static_cast<float>(mousePosWindow.y));
//     // mousePosView = window.mapPixelToCoords(mousePosWindow);
//     // std::cout<<mousePosView.x<<" "<<mousePosView.y<<std::endl
// }
// Update game logic
void Game::Update(sf::Time dt)
{
    player.Update(dt);
    // Add game update logic here
}

// Render the game
void Game::Render()
{
    window.clear(sf::Color::White);
    window.draw(map) ; // Draw the tile map
    player.Render(window) ; 
    window.display();
}

// Main game loop