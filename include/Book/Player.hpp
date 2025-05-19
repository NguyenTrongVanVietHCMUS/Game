#pragma once
#include <Book/Utility.hpp> 
class Player 
{
    private : 
    
        sf::Vector2f current_position;
        sf::Vector2f final_position;
        float speed ; 
        sf::Vector2f velocity;
        
        public : 
        Player();
        ~Player(); 
        
        sf::Texture texture;
        sf::Sprite sprite;

        void PollEvents(sf::Event event) ; 
        void Update(sf::Time deltaTime) ; 
        void Render(sf::RenderWindow& window) ; 
};