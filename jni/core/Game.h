#ifndef __GAME_H__
#define __GAME_H__

#include "Object.h"
#include "ChessGameConfig.h"
#include "Player.h"
#include "Chessboard.h"

namespace CIG
{
    class Game : public Object
    {
        public:
            Game(const MyJSONNode &json) : JSON_INI(typeId), JSON_INI(version), JSON_INI(players), JSON_INI(roomNum), JSON_INI(config)
            {

            }
            virtual ~Game();

            GAME_TYPE typeId;
            string version;
            Array<Player, INI_PLAYER_ARRAY_SIZE, 0> players;
            unsigned roomNum;
            ChessGameConfig config;
            Chessboard chessboard;

            inline virtual string toJSON()const
            {
                ostringstream oss;
                oss << JSON_OBJECT(JSON_KEYVALUE(typeId) JSON_COMMA JSON_KEYVALUE(version) JSON_COMMA JSON_KEYVALUE(players) JSON_COMMA JSON_KEYVALUE(roomNum) JSON_COMMA JSON_KEYVALUE(config));
                return oss.str();
            }
    };
}
#endif