#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "utilities.h"

#define JNICALL
#define  JNIEXPORT
using namespace std;

class Game;
extern map<int, Game *> games;
extern jstring error;
extern "C"
{
    /*****************
    建立新游戏
    *****************/
    JNIEXPORT void JNICALL newGame(CIG:: GAME_TYPE id, jsize gameId);
    /*****************
    载入储存的游戏
    *****************/
    JNIEXPORT void JNICALL loadGame(jbyteArray jsonString);
    JNIEXPORT jstring JNICALL getGameHead(jsize gameId);
    JNIEXPORT jstring JNICALL getGameDetails(jsize gameId);
    JNIEXPORT void JNICALL abortGame(jsize gameId);
    JNIEXPORT void JNICALL addPlayer(jsize gameId, jsize playId, jsize index);
    JNIEXPORT jsize JNICALL addAI(jsize gameId, jsize index, jsize level, jsize timeout);
    JNIEXPORT void JNICALL replaceAiWithPlayer(jsize gameId, jsize playerId, jsize index);
    JNIEXPORT void JNICALL replacePlayerWithAi(jsize gameId, jsize index, jsize playerId);
    JNIEXPORT void JNICALL quitPlayer(jsize gameId, jsize playerId);
    JNIEXPORT jstring JNICALL saveGame(jsize gameId);
    JNIEXPORT void JNICALL playerAction(jsize gameId, jsize playerId, jbyteArray jsonString);
}
#endif