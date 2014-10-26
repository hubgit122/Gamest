#include "ChessGame.h"

namespace CIG
{
    ChessGame::ChessGame(const MyJSONNode &json) : Game(json), JSON_INI(history), chessBoard(json, *this)
    {
    }

    ChessGame &ChessGame::operator=(const ChessGame &g)
    {
        history = g.history;
        chessBoard = g.chessBoard;
        return *this;
    }

    std::string ChessGame::toJSON() const
    {
        ostringstream oss;
        oss << JSON_OBJECT(JSON_COMMA JSON_KEYVALUE(history) JSON_COMMA JSON_KEYVALUE(chessBoard));
        return oss.str();
    }
}

