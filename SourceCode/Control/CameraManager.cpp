#include <Control/CameraManager.hpp>

void CameraManager::setCenter(float x, float y)
{
    view.setCenter(x, y);
    target->setView(view);
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

void CameraManager::updateTarget(sf::RenderTarget& renderTarget)
{
    target = &renderTarget;
    view = renderTarget.getDefaultView();
}

void CameraManager::draw(sf::RenderTarget& target, sf::RenderStates states) 
{
    updateTarget(target);
    for (const auto& effect : activeEffects) {
        effect->draw(target, states);
    }
}