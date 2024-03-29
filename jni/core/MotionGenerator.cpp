#include "Array.h"
#include "Player.h"
#include "Chessman.h"
#include "ChessmanIndex.h"
#include "MotionGenerator.h"
#include "ChessGame.h"
#include "Chessboard.h"
namespace CIG
{
    void MotionGenerator::generateMoves(bool guiInput)
    {
        if(chessboard.win[chessboard.nowTurn] || chessboard.loose[chessboard.nowTurn])
        {
            return;                             //如果已经输了或赢了, 就不产生走法, 走法栈是空的.
        }

        bool result;

        do
        {
            Move logMotionStack;
            OperationStack operationStack;
            operationStack.push(BEGIN);
            logMotionStack.push(Motion(ChessmanIndex(chessboard.nowTurn, -1), BEGIN, PointOrVectorS(-1, -1)));
            result = generateRecursively(logMotionStack, operationStack, guiInput);
            //operationStack.popNoReturn();
        }
        while(!result);
    }

    MotionGenerator::MotionGenerator(Chessboard &cb) : chessboard(cb), config(cb.game.config)
    {

    }

    // 过程比较复杂:
    // 对于运行中搜索的一步, 若全局状态栈非空, 取定栈顶为当前状态,
    // 以记录棋盘栈顶为当前环境, 生成与状态栈顶相应的可能的走法和对应的结果棋盘, 入各自运行栈.
    // 若当前走法运行栈非空, 取定栈顶的元素入记录栈, 开始下一阶段的搜索.          ///这里适合用递归函数做, 借助程序运行栈, 而不是循环.
    // 若当前棋盘和走法运行栈空, 说明该状态没有可用走法, 状态栈弹栈, 重新取定栈顶为当前状态.
    // 若全局状态栈顶为end, 临时栈入全局栈, 状态栈弹栈, 重新取定栈顶为当前状态.
    // 初始条件配置: operationStack.push(CIGRuleConfig::BEGIN);
    bool MotionGenerator::generateRecursively(Move &logMotionStack, OperationStack &operationStack, bool guiInput /*= false*/)
    {
        ////根据输入选择当前的操作
        //if(guiInput)
        //{
        //    if(config.operationGraph[logMotionStack.top().operation][0] == END && config.operationGraph[logMotionStack.top().operation][1] == NOMORE)
        //    {
        //        if(chessboard.onChangeTurn())
        //        {
        //            chessboard.undoChangeTurn();
        //            moveStack.push(logMotionStack);
        //            return true;
        //        }
        //        else
        //        {
        //            return false;
        //        }
        //    }

        //    bool result;
        //    PointOrVectorS dist;
        //    msg;

        //    if(logMotionStack.top().operation != BEGIN)
        //    {
        //        GUI::drawBoard(&chessboard, &logMotionStack);
        //    }

        //    GUI::getInput(dist, msg);

        //    switch(msg)
        //    {
        //        case CIG_END:
        //            for(int i = 0; (config.operationGraph[logMotionStack.top().operation][i] != NOMORE) && (i < END + 1); ++i)
        //            {
        //                if(config.operationGraph[logMotionStack.top().operation][i] == END)
        //                {
        //                    if(chessboard.onChangeTurn())
        //                    {
        //                        chessboard.undoChangeTurn();
        //                        moveStack.push(logMotionStack);
        //                        return true;
        //                    }
        //                    else
        //                    {
        //                        return false;
        //                    }
        //                }
        //            }

        //            return false;
        //            break;

        //        case CIG_UNDO:
        //            return false;
        //            break;

        //        case CIG_POINT:
        //        {
        //            Move runningMotionStack;
        //            unsigned  op = operationStack.top();
        //            int i = 0;

        //            for(; config.operationGraph[op][i] != NOMORE; ++i)
        //            {
        //                operationStack.push(config.operationGraph[op][i]);

        //                if(config.operationGraph[op][i] == END && logMotionStack.top().distination == dist)
        //                {
        //                    if(chessboard.onChangeTurn())
        //                    {
        //                        chessboard.undoChangeTurn();
        //                        moveStack.push(logMotionStack);
        //                        return true;
        //                    }
        //                    else
        //                    {
        //                        return false;
        //                    }
        //                }
        //            }

        //            Motion tmpMotion;
        //            //在tempMotionStack里生成所有动作, 如果有END, 保存在moveStack里
        //            Move tempMotionStack = runningMotionStack;
        //            OperationStack tempOperationStack = operationStack;
        //            int j = i;

        //            for(; j > 0; --j)
        //            {
        //                generateMotionsForOneOperation(tempOperationStack, logMotionStack, tempMotionStack, guiInput);          //在runnningMotionStack和MoveStack中保存了下一步所有的可能结果.
        //                tempOperationStack.popNoReturn();
        //            }

        //            int count = 0;

        //            for(int j = 0; j < tempMotionStack.size; ++j)
        //            {
        //                if(tempMotionStack[j].distination == dist)
        //                {
        //                    tmpMotion = tempMotionStack[j];
        //                    count++;
        //                }
        //            }

        //            if(count == 0)
        //            {
        //                result = false;
        //                break;
        //            }
        //            else if(count > 1)
        //            {
        //                ;//让玩家自己选择
        //                //tmpMotion =
        //            }

        //            result = false;

        //            for(; i > 0; --i)
        //            {
        //                generateMotionsForOneOperation(operationStack, logMotionStack, runningMotionStack, guiInput);

        //                while(runningMotionStack.size > 0)
        //                {
        //                    if(runningMotionStack.top() == tmpMotion)
        //                    {
        //                        Motion &nowOperation = tmpMotion;
        //                        logMotionStack.push(nowOperation);
        //                        chessboard.onMotionIntent(nowOperation);
        //                        result = generateRecursively(logMotionStack, operationStack, guiInput);
        //                        chessboard.undoMotion(nowOperation);
        //                        logMotionStack.popNoReturn();
        //                    }

        //                    runningMotionStack.popNoReturn();
        //                }

        //                operationStack.popNoReturn();
        //            }
        //        }
        //        break;

        //        default:
        //            break;
        //    }

        //    return result;
        //}
        //else
        //{
        //    Move runningMotionStack;
        //    unsigned  op = operationStack.top();
        //    int i = 0;

        //    for(; config.operationGraph[op][i] != NOMORE; ++i)
        //    {
        //        operationStack.push(config.operationGraph[op][i]);
        //    }

        //    for(; i > 0; --i)
        //    {
        //        generateMotionsForOneOperation(operationStack, logMotionStack, runningMotionStack);

        //        while(runningMotionStack.size > 0)
        //        {
        //            Motion &nowOperation = runningMotionStack.top();
        //            logMotionStack.push(nowOperation);
        //            chessboard.onMotionIntent(nowOperation);
        //            generateRecursively(logMotionStack, operationStack, guiInput);
        //            chessboard.undoMotion(nowOperation);
        //            logMotionStack.popNoReturn();
        //            runningMotionStack.popNoReturn();
        //        }

        //        operationStack.popNoReturn();
        //    }

        //    return true;
        //}
    }

    void MotionGenerator::generateMotionsForOneOperation(OperationStack &operationStack, Move &logMotionStack, Move &runningMotionStack, bool guiInput /*= false */)
    {
        unsigned  s = operationStack.top();

        switch(s)
        {
            case BEGIN:
                break;

            case ADD:
                for(int i = 0; i < (1 << config.INI_BOARD_WIDTH_LOG2); ++i)
                {
                    for(int j = 0; j < (1 << config.INI_BOARD_HEIGHT_LOG2); ++j)
                    {
                        PointOrVectorS dist = PointOrVectorS(i, j);

                        if(chessboard[dist] || !config.boardRange[dist])
                        {
                            continue;
                        }

                        testAndSave(s, NULL, dist, runningMotionStack);
                    }
                }

                break;

            case PICK:
            {
                const Stack<Chessman, INI_CHESSMAN_GROUP_SIZE, 0> &cg = chessboard.players[chessboard.nowTurn].ownedChessmans;

                if(logMotionStack.size <= 1)
                {
                    for(unsigned i = 0; i < cg.size; ++i)
                    {
                        Chessman *c = const_cast<Chessman *>(&(cg.at(i)));
                        testAndSave(s, c, c->coordinate, runningMotionStack);
                    }
                }
                else                //除了跳棋, 都只可能满足上边的分支.
                {
                    Chessman *c = const_cast<Chessman *>(&(cg.at(logMotionStack.top().chessmanIndex.index)));
                    testAndSave(s, c, c->coordinate, runningMotionStack);
                }
            }
            break;

            case CAPTURE:
            case PUT:
            {
                Chessman *c = chessboard.pickedChessman[-1];

                if(logMotionStack.top().operation == CAPTURE)
                {
                    testAndSave(s, c, logMotionStack.top().distination, runningMotionStack);
                    break;
                }

                switch(c->chessmanType)
                {
                    case MONO_CHESS:
                        testAndSave(s, chessboard.pickedChessman[-1], logMotionStack.top().distination, runningMotionStack);
                }
            }
            break;

            case END:
                if(!guiInput)
                {
                    if(chessboard.onChangeTurn())
                    {
                        chessboard.undoChangeTurn();
                        moveStack.push(logMotionStack);
                    }
                }

                break;

            default:
                break;
        }
    }

    bool MotionGenerator::testAndSave(unsigned short s, Chessman *c, PointOrVectorS dist, Move &runningMotionStack)
    {
        switch(s)
        {
            case BEGIN:
                break;

            case ADD:
            {
                if(chessboard.onAddIntent(dist))
                {
                    chessboard.undoAdd(dist);
                    Motion tmpMotion(ChessmanIndex(), ADD, dist);
                    runningMotionStack.push(tmpMotion);
                    return true;
                }
            }
            break;

            case PICK:
            {
                if(chessboard.onPickIntent(c))
                {
                    chessboard.undoPick(c, c->coordinate);
                    Motion tmpMotion(c->chessmanIndex, PICK, c->coordinate);
                    runningMotionStack.push(tmpMotion);
                }
            }
            break;

            case PUT:
            {
                PointOrVectorS preP(c->coordinate);

                if(chessboard.onPutIntent(c, dist))
                {
                    chessboard.undoPut(c, preP);
                    Motion tmpMotion(c->chessmanIndex, s, dist, preP);
                    runningMotionStack.push(tmpMotion);
                    return true;
                }
            }
            break;

            case CAPTURE:
            {
                Chessman *temp = chessboard[dist];

                if(chessboard.onCaptureIntent(c, dist))
                {
                    chessboard.undoCaptured(temp);
                    Motion tmpMotion(temp->chessmanIndex, s, dist);
                    runningMotionStack.push(tmpMotion);
                    return true;
                }
            }
            break;

            case PROMOTION:
                break;

            case DECOVER:
                break;

            case END:
                break;

            default:
                break;
        }

        return false;
    }


}