#include<Game.hpp>
int main()
{
    Game game = Game(600,800) ; 
    while(game.Running())
    {
        game.Update() ; 
        game.Draw() ; 
    }

    return 0;
}