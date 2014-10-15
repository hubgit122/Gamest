
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
    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    class ChessGame : public Game
    {
        public:
            ChessGame();
            ChessGame(const JSONNode &json);
            virtual ~ChessGame();
            inline virtual string toJSON()const;

            ChessGameConfig config;
            Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM> cb;
            Board<bool, INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2> boardRange;
            Array < Board<CHESSMAN_TYPES, INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2>, PLAYER_NUM, -1 > iniBoards;

            Stack<Move, ChessGameConfig::INT_BOARD_HISTORY_STACK_SIZE, 0> history;
    };

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    ChessGame::~ChessGame()
    {
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    ChessGame::ChessGame(const JSONNode &json) :
        history(),
        chessBoard()
    {
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    ChessGame::ChessGame()
    {

    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    void ChessGame::operator=(const ChessGame &g)
    {
        history = g.history;
        chessBoard = g.chessBoard;
    }
}

#endif /*__CHESS_GAME_H__*/

