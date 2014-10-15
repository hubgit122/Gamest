#ifndef __GAME_H__
#define __GAME_H__

#include "GameHead.h"
#include "Object.h"
#include "ChessGameConfig.h"
#include "Player.h"

namespace CIG
{
    class Game : public Object
    {
        public:
            Game(string json)
            {

            }
            virtual ~Game();

            GAME_TYPE typeId;
            string version;
            Array<Player, INI_PLAYER_ARRAY_SIZE, 0> players;
            unsigned roomNum;

            inline virtual string toJSON()const;
        private:
            Game() {};
    };
}
#endif