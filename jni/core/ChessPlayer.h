#include "Player.h"

#ifndef __ChessPlayer_H__
#define __ChessPlayer_H__

namespace CIG
{
    // 注意Player是完全依赖于Chesssboard的, 因为棋子的偏移量. 所以初始化时如果没有Chesssboard的信息, 也要赋空值而不是复制.
    // 拥有的棋子也是构造后在棋盘的构造函数里边加上去的.
    class Chessboard;
    class ChessPlayer : public Player
    {
        public:
            ChessPlayer(Chessboard &cb);
            ChessPlayer(const MyJSONNode &json, Chessboard &cb) : chessboard(cb), JSON_INI(ownedChessmans) {}
            ChessPlayer(unsigned short p, Chessboard &cb);
            ChessPlayer(const ChessPlayer &p, Chessboard &cb);
            virtual ~ChessPlayer();
            inline virtual string toJSON()const
            {
                ostringstream oss;
                oss << JSON_OBJECT(JSON_KEY(Player) JSON_VALUE((Player &)(*this)) JSON_COMMA JSON_KEYVALUE(ownedChessmans));
                return oss.str();
            }

            void operator = (const ChessPlayer &p);

            Array<Chessman, INI_CHESSMAN_GROUP_SIZE, 0> ownedChessmans;
            Chessboard &chessboard;
    };
}

#endif /*__ChessPlayer_H_*/

