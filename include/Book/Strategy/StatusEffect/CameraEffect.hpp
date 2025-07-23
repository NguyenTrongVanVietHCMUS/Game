#pragma once
#include<Book/CameraEffect.hpp>
#include<Book/Entity.hpp>
#include <Control/CameraManager.hpp>

class FollowCameraEffect : public CameraEffect
{
private:
    Entity* targetEntity; // The entity to follow
    float smoothness = 0.1; // Smoothness factor for camera movement
public:
    FollowCameraEffect(CameraManager* cameraManager, Entity* target)
        : CameraEffect(0.0f, cameraManager), targetEntity(target) {}
    void update(const sf::Time& dt) override ;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {}
    bool isActive() const override {return true; }
};

class ShakeCameraEffect : public CameraEffect
{
private:
    float shakeIntensity = 5.0f; // Intensity of the shake effect
public:
    ShakeCameraEffect(float duration, CameraManager* cameraManager = nullptr, 
                      float intensity = 5.0f)
        : CameraEffect(duration, cameraManager), shakeIntensity(intensity) {}

    void update(const sf::Time& dt) override ;
};