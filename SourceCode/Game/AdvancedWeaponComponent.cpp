#include <Book/AdvancedWeaponComponent.hpp>
#include <Control/StrategyFactory.hpp>
#include <Book/Weapon2.hpp>
AdvanceWeaponComponent::AdvanceWeaponComponent(std::shared_ptr<Weapon2> weapon_, Entity* owner_)
    : weapon(weapon_), owner(owner_) {}

bool AdvanceWeaponComponent::loadFromJson(const nlohmann::json& comboJson, State* map, Entity* owner) {
    sequence.clear();
    currentIndex = 0;
    comboActive = true;
    waitingForInput = false;
    inputSignaled = false;

    for (const auto& nodeJson : comboJson.at("combo")) {
        ComboNode node;

        // Behavior
        if (nodeJson.contains("behavior")) {
            node.behavior = StrategyFactory::createBehavior(nodeJson.at("behavior"), map);
        }

        // Animation
        if (nodeJson.contains("animation")) {
            node.animation = StrategyFactory::createAnimation(nodeJson.at("animation"), owner);
        }

        // NextType
        std::string nt = nodeJson.value("nextType", "After");
        if (nt == "After") node.nextType = NextType::After;
        else if (nt == "With") node.nextType = NextType::With;
        else if (nt == "WaitingInput") node.nextType = NextType::WaitingInput;

        // Timing fields
        node.requiredDelay = nodeJson.value("delay", 0.0f);
        node.maxGap = nodeJson.value("maxGap", 0.2f);

        if (node.nextType == NextType::WaitingInput) {
            node.inputWindow = nodeJson.value("inputWindow", 0.5f);
            std::string inputName = nodeJson.value("input", "");

            // Example inputCheck: replace with your real input system.
            node.inputCheck = [this, inputName]() -> bool {
                // placeholder: you would check actual input state here, e.g. Input::isPressed(inputName)
                if (inputSignaled) {
                    inputSignaled = false;
                    return true;
                }
                return false;
            };
        }

        // Optional onEnter hook from JSON could be added here if needed

        sequence.push_back(std::move(node));
    }
}

void AdvanceWeaponComponent::update(const sf::Time& dt) {
    if (sequence.empty()) return;
    if (!comboActive) return;

    ComboNode& node = sequence[currentIndex];

    if (!node.started) {
        // Enter node
        if (node.onEnter) node.onEnter();

        if (node.behavior) {
            // Example: activate behavior; adapt signature as needed
            node.behavior->activate(*weapon, owner);
        }
        if (node.animation) {
            node.animation->play();
        }
        node.started = true;
        node.animationFinished = false;
        node.postFinishTimer = 0.0f;
        node.inputTimer = 0.0f;
        waitingForInput = false;
    }

    // Update animation
    if (node.animation) {
        node.animation->update(*weapon, dt);
        // Here you need a way to detect finished: assuming animation has TotalTime and current time inside.
        // Placeholder: you could expose a method isDone() in concrete animations.
        // For simplicity, let's assume animationFinished is set externally or inferred; so here we simulate:
        // (In real code replace with actual check)
        // e.g., animationDone = dynamic_cast<YourConcreteAnimation*>(node.animation.get())->isFinished();
        // For now, we fake it by checking an internal timer stored in animation if accessible.
    }

    // Simplified: assume animation is finished if we somehow detect it. For demonstration, skip.
    bool animationDone = node.animation->isDone(); // you must set this in your real animation when complete

    switch (node.nextType) {
        case NextType::After:
            if (animationDone) {
                node.postFinishTimer += dt.asSeconds();
                if (node.postFinishTimer >= node.requiredDelay) {
                    // advance immediately after requiredDelay
                    advanceToNext();
                } else if (node.postFinishTimer > node.requiredDelay + node.maxGap) {
                    resetCombo();
                }
            }
            break;
        case NextType::With:
            // Start next immediately (no need to wait for finish)
            advanceToNext();
            break;
        case NextType::WaitingInput:
            if (!waitingForInput) {
                if (animationDone) {
                    waitingForInput = true;
                    node.inputTimer = 0.0f;
                }
            } else {
                node.inputTimer += dt.asSeconds();
                if (node.inputCheck && node.inputCheck()) {
                    advanceToNext();
                } else if (node.inputTimer > node.inputWindow) {
                    resetCombo();
                }
            }
            break;
    }
}

void AdvanceWeaponComponent::advanceToNext() {
    // Reset state of current node so if we loop it behaves
    if (currentIndex + 1 >= sequence.size()) {
        // Reached end: reset or stop
        resetCombo();
        return;
    }
    currentIndex++;
    sequence[currentIndex].started = false;
    waitingForInput = false;
}

void AdvanceWeaponComponent::signalInput() {
    inputSignaled = true;
}

void AdvanceWeaponComponent::resetCombo() {
    currentIndex = 0;
    comboActive = true;
    waitingForInput = false;
    inputSignaled = false;
    for (auto& node : sequence) {
        node.started = false;
        node.animationFinished = false;
        node.postFinishTimer = 0.0f;
        node.inputTimer = 0.0f;
    }
}

void AdvanceWeaponComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (sequence.empty()) return;
    const ComboNode& node = sequence[currentIndex];
    if (node.animation) {
        node.animation->draw(target, states);
    }
}


void AdvanceWeaponComponent::setOwner(Entity* newOwner) {
    owner = newOwner;
    for (auto& node : sequence) {
        if (node.animation) {
            node.animation->SetOwner(newOwner);
        }
    }
}