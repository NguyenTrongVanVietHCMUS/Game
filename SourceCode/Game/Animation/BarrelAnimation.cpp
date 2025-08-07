#include <Book/InteractingAnimation/BarrelAnimation.hpp>
#include <Object/Object.hpp>

BarrelAnimation::BarrelAnimation(Object* owner, float scalex, float scaley, std::string textureFile)
    : InteractingAnimation(owner), scalex(scalex), scaley(scaley)
{
    BarrelTexture->loadFromFile(textureFile);
    barrelSprite->setTexture(*BarrelTexture);
    barrelSprite->setScale(scalex, scaley);
    barrelSprite->setPosition(owner->getPosition());
}

BarrelAnimation::~BarrelAnimation()
{
    delete BarrelTexture;
    delete barrelSprite;
}

void BarrelAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*barrelSprite, states); // Draw the barrel sprite
}