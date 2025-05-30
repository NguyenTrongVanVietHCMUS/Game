#pragma once 

#include "Control/StateIdentifiers.hpp"
#include "Control/ResourceIdentifiers.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <Control/State.hpp>
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

		virtual void		draw(){return;};
		virtual bool		update(sf::Time dt){return 0 ; };
		virtual bool		handleEvent(const sf::Event& event){return false ;}


	protected:
		void				requestStackPush(States::ID stateID);
		void				requestStackPop();
		void				requestStateClear();

		Context				getContext() const;

	protected :
		StateStack*			mStack;
		Context				mContext;
};

