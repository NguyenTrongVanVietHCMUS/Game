#include<Book/Strategy/StatusEffect/CameraEffect.hpp>
#include<Book/Utility.hpp>

void DarknessCameraEffect::update(const sf::Time& dt) {
    updateElapsedTime(dt);
    float delta = dt.asSeconds();


    if (currentAlpha < targetAlpha)
        currentAlpha = std::min(currentAlpha + alphaLerpSpeed * delta, targetAlpha);

    if(currentAlphaMultiplier < targetAlphaMultiplier && !isReverse)
        currentAlphaMultiplier = std::min(currentAlphaMultiplier + alphaMultiplierLerpSpeed * delta, targetAlphaMultiplier);
    
    if((duration - elapsedTime) <= 1.0/alphaMultiplierLerpSpeed)
    {
        isReverse = true;
        currentAlphaMultiplier = std::max(currentAlphaMultiplier - alphaMultiplierLerpSpeed * delta, 0.0f);
    }
}

void DarknessCameraEffect::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Vector2f ScreenSize = cameraManager->getSize();
    sf::Vector2f worldCenter = sf::Vector2f(ScreenSize.x * 0.5f, ScreenSize.y * 0.5f); // or player position
    sf::Vector2i screenCenter = target.mapCoordsToPixel(worldCenter);
    sf::Vector2f center = sf::Vector2f(screenCenter); // screen-space center

    shader.setUniform("u_center", center);
    shader.setUniform("u_radius", currentRadius);
    shader.setUniform("u_gradient", currentAlpha);
    shader.setUniform("u_alphaMultiplier", currentAlphaMultiplier);

    overlay.setSize((sf::Vector2f)target.getSize());
    overlay.setFillColor(sf::Color::White);
    target.draw(overlay, &shader);

}