
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
    // ע��Player����ȫ������Chesssboard��, ��Ϊ���ӵ�ƫ����. ���Գ�ʼ��ʱ���û��Chesssboard����Ϣ, ҲҪ����ֵ�����Ǹ���.
    // ӵ�е�����Ҳ�ǹ���������̵Ĺ��캯����߼���ȥ��.
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

