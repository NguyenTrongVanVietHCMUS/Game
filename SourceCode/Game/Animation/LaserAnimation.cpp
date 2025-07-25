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