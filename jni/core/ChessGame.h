
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
    class ChessGame : public Game
    {
    public:
        ChessGame(const JSONNode &json);
        virtual ~ChessGame(){}
        inline virtual string toJSON()const;

        ChessGameConfig config;
        Chessboard chessBoard;
        Stack<Move, INT_BOARD_HISTORY_STACK_SIZE, 0> history;
    private:
        ChessGame::ChessGame()
        {}
    };
}

#endif /*__CHESS_GAME_H__*/

