#include <Book/Player.hpp>  
Player::Player()
{
    // Load the texture from a file
    if (!texture.loadFromFile("Media/Textures/player.png"))
    {
        // Handle error
        std::cerr << "Error loading texture" << std::endl;
    }
    // Set the sprite's texture
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
    // Initialize position, velocity, and acceleration
    current_position = sf::Vector2f(300.0f,300.0f);
    final_position = current_position;
    sprite.setPosition(current_position);
    speed = 200.0f; 
    velocity = sf::Vector2f(0.0f, 0.0f);
}
Player::~Player()
{
    // Destructor logic if needed
}
void Player::PollEvents(sf::Event event)    
{  
    if(event.type==sf::Event::MouseButtonPressed)
    {
        if(event.mouseButton.button==sf::Mouse::Right)
        {
            // Get the mouse position in the window
            final_position = sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
        }
    }
    // Calculate the direction vector
    sf::Vector2f direction = final_position - current_position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if(distance==0.0f)
        return; // Avoid division by zero
    // Normalize the direction vector
    direction /= distance;
    // Set the velocity based on speed and direction
    velocity = direction * speed;
    // Update the sprite's position
}
void Player::Update(sf::Time deltaTime)
{
    // Update the player position based on velocity
    sf::Vector2f last_position = current_position;
    current_position += velocity * deltaTime.asSeconds();
    sf::Vector2f to_final = final_position - last_position;
    sf::Vector2f to_current = current_position - last_position;
    float to_final_len = std::sqrt(to_final.x * to_final.x + to_final.y * to_final.y);
    float to_current_len = std::sqrt(to_current.x * to_current.x + to_current.y * to_current.y);
    if (to_current_len > to_final_len) {
        current_position = final_position;
        velocity = sf::Vector2f(0.0f, 0.0f);
    }
    sprite.setPosition(current_position);
}   
void Player::Render(sf::RenderWindow& window)
{
    // Draw the player sprite
    window.draw(sprite);
}