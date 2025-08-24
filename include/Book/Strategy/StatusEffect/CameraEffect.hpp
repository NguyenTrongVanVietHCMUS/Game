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

class DarknessCameraEffect : public CameraEffect
{
private:
    sf::Color darknessColor = sf::Color(0, 0, 0, 150); // Color of the darkness effect
    float fadeSpeed = 0.5f; // Speed at which the darkness fades in/out
    mutable sf::Shader shader;
    mutable sf::RectangleShape overlay;

    float currentRadius = 32.0f;
    float radiusLerpSpeed = 600.0f;

    float currentAlpha = 0.0f;
    float targetAlpha = 1000.0f;
    float alphaLerpSpeed = 50.0f;

    float currentAlphaMultiplier = 0.0f; // Multiplier for the alpha value
    float targetAlphaMultiplier = 1.0f; // Target multiplier for the alpha value
    float alphaMultiplierLerpSpeed = 0.5f; // Speed at which the alpha multiplier changes

    bool isReverse = false;
public:
    DarknessCameraEffect(float duration, CameraManager* cameraManager = nullptr)
        : CameraEffect(duration, cameraManager) {
            alphaLerpSpeed = (targetAlpha - currentAlpha) / duration;
            shader.loadFromFile("Media/Shader/spotlight.frag", sf::Shader::Fragment);
        }


    void update(const sf::Time& dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override ;
};