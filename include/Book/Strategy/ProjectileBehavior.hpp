#pragma once
#include <Book/Utility.hpp>
#include <Book/Entity.hpp>
#include <Book/Projectile2.hpp>

class StraightMovement : public IMovement
{
private:
    float speedX, speedY;

public:
    StraightMovement(float speedX, float speedY) : speedX(speedX), speedY(speedY) {}

    void update(Projectile2& projectile, const sf::Time& dt) override
    {
        // Update the position of the projectile based on its speed and the elapsed time
        projectile.position.x += speedX * dt.asSeconds();
        projectile.position.y += speedY * dt.asSeconds();
    }

    std::unique_ptr<IMovement> clone() const override
    {
        return std::make_unique<StraightMovement>(*this);
    }
};
