#include <Book/MovingAnimation.hpp>

void laserAimAnimation::draw(sf::RenderTarget& target, sf::RenderStates states)const {

    sf::Vertex line[] = {
        sf::Vertex(BeginPosition, sf::Color::Red),
        sf::Vertex(TargetPosition, sf::Color::Red)
    };
    line[0].color = sf::Color::Red;
    line[1].color = sf::Color::Red;
    target.draw(line, 2, sf::Lines);
}

void LaserAnimation::update(sf::Time dt) {

    elapseTime += dt.asMilliseconds();
    float ScaleY = sin(elapseTime);
    sprite.setScale(scale, ScaleY * 3);
    float angle = std::atan2(endPosition.y - startPosition.y, endPosition.x - startPosition.x) * 180.0f / 3.14159f; // Convert to degrees
    sprite.setRotation(angle);
    sprite.setPosition(startPosition);
}