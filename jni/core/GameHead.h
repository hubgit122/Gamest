
#ifndef __GAMEHEAD_H__
#define __GAMEHEAD_H__

#include "Object.h"
#include "ChessGameConfig.h"
#include "Player.h"

namespace CIG
{
    class GameHead : public Object
    {
        public:

            GameHead()
            {
            }

            inline virtual string toJSON()const
            {
                ostringstream oss;
                oss << JSON_OBJECT(JSON_KEYVALUE(typeId) JSON_COMMA JSON_KEYVALUE(roomNum) JSON_COMMA JSON_KEYVALUE(round) JSON_COMMA JSON_KEYVALUE(nowTurn) JSON_COMMA JSON_KEYVALUE(version));
                return oss.str();
            }
    };
}

#endif /*__GAMEHEAD_H__*/