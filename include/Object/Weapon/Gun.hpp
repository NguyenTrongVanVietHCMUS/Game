#include "Book/Weapon.hpp"
#include <Object/SkillLibraryUtility.hpp>

class Gun : public Weapon
{
public:
    Gun();
    ~Gun();

    // Override methods from Weapon interface
    void draw(sf::RenderWindow& window, sf::RenderStates states) override;
    void handleEvent(const sf::Event& event) override;
};