#include <Book/Player.hpp>  
Player::Player()
{
    // Load the texture from a file
    if (!texture.loadFromFile("Media/player.png"))
    {
        // Handle error
        std::cerr << "Error loading texture" << std::endl;
    }

    // Set the sprite's texture
    sprite.setTexture(texture);

    // Initialize position, velocity, and acceleration
    current_position = sf::Vector2f(300.0f,300.0f);
    sprite.setPosition(current_position);
    speed = 10.0f; 
    velocity = sf::Vector2f(0.0f, 0.0f);
}
Player::~Player()
{
    // Destructor logic if needed
}
void Player::PollEvents(sf::RenderWindow& window)
{
    // Handle player input events
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        // Get the mouse position in the window

        // Calculate the direction vector from the player to the mouse position
        sf::Vector2f direction = sf::Vector2f(sf::Mouse::getPosition(window)) - current_position;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0) 
        {
            // Normalize the direction vector
            direction /= length;

            // Set the velocity based on speed and direction
            velocity = direction * speed;
        }
    }
}
void Player::Update(float dt)
{
    // Update the player's position based on speed and velocity ; 
    current_position += velocity * dt;
    // Update the sprite's position
    sprite.setPosition(current_position);
    // Reset velocity to zero if not moving
}
void Player::Render(sf::RenderWindow& window)
{
    // Draw the player sprite
    window.draw(sprite);
}