#include <Screens/GameOver.hpp>
#include<Control/ResourceManager.hpp> 
GameOver::GameOver(StateStack& stack, Context context) :
    State(stack, context)
{
	showInstructionTime = sf::Time::Zero;
    showInstruction = 1; 
}

GameOver::~GameOver()
{

}

void GameOver::draw()
{
    sf::Text GameOver;
    GameOver.setFont(ResourceManager::getInstance().get<sf::Font>(Fonts::ID::PixelGame)); // Get the default font
    GameOver.setString("YOU LOST :<"); // Set the GameOver text
    GameOver.setCharacterSize(50); // Set the character size for the GameOver text
    GameOver.setFillColor(sf::Color::Red);
    GameOver.setOrigin(GameOver.getLocalBounds().width / 2.f, GameOver.getLocalBounds().height / 2.f); // Set the origin to the center of the GameOver text

    sf::RenderWindow* window = getContext().window;
    sf::Vector2u windowSize = window->getSize();
    GameOver.setPosition(static_cast<float>(windowSize.x) / 2.f, static_cast<float>(windowSize.y) / 2.f); // Set position to middle of the screen
    window->setView(window->getDefaultView()); 
    window->draw(GameOver);
    if (showInstruction)
    {
        sf::Text instruction; 
	    instruction.setFont(ResourceManager::getInstance().get<sf::Font>(Fonts::ID::PixelGame)); // Get the default font
	    instruction.setString("Press Enter to Reset"); // Set the instruction text
	    instruction.setCharacterSize(20); // Set the character size for the instruction text
	    instruction.setFillColor(sf::Color::White);
	    instruction.setOrigin(instruction.getLocalBounds().width / 2.f, instruction.getLocalBounds().height / 2.f); // Set the origin to the center of the instruction text
	    instruction.setPosition(static_cast<float>(windowSize.x) / 2.f, static_cast<float>(windowSize.y) / 2.f + 50.f); // Set position below the GameOver text
        window->draw(instruction); 
    }
}

bool GameOver::update(sf::Time dt)
{
	showInstructionTime += dt;
    if (showInstructionTime>= sf::seconds(3.f))
    {
		showInstruction = !showInstruction;
        showInstructionTime= sf::Time::Zero;
    }
    return 0;
}
bool GameOver::handleEvent(const sf::Event& event)
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
