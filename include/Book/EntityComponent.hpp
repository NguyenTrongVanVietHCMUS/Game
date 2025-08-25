#pragma once
#include <Book/Utility.hpp>
struct EntityResource{
    int current = 0;
    int max = 0;
    EntityResource(int current, int max) : current(current), max(max) {}
    EntityResource() = default;

    void setCurrent(int value) {
        current = value;
        current = std::max(0, current); // Ensure current is not negative
        current = std::min(current, max); // Ensure current does not exceed max
    }

    void setMax(int value) {
        max = value;
    }

    float ratio() const {
        if (max == 0) return 0;
        return current / max;
    }

    bool isFull() const {
        return current >= max;
    }

    bool isEmpty() const {
        return current <= 0;
    }

    void change(int value) {
        setCurrent(current + value);
    }
};

enum class CharacterResourceType {
    Health,
    Mana,
    Shield
};

class EntityAttributeActionComponent
{
protected:
    std::unordered_map<CharacterResourceType, EntityResource> attributes{
        {CharacterResourceType::Health, EntityResource(100, 100)},
        {CharacterResourceType::Mana, EntityResource(100, 100)},
        {CharacterResourceType::Shield, EntityResource(50, 50)}
    };
    float elapseTime = 0.0f;
    float elapseTimeShield = 0.0f; 
    float TimeToRegenShield = 5.0f; 
    float TimeShieldRegenRate = 0.1f;
    void updateShieldRegen(sf::Time dt);
public:
    EntityAttributeActionComponent() = default;
    virtual ~EntityAttributeActionComponent() = default;

    // Getters for the attributes
    virtual int getMaxHealth() const;
    virtual int getMaxMana() const;
    virtual int getMaxShield() const;
    virtual int getHealth() const;
    virtual int getMana() const;
    virtual int getShield() const;
    virtual const EntityResource* getAttribute(CharacterResourceType type) const;
    virtual void setAttribute(CharacterResourceType type, int current, int max);

    // Setters for the attributes
    virtual void setMaxHealth(int value);
    virtual void setMaxMana(int value);
    virtual void setMaxShield(int value);
    virtual void setHealth(int value);
    virtual void setMana(int value);
    virtual void setShield(int value);

    // Additional methods can be added as needed
    virtual void TakeDamage(int damage);
    virtual void Heal(int amount);

    // additional method for flag
    virtual bool isDeath() const;
    // update
    virtual void update(sf::Time dt);
};