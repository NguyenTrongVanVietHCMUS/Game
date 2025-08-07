#pragma once

#include<Book/InteractingAnimation/InteractingAnimation.hpp>
#include<Book/Utility.hpp>


class BarrelAnimation : public InteractingAnimation
{
private: 
    float scalex; 
	float scaley; 
    sf::Texture* BarrelTexture = new sf::Texture();
    sf::Sprite* barrelSprite = new sf::Sprite();
public:
    BarrelAnimation(Object* owner, float scalex, float scaley, std::string textureFile = "Media/Assets/TileSets/Objects/Barrel.png");
    ~BarrelAnimation();

public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};