
#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "utilities.h"
#include "Object.h"
#include "Array.h"
#include "Stack.h"
#include "GUI.h"
#include "ChessGameConfig.h"

namespace CIG
{
    class Chessboard;
    // ע��Player����ȫ������Chesssboard��, ��Ϊ���ӵ�ƫ����. ���Գ�ʼ��ʱ���û��Chesssboard����Ϣ, ҲҪ����ֵ�����Ǹ���.
    // ӵ�е�����Ҳ�ǹ���������̵Ĺ��캯����߼���ȥ��.
    class Player: public Object
    {
        public:
            Player();
            Player(PLAYER_NAMES p, void (*makeBestMove_)(Chessboard *cb, void *) = GUI::askForMove , Chessboard *cb = NULL);
            Player(const Player &p, Chessboard *cb = NULL);
            virtual ~Player();

            void operator = (const Player &p);

            PLAYER_NAMES NAME;
            Stack<Chessman, ChessGameConfig::INI_CHESSMAN_GROUP_SIZE, 0> ownedChessmans;
            Chessboard *chessboard;

            void (*makeBestMove)(Chessboard *cb, void *op);
    };
}

#endif /*__PLAYER_H_*/

