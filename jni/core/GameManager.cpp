#include "GameManager.h"
using namespace CIG;

map<int, Game *> games;

JNIEXPORT void JNICALL newGame(CIG::GAME_TYPE id, jsize gameId)
{
    if(id > 0) //∆Â¿‡”Œœ∑
    {
        ChessGame *cg = new ChessGame();
        games.insert(gameId,)
    }
}



