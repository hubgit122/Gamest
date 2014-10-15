
#ifndef __MOTIONGENERATOR_H__
#define __MOTIONGENERATOR_H__
#include "Stack.h"
#include "ChessGameConfig.h"
#include "Chessboard.h"

namespace CIG
{
    class MotionGenerator
    {
        private:
            MotionGenerator();
        public:
            MotionGenerator(ChessboardInterface &cb);
            virtual ~MotionGenerator() {};
            //void operator=(const MotionGenerator&mg);

            MoveStack moveStack;
            ChessboardInterface &chessboard;             //每个ChesssBoard有一个MotionGenerator实例.
            //virtual OperationStack* nextMove();
            virtual void generateMoves(bool guiInput = false);
            virtual bool generateRecursively(Move &logMotionStack, OperationStack &operationStack, bool guiInput = false);
            virtual void generateMotionsForOneOperation(OperationStack &operationStack, Move &logOperationStack, Move &runningOperationStack, bool guiInput = false);

            bool testAndSave(OPERATIONS s, Chessman *c, PointOrVector dist, Move &runningOperationStack);
    };
}
#endif /*__MOTIONGENERATOR_H_*/

