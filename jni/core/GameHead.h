
#ifndef __GAMEHEAD_H__
#define __GAMEHEAD_H__

#include "Object.h"
#include "ChessGameConfig.h"

namespace CIG
{
    class GameHead : public Object
    {
        public:
            GAME_TYPE typeId;
            string version;
            Player players[PLAYER_NUM];
            unsigned roomNum;
            unsigned round;
            PLAYER_NAMES nowTurn;

            GameHead()
            {
            }

            friend ostringstream &operator << (ostringstream &oss, const GameHead &o)
            {
                oss << "{" << "typeId:" << o.typeId << ",roomNum:" << o.roomNum << ",round:" << o.round << ",nowTurn:" << o.nowTurn << ",version:" << version << "}";

                return oss;
            }

            friend ostream &operator << (ostream &os, const GameHead &o)
            {
                ostringstream oss;
                oss << o;
                os << oss.str();
                return os;
            }
    };
}

#endif /*__GAMEHEAD_H__*/