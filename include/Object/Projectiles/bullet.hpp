#pragma once
#include <Book/Projectile.hpp>

class Bullet : public Projectile
{
public:
    Bullet(std::string name, const sf::Vector2f& position, const sf::Vector2f& direction, float speed = 0.0f, float damage = 0.0f);
    bool update(const sf::Time& dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool handleEvent(const sf::Event& event, sf::RenderWindow* window) override;

};
