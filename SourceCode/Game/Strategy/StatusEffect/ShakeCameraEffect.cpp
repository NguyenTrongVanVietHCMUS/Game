#include<Book/Strategy/StatusEffect/CameraEffect.hpp>

void ShakeCameraEffect::update(const sf::Time& dt) {
    if (cameraManager) {
        // Implement shake logic here
        // For example, you can randomly offset the camera position
        float offsetX = (std::rand() % 100 - 50) / 100.0f * shakeIntensity; // Random offset in X
        float offsetY = (std::rand() % 100 - 50) / 100.0f * shakeIntensity; // Random offset in Y
        cameraManager->setCenter(cameraManager->getPosition() + sf::Vector2f(offsetX, offsetY));
    }
    updateElapsedTime(dt);
}