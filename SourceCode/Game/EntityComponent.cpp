#include <Book/EntityComponent.hpp>

int EntityAttributeActionComponent::getMaxHealth() const {
    return attributes.at(CharacterResourceType::Health).max;
}
int EntityAttributeActionComponent::getMaxMana() const {
    return attributes.at(CharacterResourceType::Mana).max;
}
int EntityAttributeActionComponent::getMaxShield() const {
    return attributes.at(CharacterResourceType::Shield).max;
}
int EntityAttributeActionComponent::getHealth() const {
    return attributes.at(CharacterResourceType::Health).current;
}
int EntityAttributeActionComponent::getMana() const {
    return attributes.at(CharacterResourceType::Mana).current;
}
int EntityAttributeActionComponent::getShield() const {
    return attributes.at(CharacterResourceType::Shield).current;
}
void EntityAttributeActionComponent::setMaxHealth(int value) {
    attributes[CharacterResourceType::Health].setMax(value);
}
void EntityAttributeActionComponent::setMaxMana(int value) {
    attributes[CharacterResourceType::Mana].setMax(value);
}
void EntityAttributeActionComponent::setMaxShield(int value) {
    attributes[CharacterResourceType::Shield].setMax(value);
}
void EntityAttributeActionComponent::setHealth(int value) {
    attributes[CharacterResourceType::Health].setCurrent(value);
}
void EntityAttributeActionComponent::setMana(int value) {
    attributes[CharacterResourceType::Mana].setCurrent(value);
}
void EntityAttributeActionComponent::setShield(int value) {
    attributes[CharacterResourceType::Shield].setCurrent(value);
}

const EntityResource* EntityAttributeActionComponent::getAttribute(CharacterResourceType type) const {
    auto it = attributes.find(type);
    if (it != attributes.end()) {
        return &it->second;
    }
    return nullptr;
}

void EntityAttributeActionComponent::TakeDamage(int damage) {
    elapseTime = 0.0f; // Reset elapse time for shield regeneration
    if (attributes[CharacterResourceType::Shield].current > 0) {
        int shieldDamage = std::min(damage, static_cast<int>(attributes[CharacterResourceType::Shield].current));
        attributes[CharacterResourceType::Shield].change(-shieldDamage);
        damage -= shieldDamage;
    }
    attributes[CharacterResourceType::Health].change(-damage);
}
void EntityAttributeActionComponent::Heal(int amount) {
    attributes[CharacterResourceType::Health].change(amount);
    if (attributes[CharacterResourceType::Health].current > attributes[CharacterResourceType::Health].max) {
        attributes[CharacterResourceType::Health].setCurrent(attributes[CharacterResourceType::Health].max);
    }
}

void EntityAttributeActionComponent::update(sf::Time dt) {
    elapseTime += dt.asSeconds();
    if(elapseTime >= TimeToRegenShield && attributes[CharacterResourceType::Shield].current < attributes[CharacterResourceType::Shield].max) {
        updateShieldRegen(dt);
    }
}

void EntityAttributeActionComponent::updateShieldRegen(sf::Time dt) {
    elapseTimeShield += dt.asSeconds();
    if (elapseTimeShield >= TimeShieldRegenRate) {
        attributes[CharacterResourceType::Shield].change(1);
        elapseTimeShield = 0.0f;
    }
}

void EntityAttributeActionComponent::setAttribute(CharacterResourceType type, int current, int max) {
    attributes[type] = EntityResource(current, max);
}

bool EntityAttributeActionComponent::isDeath() const {
    return attributes.at(CharacterResourceType::Health).isEmpty();
}