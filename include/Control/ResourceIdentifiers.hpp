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
		bomb,
		Knight,
		Boar,
		GoblinShooter,
		SwordMinion,


		AK_47,
		SwordMinionSword,
		Buttons,
		ExtraButtons,
		Explosion,
		Particle,
		FinishLine,
		HeartIcon,
		ShieldIcon,
		ManaIcon,
		FuryIcon,
		HeartBar,
		ShieldBar,
		ManaBar,
		FuryBar,
		EmptyBar,
		HUDBar,
		WoodenBackground,
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
		Jungle,
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

