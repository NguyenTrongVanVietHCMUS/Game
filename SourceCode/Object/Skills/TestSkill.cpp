#include "Object/Skills/TestSkill.hpp"

void TestSkill::execute(Entity* user) 
{
    std::cerr << "Executing TestSkill" << std::endl;
    triggerCooldown();

    // Get the position from user entity
    sf::Vector2f userPosition = user->getPosition();
    // Use the position and mouse position to determine the direction of the bullet
    sf::Vector2f bulletDirection = _MousePosition - userPosition;
    // Check if the direction is zero, if so, set a default direction
    if (bulletDirection == sf::Vector2f(0.f, 0.f)) {
        bulletDirection = user->getDirection(); // Use the user's direction if mouse position is not set
    }
    // Create 2 bullets, one for each side of the user, No need to normalize
    Bullet *bullet = new Bullet("Bullet",user->getPosition(), bulletDirection, ProjectileSpeed , 20.0f);
    _projectileHolder.addProjectile(bullet);
}

void TestSkill::update(sf::Time dt) 
{
    if (_cooldownRemaining > sf::Time::Zero) {
        //std::cerr << "Updating TestSkill cooldown : " << _cooldownRemaining.asSeconds() << std::endl;
        _cooldownRemaining -= dt;
    } 
    // if triggered, update the projectiles
    if(_isTriggered){
        _MousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    }
    _projectileHolder.updateProjectiles(dt);
}

void TestSkill::handleEvent(const sf::Event& event, sf::RenderWindow* window) 
{
    // Handle events related to the skill here
    _projectileHolder.handleEvents(event, window);

    // Left click to trigger the skill
    
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
    
        // Get the mouse position in world coordinates
        _MousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        std::cerr << "Mouse Position: " << _MousePosition.x << ", " << _MousePosition.y << std::endl;
        triggerSkill();
        this->window = window; // Set the window pointer for event handling
    }else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        // Reset the triggered state when the mouse button is released
        resetTriggered();
    }
}


Skill* TestSkill::clone() 
{
    return new TestSkill(_cooldownTime); // Create a new instance of TestSkill
}

void TestSkill::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    _projectileHolder.drawProjectiles(target, states);
}