#include <Control/CameraManager.hpp>

void CameraManager::setCenter(float x, float y)
{
    view.setCenter(x, y);
}

void CameraManager::setCenter(const sf::Vector2f& center)
{
    view.setCenter(center);
}

const sf::View& CameraManager::getView() const
{
    return view;
}

void CameraManager::applyEffect(CameraEffect* effect)
{
    if (effect) {
        activeEffects.push_back(effect);
    }
}

void CameraManager::update(sf::Time dt)
{
    for (auto& effect : activeEffects) {
        if (effect->isActive()) {
            effect->update(dt);
        }
    }
    // Remove inactive effects
    activeEffects.erase(
        std::remove_if(activeEffects.begin(), activeEffects.end(),
                       [](CameraEffect* effect) { return !effect->isActive(); }),
        activeEffects.end()
    );
}

void CameraManager::handleEvents(const sf::Event& event)
{
    if (event.type == sf::Event::Resized)
    {
        // New size from the window
        float newW = static_cast<float>(event.size.width);
        float newH = static_cast<float>(event.size.height);

        // Resize the main camera view
        view.setSize(newW, newH);

        // If you have a separate UI view, resize that too
        // (so your UI elements also scale/position correctly)
        UIView.setSize(newW, newH);
    }
}

void CameraManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.setView(UIView); // Set the camera view for drawing
    for (const auto& effect : activeEffects) {
        effect->draw(target, states);
    }
    target.setView(view); // Reset to the UI view after drawing effects
}
