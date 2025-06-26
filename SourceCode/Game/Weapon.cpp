#include <Book/Weapon.hpp>

void Weapon::UpdateAngle(const sf::Event& event, sf::RenderWindow* window) {
    if (event.type == sf::Event::MouseMoved) {
        // Get the mouse position relative to the window using pixel coordinates

        sf::Vector2f worldPosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        // Calculate the angle between the weapon's position and the mouse position
        sf::Vector2f direction = worldPosition - position;
       
        angle = std::atan2(direction.y, direction.x) * 180 / 3.14159f; // Convert radians to degrees
        // std::cerr << "Get angle: " << angle << std::endl;
    }
    else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
        // If the right mouse button is pressed, update the angle to face the mouse position
        sf::Vector2f worldPosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));   
        sf::Vector2f direction = worldPosition - position;
        angle = std::atan2(direction.y, direction.x) * 180 / 3.14159f; // Convert radians to degrees
    }
}


void Weapon::setHolder(Entity* holder) {
    this->holder = holder; // Set the holder entity for the weapon
    skillHolder.setEntity(holder); // Set the entity for the skill holder
}