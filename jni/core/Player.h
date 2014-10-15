
#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "utilities.h"
#include "Object.h"
#include "Array.h"
#include "Stack.h"
#include "ChessGameConfig.h"

namespace CIG
{
    class ChessboardInterface;
    // ע��Player����ȫ������Chesssboard��, ��Ϊ���ӵ�ƫ����. ���Գ�ʼ��ʱ���û��Chesssboard����Ϣ, ҲҪ����ֵ�����Ǹ���.
    // ӵ�е�����Ҳ�ǹ���������̵Ĺ��캯����߼���ȥ��.
    class Player: public Object
    {
        public:
            Player();
            Player(unsigned short p, void(*makeBestMove_)(ChessboardInterface *cb, void *) /*= GUI::askForMove*/, ChessboardInterface *cb = NULL);
            Player(const Player &p, ChessboardInterface *cb = NULL);
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
            ChessboardInterface *chessboard;

            void (*makeBestMove)(ChessboardInterface *cb, void *op);
    };
}

#endif /*__PLAYER_H_*/

