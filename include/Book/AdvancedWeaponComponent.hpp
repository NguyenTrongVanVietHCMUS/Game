#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include "Entity.hpp"
#include <Book/StrategyClass.hpp>

class Weapon2;
class State;   // forward declaration of State

enum class NextType {
    After,
    With,
    WaitingInput
};

struct ComboNode {
    std::unique_ptr<IBehavior> behavior;
    std::unique_ptr<IWeaponAnimation> animation;
    NextType nextType = NextType::After;

    // For WaitingInput
    float inputWindow = 0.0f;
    std::function<bool()> inputCheck;

    // For After
    float requiredDelay = 0.0f;
    float maxGap        = 0.2f;

    // Internal state
    bool started           = false;
    bool animationFinished = false;
    float postFinishTimer  = 0.0f;
    float inputTimer       = 0.0f;

    std::function<void()> onEnter;
};

class AdvanceWeaponComponent {
public:
    AdvanceWeaponComponent(std::shared_ptr<Weapon2> weapon, Entity* owner);

    // Load combo sequence from JSON using your strategy factory
    bool loadFromJson(const nlohmann::json& comboJson,
                      State* map,
                      Entity* owner);

    // Per-frame update
    void update(const sf::Time& dt);

    // Signal input (for WaitingInput)
    void signalInput();

    // Reset combo sequence
    void resetCombo();

    // Draw current animation (optional)
    void draw(sf::RenderTarget& target,
              sf::RenderStates states) const;

    // Change the owner (updates all node.animation owners)
    void setOwner(Entity* newOwner);

private:
    void advanceToNext();

    std::vector<ComboNode> sequence;
    size_t currentIndex = 0;

    bool comboActive     = false;
    bool waitingForInput = false;
    bool inputSignaled   = false;

    std::shared_ptr<Weapon2> weapon;
    Entity* owner = nullptr;
};
