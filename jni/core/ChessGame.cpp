#include "ChessGame.h"

namespace CIG
{


    ChessGame::ChessGame(const JSONNode &json) :
            config(json.at("config"))
            history(json.at("history")),
            chessBoard(json.at("chessBoard"))
    {
    }

    void ChessGame::operator=(const ChessGame &g)
    {
        history = g.history;
        chessBoard = g.chessBoard;
    }

    std::string ChessGame::toJSON() const
    {
        ostringstream oss;
        oss << JSON_OBJECT(JSON_KEYVALUE(config) JSON_COMMA JSON_KEYVALUE(history) JSON_COMMA JSON_KEYVALUE(chessBoard));
        return oss.str();
    }
}

