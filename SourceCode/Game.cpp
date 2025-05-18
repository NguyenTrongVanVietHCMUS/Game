#include<Game.hpp>

Game::Game(int width, int height) : window(sf::VideoMode(width, height), "SFML Game"), m_width(width), m_height(height)
{
    // Initialize the game
    window.setFramerateLimit(60);
    isRunning = true;
}
Game::~Game()
{
    // Cleanup if needed
}