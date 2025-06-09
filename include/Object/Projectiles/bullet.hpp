#pragma once
#include <Book/Projectile.hpp>

class Bullet : public Projectile
{
public:
    Bullet(const sf::Vector2f& position, const sf::Vector2f& direction);
    void update(sf::Time dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void handleEvent(const sf::Event& event) override;

};
