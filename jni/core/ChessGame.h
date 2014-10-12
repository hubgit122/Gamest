
#ifndef __CHESS_GAME_H__
#define __CHESS_GAME_H__

#include "ChessGameConfig.h"
#include "Array.h"
#include "Object.h"
#include "ChessBoard.h"
#include "GameHead.h"
#include "Stack.h"
#include "Game.h"

namespace CIG
{
    class ChessGame: public Game
    {
        public:
            ChessGame();
            ChessGame(string json);
            virtual ~ChessGame();

            ChessGameConfig config;
            Chessboard cb;
            Stack<Move, ChessGameConfig::INT_BOARD_HISTORY_STACK_SIZE, 0> history;
    };
}

#endif /*__CHESS_GAME_H__*/

