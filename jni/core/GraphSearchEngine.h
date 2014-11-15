
#ifndef __GRAPHSEARCHENGINE_H__
#define __GRAPHSEARCHENGINE_H__

#include "Motion.h"
#include "Stack.h"
#include <ctime>
#include "ChessBoard.h"
#include "MotionGenerator.h"
namespace CIG
{
    class GraphSearchEngine
    {
        public:
            GraphSearchEngine(const MyJSONNode &json) : JSON_INI(PLAYER_NUM), JSON_INI(limitDepth), JSON_INI(timeout) {}
            virtual ~GraphSearchEngine() {}
            inline virtual string toJSON()const
            {
                ostringstream oss;
                oss << JSON_OBJECT(JSON_KEYVALUE(PLAYER_NUM) JSON_COMMA JSON_KEYVALUE(limitDepth) JSON_COMMA JSON_KEYVALUE(timeout));
                return oss.str();
            }
            void makeBestMove(Chessboard *cb, Move &op);
            void setTimeOut(unsigned long t);
            void setLimitDepth(int d);

        private:
            int alphaBetaSearch(int alpha, int beta, int depth, Move &bestMove);
            //HashTable<Motion> historyList;
            short PLAYER_NUM;
            int limitDepth;
            int rootDepth;
            unsigned long beginTime;
            unsigned long timeout;
            Chessboard *chessboard;
            Move bestMove;
    };
}

#endif /*__GRAPHSEARCHENGINE_H_*/

