#pragma once
#include <Book/StrategyClass.hpp>
#include <Book/Utility.hpp>
#include <Control/State.hpp>
class Weapon2;
enum class ContinueMode {
    AFTER,  // Continue after the current action
    WAITING_INPUT
};

struct ComboNode
{
    std::unique_ptr<IBehavior> behavior; // Behavior to execute
    std::unique_ptr<IWeaponAnimation> animation; // Animation to play

    // Waiting input
    float inputWindow = 0.0f;
    bool isInputActive = false; // Whether input is active
    void inputActive() {isInputActive = true;} // Reset input window when input is active
    bool animationFinished() const {
        return animation->isDone();
    }
    float requiredDelay = 0.0f; // Required delay before the next action
    float maxGap = 0.1f; // Maximum gap allowed between actions

    bool started = false; // Whether the combo has started
    float inputTimer = 0.0f; // Timer for input window
    ContinueMode continueMode = ContinueMode::AFTER; // Default continue mode is AFTER

    void init()
    {
        inputTimer = 0.0f; // Reset input timer
        started = false; // Reset started state
        isInputActive = false; // Reset input active state
    }
};


class AdvancedWeaponComponent 
{
public:
    AdvancedWeaponComponent(Weapon2* weapon, Entity* owner);

    void loadFromJson(const nlohmann::json& data, State *map, Entity* owner);
    void update(sf::Time dt);
    void signalInput();
    void resetCombo();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    void advanceToNext();

private:
    std::vector<ComboNode> comboNodes; // List of combo nodes
    std::vector<ComboNode>::iterator currentComboNode; // Current combo node being executed
    Weapon2* weapon;
    Entity* owner;
};