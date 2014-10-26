
#ifndef __MOTIONGENERATOR_H__
#define __MOTIONGENERATOR_H__
#include "Stack.h"
#include "ChessGameConfig.h"
#include "Chessboard.h"

namespace CIG
{
    class MotionGenerator
    {
        public:
            MotionGenerator(Chessboard &cb) : chessboard(cb), config(cb.game.config) {}
            virtual ~MotionGenerator() {};

            MoveStack moveStack;
            Chessboard &chessboard;
            ChessGameConfig &config;

            virtual void generateMoves(bool guiInput = false);
            virtual bool generateRecursively(Move &logMotionStack, OperationStack &operationStack, bool guiInput = false);
            virtual void generateMotionsForOneOperation(OperationStack &operationStack, Move &logOperationStack, Move &runningOperationStack, bool guiInput = false);

            bool testAndSave(unsigned short s, Chessman *c, PointOrVectorS dist, Move &runningOperationStack);
    };
}
#endif /*__MOTIONGENERATOR_H_*/

