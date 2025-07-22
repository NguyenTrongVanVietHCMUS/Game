#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <book/Strategy/CameraEffectBehavior.hpp>
#include <Book/Attribute/CameraAttribute.hpp>


class CameraManager
{
public:
    CameraAttribute attribute;
private:
    sf::View view; // The camera view
    sf::RenderTarget* target; // The render target to which the camera applies
    std::vector<CameraEffect*> activeEffects;
public:
    CameraManager(sf::RenderTarget& renderTarget)
        : target(&renderTarget), view(renderTarget.getDefaultView()){}
    CameraManager(){}

    void setCenter(float x, float y);
    const sf::View& getView() const;
public:
    void applyEffect(CameraEffect* effect);
    void updateTarget(sf::RenderTarget& renderTarget);
    void update(sf::Time dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) ;
};