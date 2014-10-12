
#include "ChessGame.h"

namespace CIG
{
    ChessGame::~ChessGame()
    {
    }

    ChessGame::ChessGame(string json):
        history(),
        chessBoard()
    {
    }

    ChessGame::ChessGame()
    {

    }

    void ChessGame::operator=(const ChessGame &g)
    {
        history = g.history;
        chessBoard = g.chessBoard;
    }
}
