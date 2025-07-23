#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <Book/CameraEffect.hpp>
#include <Book/Attribute/CameraAttribute.hpp>


class CameraManager
{
public:
    CameraAttribute attribute;
private:
    sf::View view; // The camera view
    sf::View UIView;
    std::vector<CameraEffect*> activeEffects;
public:
    CameraManager()
        : view(sf::FloatRect(0, 0, 1216, 672)), UIView(sf::FloatRect(0, 0, 1216, 672)){}
    CameraManager(const sf::View& initialView)
        : view(initialView), UIView(sf::FloatRect(0, 0, 1216, 672)) {}

    void setCenter(float x, float y);
    void setCenter(const sf::Vector2f& center);
    const sf::View& getView() const;
    sf::Vector2f getPosition() const {return view.getCenter();}
public:
    void applyEffect(CameraEffect* effect);
    void update(sf::Time dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};