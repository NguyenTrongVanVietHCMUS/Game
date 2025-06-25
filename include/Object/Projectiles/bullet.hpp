#pragma once
#include <Book/Projectile.hpp>

class Bullet : public Projectile
{
public:
    Bullet(std::string name, const sf::Vector2f& position, const sf::Vector2f& direction);
    bool update(const sf::Time& dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool handleEvent(const sf::Event& event, sf::RenderWindow* window) override;

};
