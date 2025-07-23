#pragma once
#include<Book/CameraEffect.hpp>
#include<Book/Entity.hpp>
#include <Control/CameraManager.hpp>

class FollowCameraEffect : public CameraEffect
{
private:
    Entity* targetEntity; // The entity to follow
public:
    FollowCameraEffect(CameraManager* cameraManager, Entity* target)
        : CameraEffect(0.0f, cameraManager), targetEntity(target) {}
    void update(const sf::Time& dt) override {
        if (targetEntity) {
            // Update the camera position to follow the target entity
            cameraManager->setCenter(targetEntity->getPosition());
        }
    }
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {}
    bool isActive() const override {return true; }
};