#pragma once 
// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}
class TileMap;
namespace Textures
{
	enum ID
	{
		Knight,
		Boar,
		GoblinShooter,
		AK_47,
		TitleScreen,
		Buttons,
		ExtraButtons,
		Explosion,
		Particle,
		FinishLine,
		WoodenBackground,
		WHITEPAWN,
		WHITEKNIGHT,
		WHITEBISHOP,
		WHITEROOK,
		WHITEQUEEN,
		WHITEKING,
		BLACKPAWN,
		BLACKKNIGHT,
		BLACKBISHOP,
		BLACKROOK,
		BLACKQUEEN,
		BLACKKING,
		FLIPBUTTON,
		ModernWHITEPAWN,
		ModernWHITEKNIGHT,
		ModernWHITEBISHOP,
		ModernWHITEROOK,
		ModernWHITEQUEEN,
		ModernWHITEKING,
		ModernBLACKPAWN,
		ModernBLACKKNIGHT,
		ModernBLACKBISHOP,
		ModernBLACKROOK,
		ModernBLACKQUEEN,
		ModernBLACKKING,
		CartoonWHITEPAWN,
		CartoonWHITEKNIGHT,
		CartoonWHITEBISHOP,
		CartoonWHITEROOK,
		CartoonWHITEQUEEN,
		CartoonWHITEKING,
		CartoonBLACKPAWN,
		CartoonBLACKKNIGHT,
		CartoonBLACKBISHOP,
		CartoonBLACKROOK,
		CartoonBLACKQUEEN,
		CartoonBLACKKING,
		NONE
	};
}

namespace Shaders
{
	enum ID
	{
	};
}

namespace Fonts
{
	enum ID
	{
		Title,
		Main,
	};
}

namespace Music
{
	enum ID
	{
		MusicTheme1,
		MusicTheme2,
		MusicTheme3,
		MusicMission1,
		MusicMission2,
		MusicMission3,
	};
}
namespace Map
{
	enum ID
	{
		Title,
		Lobby, 
		Jungle,
	};
}
namespace SoundEffect
{
	enum ID
	{
		Button,
		movechess,
		capturemove,
		movecheck,
		gameend,
		gamedraw,
	};
}
// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>			TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>					FontHolder;
typedef ResourceHolder<TileMap,Map::ID>					MapHolder;
typedef ResourceHolder<sf::Shader, Shaders::ID>				ShaderHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID>	SoundBufferHolder;

