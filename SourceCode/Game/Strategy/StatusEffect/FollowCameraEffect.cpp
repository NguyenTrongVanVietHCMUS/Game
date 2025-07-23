#include <Book/Strategy/StatusEffect/CameraEffect.hpp>


void FollowCameraEffect::update(const sf::Time& dt) {
    if (targetEntity) {
        // Update the camera position to follow the target entity
        sf::Vector2f targetPosition = targetEntity->getPosition();
        sf::Vector2f currentPosition = cameraManager->getPosition();

        // Smoothly interpolate the camera position towards the target entity
        sf::Vector2f newPosition = currentPosition + (targetPosition - currentPosition) * smoothness;
        cameraManager->setCenter(newPosition);
    }
}

