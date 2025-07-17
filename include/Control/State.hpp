#pragma once 
#include <Book/Utility.hpp>
#include <Control/StateIdentifiers.hpp>
#include <Control/ResourceIdentifiers.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include<Book/TileMap.hpp>
#include <memory>


namespace sf
{
	class RenderWindow;
}
class StateStack;
class MusicPlayer;
class SoundPlayer;
class State
{
	public:
		typedef std::unique_ptr<State> Ptr;

		struct Context
		{
								Context(
									sf::RenderWindow& window, 
									TextureHolder& textures,
								 	FontHolder& fonts,
									MusicPlayer& music, 
									SoundPlayer& sounds,
									MapHolder& maps);

			sf::RenderWindow*	window;
			TextureHolder*		textures;
			FontHolder*			fonts;
			MusicPlayer*		music;
			SoundPlayer*		sounds;
			MapHolder*			maps;
		};


	public:
							State(StateStack& stack, Context context);
		virtual				~State();

		virtual void		draw(){return;}
		virtual bool		update(const sf::Time& dt){return 0 ; }
		virtual bool		handleEvent(const sf::Event& event) {
			return false;
		}
		virtual void 	    pushEntity(Entity* entity);
		virtual void 	    popEntity(Entity* entity);
		virtual Entity*		GetClosestEntity(Entity::Type type, sf::Vector2f position) const;
		virtual void        handleCollision(); 

	protected:
		void				requestStackPush(States::ID stateID);
		void				requestStackPop();
		void				requestStateClear();
		Context				getContext() const;

	protected :
		StateStack*			mStack;
		Context				mContext;
		TileMap* map ; 
	
};

