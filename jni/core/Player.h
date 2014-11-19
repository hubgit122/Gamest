
#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "utilities.h"
#include "Object.h"
#include "Array.h"
#include "Stack.h"
#include "ChessGameConfig.h"
#include "Chessman.h"

namespace CIG
{
    // 注意Player是完全依赖于Chesssboard的, 因为棋子的偏移量. 所以初始化时如果没有Chesssboard的信息, 也要赋空值而不是复制.
    // 拥有的棋子也是构造后在棋盘的构造函数里边加上去的.
    class Chessboard;
    class Player: public Object
    {
        public:
            Player();
            Player(const MyJSONNode &json) : JSON_INI(index) {}
            Player(unsigned short p, string(*makeBestMove_)(string) /*= GUI::askForMove*/);
            Player(const Player &p);
            virtual ~Player();
            inline virtual string toJSON()const
            {
                ostringstream oss;
                oss << JSON_OBJECT(JSON_KEYVALUE(index));
                return oss.str();
            }

            void operator = (const Player &p);

            unsigned short index;
            string(*makeBestMove)(string);
    };
}

#endif /*__PLAYER_H_*/

