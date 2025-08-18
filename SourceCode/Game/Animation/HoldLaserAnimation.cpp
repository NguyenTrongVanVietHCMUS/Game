#include <Book/MovingAnimation.hpp>
#include <Book/Projectile2.hpp>
void HoldLaserAnimation::ReCalculateScale(){
    if(owner)
    {
        startPosition =
            sf::Vector2f(owner->getAttribute("Start Position X")
            , owner->getAttribute("Start Position Y"));
        endPosition =
            sf::Vector2f(owner->getAttribute("End Position X")
            , owner->getAttribute("End Position Y"));
        float distance = std::pow(endPosition.x - startPosition.x, 2) + std::pow(endPosition.y - startPosition.y, 2);
        distance = std::sqrt(distance);
        float spriteWidth = sprite.getGlobalBounds().width;
        scale = distance / spriteWidth;
        sprite.setScale(scale, 1.0f);
        supportSprite.setScale(scale, 1.0f);
    } else
    {
        std::cerr << "WARNING : HoldLaserAnimation owner is null." << std::endl;
    }
    
}

HoldLaserAnimation::HoldLaserAnimation(sf::Texture *texture, sf::Vector2f middlePosition, sf::Vector2f& position)
: startPosition(startPosition), endPosition(endPosition), owner(owner),
MovingAnimation(texture, sf::Vector2u(1.f, 1.f), 0, position, 1.0f, middlePosition) {
    float distance = std::pow(endPosition.x - startPosition.x, 2) + std::pow(endPosition.y - startPosition.y, 2);
    distance = std::sqrt(distance);
    float spriteWidth = sprite.getGlobalBounds().width;
    supportSprite.setTexture(*texture);
    scale = distance / spriteWidth;
    sprite.setScale(scale, 1.0f);
    sprite.setOrigin(0.0f, sprite.getGlobalBounds().height / 2.0f); // Center the sprite vertically
    supportSprite.setScale(scale, 1.0f);
    supportSprite.setOrigin(0.0f, supportSprite.getGlobalBounds().height / 2.0f); // Center the sprite vertically
    std::cerr << "Trying to load the ball texture." << std::endl;
    BallTexture = new sf::Texture();
    if(BallTexture->loadFromFile("Media/Assets/Projectiles/LaserBall.png")) {
        std::cerr << "Ball texture loaded successfully." << std::endl;
        ballSprite1.setTexture(*BallTexture);
        ballSprite2.setTexture(*BallTexture);
    } else {
        std::cerr << "Failed to load LaserBall texture." << std::endl;
    }
    std::cerr << "Ball texture loaded successfully." << std::endl;
}

void HoldLaserAnimation::update(sf::Time dt) {

    ReCalculateScale();
    elapseTime += dt.asMilliseconds();
    float ScaleY = sin(elapseTime);
    float finalScale = std::abs(ScaleY); // Scale between 0.5 and 1.0
    sprite.setScale(scale, ScaleY * 3);
    supportSprite.setScale(scale, cos(elapseTime * 1.5) * 2.5f);
    float angle = std::atan2(endPosition.y - startPosition.y, endPosition.x - startPosition.x) * 180.0f / 3.14159f; // Convert to degrees
    sprite.setRotation(angle);
    sprite.setPosition(startPosition);
    supportSprite.setPosition(startPosition);
    supportSprite.setRotation(angle);
    // draw the ball sprite at the end and start position
    ballSprite1.setPosition(startPosition);
    ballSprite2.setPosition(endPosition);
    ballSprite1.setScale(finalScale * 5, finalScale * 5);
    ballSprite2.setScale(finalScale * 5, finalScale * 5);
    ballSprite1.setPosition(startPosition.x - std::abs(ballSprite1.getGlobalBounds().width / 2), startPosition.y - std::abs(ballSprite1.getGlobalBounds().height / 2));
    ballSprite2.setPosition(endPosition.x - std::abs(ballSprite2.getGlobalBounds().width / 2), endPosition.y - std::abs(ballSprite2.getGlobalBounds().height / 2));
}

void HoldLaserAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
    target.draw(supportSprite, states);
    target.draw(ballSprite1, states);
    target.draw(ballSprite2, states);
    
}