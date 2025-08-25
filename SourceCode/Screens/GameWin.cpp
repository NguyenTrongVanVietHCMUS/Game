#include <Screens/GameWin.hpp>
#include<Control/ResourceManager.hpp> 
GameWin::GameWin(StateStack& stack, Context context) :
    State(stack, context)
{
    showInstructionTime = sf::Time::Zero;
    showInstruction = 1;
}

GameWin::~GameWin()
{

}

void GameWin::draw()
{
    sf::Text GameWin;
    GameWin.setFont(ResourceManager::getInstance().get<sf::Font>(Fonts::ID::PixelGame)); // Get the default font
    GameWin.setString("YOU WIN :>"); // Set the GameWin text
    GameWin.setCharacterSize(50); // Set the character size for the GameWin text
    GameWin.setFillColor(sf::Color::White);
    GameWin.setOrigin(GameWin.getLocalBounds().width / 2.f, GameWin.getLocalBounds().height / 2.f); // Set the origin to the center of the GameWin text

    sf::RenderWindow* window = getContext().window;
    sf::Vector2u windowSize = window->getSize();
    GameWin.setPosition(static_cast<float>(windowSize.x) / 2.f, static_cast<float>(windowSize.y) / 2.f); // Set position to middle of the screen
    window->setView(window->getDefaultView());
    window->draw(GameWin);
    if (showInstruction)
    {
        sf::Text instruction;
        instruction.setFont(ResourceManager::getInstance().get<sf::Font>(Fonts::ID::PixelGame)); // Get the default font
        instruction.setString("Press Enter to Reset"); // Set the instruction text
        instruction.setCharacterSize(20); // Set the character size for the instruction text
        instruction.setFillColor(sf::Color::Red);
        instruction.setOrigin(instruction.getLocalBounds().width / 2.f, instruction.getLocalBounds().height / 2.f); // Set the origin to the center of the instruction text
        instruction.setPosition(static_cast<float>(windowSize.x) / 2.f, static_cast<float>(windowSize.y) / 2.f + 50.f); // Set position below the GameWin text
        window->draw(instruction);
    }
}

bool GameWin::update(sf::Time dt)
{
    showInstructionTime += dt;
    if (showInstructionTime >= sf::seconds(0.3f))
    {
        showInstruction = !showInstruction;
        showInstructionTime = sf::Time::Zero;
    }
    return 0;
}
bool GameWin::handleEvent(const sf::Event& event)
{
    sf::RenderWindow* window = getContext().window;
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Enter)
        {
            requestStackPop();
            requestStackPush(States::Lobby);
        }
    }
    if (event.type == sf::Event::Closed)
    {
        requestStackPop();
    }
    return 0;
}
