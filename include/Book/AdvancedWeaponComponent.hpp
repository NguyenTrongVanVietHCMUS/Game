#pragma once
#include <vector>
#include <memory>
#include <functional>
#include <string>
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include "Weapon2.hpp"        
#include "Entity.hpp"

enum class NextType {
    After,
    With,
    WaitingInput
};

struct ComboNode {
    std::unique_ptr<IBehavior> behavior;
    std::unique_ptr<IWeaponAnimation> animation;
    NextType nextType = NextType::After;

    // for WaitingInput
    float inputWindow = 0.0f;
    std::function<bool()> inputCheck; // returns true when continuation input is detected

    // for After: optional delay before advancing, and max gap before reset
    float requiredDelay = 0.0f;
    float maxGap = 0.2f; // if next doesn't start within this after requiredDelay, reset

    // internal state
    bool started = false;
    bool animationFinished = false;
    float postFinishTimer = 0.0f;
    float inputTimer = 0.0f;

    std::function<void()> onEnter; // optional hook
};

class AdvanceWeaponComponent {
public:
    AdvanceWeaponComponent(std::shared_ptr<Weapon2> weapon, Entity* owner);

    // load combo sequence from JSON using your strategy factory
    void loadFromJson(const nlohmann::json& comboJson, State* map, Entity* owner);
    // per-frame update
    void update(const sf::Time& dt);
    // external trigger for input (alternative to polling inside inputCheck)
    void signalInput();
    void resetCombo();
    // optional: draw current animation
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setOwner(Entity* newOwner);
private:
    void advanceToNext();

    std::vector<ComboNode> sequence;
    size_t currentIndex = 0;

    bool comboActive = false;
    bool waitingForInput = false;

    std::shared_ptr<Weapon2> weapon = nullptr;
    Entity* owner = nullptr;

    // buffered input flag (for manual signalInput)
    bool inputSignaled = false;
};
