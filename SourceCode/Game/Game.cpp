#include "Book/Game.hpp"
// Constructor
Game::Game()
: 
    window(sf::VideoMode(width, height), "Live Knight", sf::Style::Close | sf::Style::Titlebar|sf::Style::Resize),
	textures(),
	fonts(),
	music(),
	sounds(),
    stateStack(State::Context(window, textures, fonts, music, sounds, maps))
{
	{
		window.setVerticalSyncEnabled(true); // Enable vertical sync
		window.setFramerateLimit(60); // Limit to 60 FPS
		{
			// load textures 
			ResourceManager::getInstance().load<sf::Texture>(Textures::ID::Knight, "Media/Assets/Characters/Knight/knight_1.png");
			ResourceManager::getInstance().load<sf::Texture>(Textures::ID::Boar, "Media/Assets/Mobs/Boar/NormalBoar.png"); 
			ResourceManager::getInstance().load<sf::Texture>(Textures::ID::GoblinShooter, "Media/Assets/Mobs/GoblinShooter/GoblinShooter.png");
			ResourceManager::getInstance().load<sf::Texture>(Textures::ID::AK_47, "Media/Assets/Weapons/gun/AK_47.png");
		}

		{
			// load maps 

			ResourceManager::getInstance().load<TileMap>(Map::ID::Title, "Media/Assets/Maps/Title/title.world");
			ResourceManager::getInstance().load<TileMap>(Map::ID::Lobby, "Media/Assets/Maps/Lobby/lobby.world");
			ResourceManager::getInstance().load<TileMap>(Map::ID::Jungle, "Media/Assets/Maps/Dungeon/Jungle/jungle.world");
		}

		{
			// load fonts 
			ResourceManager::getInstance().load<sf::Font>(Fonts::ID::Main, "Media/Fonts/Sansation.ttf");
			ResourceManager::getInstance().load<sf::Font>(Fonts::ID::Title, "Media/Fonts/PressStart2P_Regular.ttf");

		}

	
	}
	registerStates();	
	stateStack.pushState(States::Title);

	// Set the frame rate limit 

}   

// Destructor
Game::~Game()   
{

}

void Game::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (window.isOpen())
    {       
        timeSinceLastUpdate += clock.restart();
		Update(sf::Time::Zero); // Initial update to set up the game state
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            PollEvents();
            Update(TimePerFrame); 
            if (stateStack.isEmpty())
				window.close();
        }
        Render(); 
    }
}
// Poll events
void Game::PollEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        stateStack.handleEvent(event);
        if (event.type == sf::Event::Closed)
            window.close() ; 
    }
}

void Game::Update(sf::Time dt)
{
    stateStack.update(dt) ;
}

void Game::Render()
{
    window.clear();
	stateStack.draw();
	window.display();
}

void Game::registerStates()
{
	stateStack.registerState<Title>(States::Title);
	stateStack.registerState<Lobby>(States::Lobby);
	stateStack.registerState<Jungle>(States::Jungle);
	// stateStack.registerState<PauseState>(States::Pause);
	// stateStack.registerState<SettingsState>(States::Settings);
	// stateStack.registerState<ChessGame1PlayerState>(States::ChessGame1Player);
	// stateStack.registerState<ChessGame2PlayersState>(States::ChessGame2Players);
	// stateStack.registerState<PromotionState>(States::PromotionState);
	// stateStack.registerState<CheckMateWhiteState>(States::CheckMateWhite);
	// stateStack.registerState<CheckMateBlackState>(States::CheckMateBlack);
	// stateStack.registerState<StaleMateState>(States::StaleMate);
	// stateStack.registerState<FIFTYMOVERULE>(States::FIFTY_MOVE_RULE);
	// stateStack.registerState<THREEFOLDREPETITION>(States::THREEFOLD_REPETITION);
	// stateStack.registerState<INSUFFICIENTMATERIAL>(States::INSUFFICIENT_MATERIAL);
	// stateStack.registerState<AudioSettingsState>(States::AudioSettings);
	// stateStack.registerState<ChooseBoard>(States::ChooseBoard);
	// stateStack.registerState<ChoosePieces>(States::ChoosePieces);
	// stateStack.registerState<ChooseMusicTheme>(States::ChooseMusicTheme);
	// stateStack.registerState<ChooseMusicMission>(States::ChooseMusicMission);
	// stateStack.registerState<volumeSettings>(States::volumeSettings);
	// stateStack.registerState<MenuPlaysState>(States::MenuPlaysState);
	// stateStack.registerState<ChooseTeamState>(States::ChooseTeamState);
	// stateStack.registerState<NewGameState>(States::NewGame);
	// stateStack.registerState<ChooseLevel>(States::ChooseLevel);
	// stateStack.registerState<Loadgame>(States::Loadgame);
	// stateStack.registerState<SettingOnlyAudio>(States::SettingOnlyAudio);
	// stateStack.registerState<SaveGameState>(States::Savegame);
	// stateStack.registerState<AudioSettingsStateOnlyMusicTheme>(States::AudioSettingsStateOnlyMusicTheme);
}

// Main game loop