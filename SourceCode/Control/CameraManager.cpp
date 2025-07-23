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
            std::cerr << "Updating camera effect" << std::endl;
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

void CameraManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.setView(UIView);
    for (const auto& effect : activeEffects) {
        effect->draw(target, states);
    }
    target.setView(view); // Reset to the UI view after drawing effects
}
