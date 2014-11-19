#include "Player.h"

#ifndef __ChessPlayer_H__
#define __ChessPlayer_H__

namespace CIG
{
    // ע��Player����ȫ������Chesssboard��, ��Ϊ���ӵ�ƫ����. ���Գ�ʼ��ʱ���û��Chesssboard����Ϣ, ҲҪ����ֵ�����Ǹ���.
    // ӵ�е�����Ҳ�ǹ���������̵Ĺ��캯����߼���ȥ��.
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

