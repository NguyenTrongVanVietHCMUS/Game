#include <Book/Projectile2.hpp>
#include <Control/State.hpp>
void Projectile2::setBehavior(std::unique_ptr<IMovement> movement, std::unique_ptr<ICollision> collision)
{
    if (movement) {
        movementStrategy = std::move(movement);
    }
    if (collision) {
        collisionStrategy = std::move(collision);
    }
}

void Projectile2::setMovement(std::unique_ptr<IMovement> movement)
{
    if (movement) {
        movementStrategy = std::move(movement);
    }
}

void Projectile2::setCollision(std::unique_ptr<ICollision> collision)
{
    if (collision) {
        collisionStrategy = std::move(collision);
    }
}

void Projectile2::addTrailEffect(std::unique_ptr<IEffect> effect)
{
    if (effect) {
        trailStrategies.push_back(std::move(effect));
    }
}

void Projectile2::setMovingAnimation(std::unique_ptr<MovingAnimation> animation)
{
    if (animation) {
        movingAnimation = std::move(animation);
        if(movingAnimation){
            if(auto laserAnimation = dynamic_cast<LaserAnimation*>(movingAnimation.get())) {
                laserAnimation->setOwner(this); // Set the owner of the laser animation to this projectile
            }
        }
    }
}

void Projectile2::setAttribute(const std::string& attributeName, float value)
{
    attributes[attributeName] = value;
}

float Projectile2::getAttribute(const std::string& attributeName) const
{
    auto it = attributes.find(attributeName);
    if (it != attributes.end()) {
        return it->second;
    }
    return 0.0f; // Default value if attribute not found
}

bool Projectile2::update(sf::Time dt)
{
    float CurrentLifeTime = getAttribute("CurrentLifeTime");
    CurrentLifeTime += dt.asSeconds(); // Increment the current lifetime by the delta time
    float MaxLifeTime = getAttribute("MaxLifeTime");
    if (CurrentLifeTime >= MaxLifeTime) {

        // Projectile has reached its maximum lifetime, handle destruction
        currentMap->popEntity(this); // Remove the projectile from the map
        return true; // Indicate that the projectile should be removed
    }
    if (movementStrategy) {
        movementStrategy->update(*this, dt);
        if( !movementStrategy->isActive) {
            currentMap->popEntity(this); // Remove the projectile if the movement strategy is inactive
            return true; // Indicate that the projectile should be removed
        }
    }
    // if get CurrentAngle from attribute
    float currentAngle = getAttribute("CurrentAngle") * 180.0f / 3.14f;
    sprite.setRotation(currentAngle);

    sprite.setPosition(getPosition()); // Update the sprite position to match the projectile's position

    for (const auto& effect : trailStrategies) {
        effect->apply(*this);
    }
    setAttribute("CurrentLifeTime", CurrentLifeTime); // Update the current lifetime attribute
    if (movingAnimation) {
        movingAnimation->update(dt); // Update the moving animation if it exists

        if(HitboxMode){
            hitbox.hitbox = movingAnimation->getBoundingBox(); // Update the hitbox based on the moving animation
        } else 
        {
            hitbox.hitbox = sf::FloatRect(
                -100.0f,
                -100.0f,
                0.0f,
                0.0f
            );
        }
    }
    // for every collided Entities
    if(movingAnimation)
    {
        if(auto laserAnimation = dynamic_cast<LaserAnimation*>(movingAnimation.get())) {
            // Do nothing
        } else {
            for (auto entity : collidedEntitiesFlag) {
            collidedEntities[entity] = debounceTime;
        }
        }

    } else {
        for (auto entity : collidedEntitiesFlag) {
            collidedEntities[entity] = debounceTime;
        }
    }
    collidedEntitiesFlag.clear(); // Clear the flag after processing
    for (auto it = collidedEntities.begin(); it != collidedEntities.end(); ) {
        it->second -= dt.asSeconds(); // Decrease the debounce timer
        if (it->second <= 0) {
            it = collidedEntities.erase(it); // Remove expired entities
        } else {
            ++it;
        }
    }

    return true;
}

void Projectile2::collide(Entity* other)
{
    if (collisionStrategy) {
        if (AllowCollide(const_cast<Entity*>(other))) {
            collisionStrategy->collide(*this, other);
            collidedEntitiesFlag.push_back(other);
    
        }
    }
}

bool Projectile2::AllowCollide(Entity* other) const
{
    return collidedEntities.find(other) == collidedEntities.end();
}

void Projectile2::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(movingAnimation) {
        
        movingAnimation->draw(target, states); // Draw the moving animation if it exists
       // hitbox.draw(target, states); //Draw the hitbox for debugging purposes
    } else {
       // hitbox.draw(target, states); // Draw the hitbox for debugging purposes
        target.draw(sprite, states);  
        
    }
     
}

void Projectile2::setSpriteScale(float scale)
{
    if(movingAnimation) {
        movingAnimation->setSpriteScale(scale); // Set the scale of the sprite in the moving animation
    } else sprite.setScale(scale, scale); // Set the scale of the sprite
}


void Projectile2::setSpriteRotation(float angle)
{
    if(movingAnimation) {
        movingAnimation->setSpriteRotation(angle); // Set the rotation of the sprite in the moving animation
    } else {
        sprite.setRotation(angle); // Set the rotation of the sprite
    }
}


Projectile2::Projectile2(std::string name, float lifeTime, sf::Vector2f position, State* currentMap, sf::Texture texture)
: Entity(name, position), currentMap(currentMap) {
    // Load the projectile texture
    std::cerr << "Warning : Using texture from memory, make sure the texture is valid and not destroyed before using it" << std::endl;
    this->texture = texture;
    attributes["MaxLifeTime"] = lifeTime; // Set the maximum lifetime of the projectile
    attributes["CurrentLifeTime"] = 0.0f; // Initialize current lifetime to 0
    sprite.setTexture(texture);
    // update hitbox size
    hitbox.hitbox = sf::FloatRect(position.x, position.y, texture.getSize().x, texture.getSize().y);
    // set origin hitbox to center of the sprite
    sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y);
}

Projectile2::Projectile2(std::string name,float LifeTime,sf::Vector2f position, float scale, State* CurrentMap, std::string texturePath,
std::unique_ptr<IMovement> movement, std::unique_ptr<ICollision> collision, std::unique_ptr<MovingAnimation> animation)
: Entity(name, position), movementStrategy(std::move(movement)), collisionStrategy(std::move(collision)), currentMap(CurrentMap), movingAnimation(std::move(animation)) {
    if (!texture.loadFromFile(texturePath)) {
        throw std::runtime_error("Failed to load projectile texture");
    }   
    this->texturePath = texturePath; // Store the texture path for future reference
    attributes["MaxLifeTime"] = LifeTime; // Set the maximum lifetime of the projectile
    sprite.setTexture(texture);
    // update hitbox size
    hitbox.hitbox = sf::FloatRect(position.x, position.y, texture.getSize().x, texture.getSize().y);
    // set origin hitbox to center of the sprite
    
    sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y);
    sprite.setScale(scale, scale); // Set the scale of the sprite
    // Try cast Moving animation to Laser beam animation
    if (movingAnimation) {
        if (auto laserAnimation = dynamic_cast<LaserAnimation*>(movingAnimation.get())) {
            laserAnimation->setOwner(this);
        } 
    } 
}


Projectile2::Projectile2(std::string name,float LifeTime,sf::Vector2f position, State* CurrentMap, std::string texturePath,
std::unique_ptr<IMovement> movement, std::unique_ptr<ICollision> collision , std::unique_ptr<MovingAnimation> animation)
: Entity(name, position), movementStrategy(std::move(movement)), collisionStrategy(std::move(collision)), currentMap(CurrentMap), movingAnimation(std::move(animation)) {
    // Load the projectile texture
    if (!texture.loadFromFile(texturePath)) {
        throw std::runtime_error("Failed to load projectile texture");
    }
    this->texturePath = texturePath; // Store the texture path for future reference
    attributes["MaxLifeTime"] = LifeTime; // Set the maximum lifetime of the projectile
    sprite.setTexture(texture);
    // update hitbox size
    hitbox.hitbox = sf::FloatRect(position.x, position.y, texture.getSize().x, texture.getSize().y);
    // set origin hitbox to center of the sprite
    
    sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y);
    if (movingAnimation) {
        if (auto laserAnimation = dynamic_cast<LaserAnimation*>(movingAnimation.get())) {
            std::cerr << "Projectile2: Moving animation is a LaserAnimation." << std::endl;
            laserAnimation->setOwner(this);
        } else std::cerr << "Projectile2: Moving animation is not a LaserAnimation." << std::endl;
    }
}

Projectile2* Projectile2::clone(sf::Vector2f direction) const {
    auto *proj = new Projectile2(name, getAttribute("MaxLifeTime"), position, currentMap, texturePath);
    proj->movementStrategy = movementStrategy ? movementStrategy->clone() : nullptr;
    proj->collisionStrategy = collisionStrategy ? collisionStrategy->clone() : nullptr;
    if(proj->collisionStrategy){
        std::cerr << "Cloning projectile with collision strategy" << std::endl;
    } else std::cerr << "WARNING : Cloning projectile without collision strategy" << std::endl;
    proj->movementStrategy->setDirection(direction); // Set the direction for the cloned projectile
    proj->setAttribute("CurrentLifeTime", 0.0f); // Reset the
    if(movingAnimation) {
        proj->movingAnimation = std::make_unique<MovingAnimation>(*movingAnimation, proj->position);
    }
    for (const auto& effect : trailStrategies) {
        proj->trailStrategies.push_back(effect->clone());
    }
    return proj;
}

void Projectile2::selfDelete() {
    currentMap->popEntity(this); 
}

sf::Vector2f Projectile2::getProjDirection(Entity *other) const {
    if (movementStrategy) {
        return movementStrategy->getDirection();
    }
    if(other)
    {
        return other->getPosition() - position;
    }
    std::cerr << "Warning: No movement strategy set and no entity to calculate. RETURN THE DIRECTION TO THE RIGHT\n";
    return sf::Vector2f(0.0f, 5.0f);
}