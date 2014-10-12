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

            GameHead head;
        private:
            Game();
    };
}
#endif