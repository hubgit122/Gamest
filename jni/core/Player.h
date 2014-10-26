
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
    class Chessboard;
    // 注意Player是完全依赖于Chesssboard的, 因为棋子的偏移量. 所以初始化时如果没有Chesssboard的信息, 也要赋空值而不是复制.
    // 拥有的棋子也是构造后在棋盘的构造函数里边加上去的.
    class Player: public Object
    {
        public:
            Player();
            Player(unsigned short p, void(*makeBestMove_)(Chessboard *cb, void *) /*= GUI::askForMove*/, Chessboard *cb = NULL);
            Player(const Player &p, Chessboard *cb = NULL);
            virtual ~Player();
            inline virtual string toJSON()const
            {
                ostringstream oss;
                oss << JSON_OBJECT(JSON_KEYVALUE(index) JSON_COMMA JSON_KEYVALUE(ownedChessmans));
                return oss.str();
            }

            void operator = (const Player &p);

            unsigned short index;
            Stack<Chessman, INI_CHESSMAN_GROUP_SIZE, 0> ownedChessmans;
            Chessboard *chessboard;

            void (*makeBestMove)(Chessboard *cb, void *op);
    };
}

#endif /*__PLAYER_H_*/

