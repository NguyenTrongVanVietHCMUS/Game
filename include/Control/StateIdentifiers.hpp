#pragma once 	
namespace States
{
	enum ID
	{
		None,
		Title,
		Lobby, 
		Pause,
		Settings,
		SettingOnlyAudio,
		ChessGame1Player,
		ChessGame2Players,
		PromotionState,
		CheckMateWhite,
		CheckMateBlack,
		StaleMate,
		INSUFFICIENT_MATERIAL,
		THREEFOLD_REPETITION,
		FIFTY_MOVE_RULE,
		AudioSettings,
		ChooseBoard,
		ChoosePieces,
		ChooseMusicTheme,
		ChooseMusicMission,
		volumeSettings,
		MenuPlaysState,
		ChooseTeamState,
		NewGame,
		ChooseLevel,
		Loadgame,
		Savegame,
		AudioSettingsStateOnlyMusicTheme,
	};
}

