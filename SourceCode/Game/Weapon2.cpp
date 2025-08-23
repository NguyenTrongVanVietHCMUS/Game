#include <Book/Weapon2.hpp>
#include <Book/AdvancedWeaponComponent.hpp>
void Weapon2::setBehavior(std::unique_ptr<IBehavior> newBehavior)
{
    if (newBehavior) {
        behavior = std::move(newBehavior);
    }
}

void Weapon2::setStat(const std::string& statName, float value)
{
    stats[statName] = value;
}

float Weapon2::getStat(const std::string& statName) const
{
    auto it = stats.find(statName);
    if (it != stats.end()) {
        return it->second;
    }
    return 0.0f; // Default value if stat not found
}

void Weapon2::activate(Entity*target)
{
    if( cooldownBehavior && !cooldownBehavior->isReady()) {
        return; // If the weapon is on cooldown, do not activate
    // Play âm thanh ở đây
    } else {
        cooldownBehavior->reset(); // Reset cooldown if ready
    }
    if (behavior) {
        sound.play();
        behavior->activate(*this, target);
    }
    if( animation) {
        animation->play(); // Start the animation when the weapon is activated
    }
}

bool Weapon2::update(sf::Time dt)
{
    type = Entity::Type::Weapon; // Set the type of the entity to Weapon
    if(ishold && cooldownBehavior) {
        cooldownBehavior->update(dt); // Update cooldown behavior
    }

    if(ishold && animation) {
        animation->update(*this, dt);
    }

    UpdateBulletSpawnPosition();
    return true;
}

void Weapon2::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
        if (animation) {
        animation->draw(target, states);
    }
    sf::CircleShape dot(3);
    dot.setFillColor(sf::Color::Red);
    dot.setOrigin(3, 3);
    dot.setPosition(OriginalBulletSpawnPosition);
    target.draw(dot, states);
}

sf::Vector2f Weapon2::GetProjectileSpawnPosition() const
{
    return OriginalBulletSpawnPosition;
}

void Weapon2::UpdateBulletSpawnPosition() {
    // Update the bullet spawn position based on the weapon's position and scale bullet spawn and original rotation
    float originalAngle = getStat("OriginalAngle");
    float angleRad = originalAngle * 3.14159f / 180.0f; // Convert degrees to radians
    sf::Vector2f lengthAfterScale;
    
    if(animation)
    {
        sf::Vector2f SpriteSize = animation->getSpriteSize();
        lengthAfterScale.x = SpriteSize.x * ScaleBulletSpawnPosition.x;
        lengthAfterScale.y = SpriteSize.y * ScaleBulletSpawnPosition.y;
    } else lengthAfterScale = {0.0f, 0.0f};
    // Using current original angle and lengthAfterScale to get the position
    OriginalBulletSpawnPosition = {
        std::cos(angleRad) * lengthAfterScale.x - std::sin(angleRad) * lengthAfterScale.y,
        std::sin(angleRad) * lengthAfterScale.x + std::cos(angleRad) * lengthAfterScale.y
    };
    OriginalBulletSpawnPosition = position + OriginalBulletSpawnPosition;
    // Draw a small circle at the postion
}

Entity::Type Weapon2::ProjectileTypeTransform(Entity* entity) const {
    switch (entity->type)
    {
    case Entity::Type::Enemy: case Entity::Type::EnemyProjectile:
        return Entity::Type::EnemyProjectile; // Transform enemy to ally projectile
    case Entity::Type::Ally: case Entity::Type::AllyProjectile:
        return Entity::Type::AllyProjectile; // Transform ally to enemy projectile
    default:
        return Entity::Type::Entity; // Default case, no transformation
    }
}

void Weapon2::switchHold( bool ishold, Entity* owner)
{
    if(this->ishold == ishold) {
        if (owner) {
            if (animation) {
                animation->SetOwner(owner); // Set the owner for the animation
            }
            if(advanceComponent) {
                advanceComponent->setOwner(owner); // Set the owner for the advanced component
            }
        }
        return; // No change in hold state
    }
    this->ishold = ishold;
    if(CurrentMap){
        if (ishold) {
            CurrentMap->popEntityNoDelete(this);
            if (owner) {
                if(animation) {
                    animation->SetOwner(owner); // Set the owner for the animation
                }   
                if(advanceComponent) {
                    advanceComponent->setOwner(owner); // Set the owner for the advanced component
                }
            }
        } else {
            this->setStat("TargetPosX", this->getPosition().x + 10);
            this->setStat("TargetPosY", this->getPosition().y);
            if(animation)
            {
                animation->update(*this, sf::seconds(0)); // Update the animation to the current state
            }
            if(advanceComponent) {
                advanceComponent->update(sf::seconds(0)); // Update the advanced component to the current state
            }
            
            CurrentMap->pushEntity(this->shared_from_this());
        }
    }
}


void Weapon2::setSound(std::string soundPath) {
    if (soundPath == "Nothing")
    {
        return; 
    }
    if(!soundBuffer.loadFromFile(soundPath))abort(); // Load the sound from the specified path
	sound.setBuffer(soundBuffer); // Set the sound buffer for the sound
    //std::cerr << "Sound set : "<< soundPath << std::endl;
}