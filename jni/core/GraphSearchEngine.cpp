
#include "GraphSearchEngine.h"
#include "ChessBoard.h"
#include "MotionGenerator.h"
#include <time.h>

namespace CIG
{
    //************************************
    // Method:    alphaBetaSearch
    // FullName:  CIG::GraphSearchEngine::alphaBetaSearch
    // Access:    private static
    // Returns:   int
    // Qualifier:
    // Parameter: int alpha
    // Parameter: int beta
    // Parameter: int depth
    // ��������Ķ��˰�, Ӧ����������:
    // ԭ���ǵ�ǰ��ҿ����޲�, �õ��ڱ�����Ҳ�߶��Լ����������߷�ʱ, �Լ����ܻ�õ��������Ľ��.
    // ��������С���������ͬ���ڵõ���ǰ�������������һ��֮�����ܵõ�����÷���������ֱ����ǰһ��ȡ�෴���õ���, ��Ӧ��ֱ�����¼��������ر����Ŀ���������.
    //************************************
    int GraphSearchEngine::alphaBetaSearch(int alpha, int beta, int depth)
    {
        int vl, vlBest;
        Move nowBestMove;
        Chessboard &nowBoard = *pChessboard;
        // һ��Alpha-Beta��ȫ������Ϊ���¼����׶�
        // 1. ����ˮƽ�ߣ��򷵻ؾ�������ֵ
        unsigned tmp = clock();

        if(depth == 0 || beginTime + timeout <= tmp)
        {
            return nowBoard.getEvaluation((ChessGameConfig::PLAYER_NAMES)(nowBoard.nowTurn - 1 + ((-!(long long)nowBoard.nowTurn)&ChessGameConfig::PLAYER_NUM)));
        }

        // 2. ��ʼ�����ֵ������߷�
        vlBest = -Chessboard::MATE_VALUE; // ��������֪�����Ƿ�һ���߷���û�߹�(ɱ��)
        //bestMove.clear();           // ��������֪�����Ƿ���������Beta�߷���PV�߷����Ա㱣�浽��ʷ��
        // 3. ����ȫ���߷�����������ʷ������         ���������, û���������.
        MotionGenerator mg(nowBoard);
        mg.generateMoves();
        MoveStack &runningMoveStack = mg.moveStack;

        //qsort(mvs, nGenMoves, sizeof(int), CompareHistory);       //����CompareHistory�Ķ���, �����ɴ�С����.

        // 4. ��һ����Щ�߷��������еݹ�
        for(int i = runningMoveStack.size - 1; i >= 0 ; --i)
        {
            Move &nowMove = runningMoveStack[i];
            nowBoard.onWholeMoveIntent(nowMove, true);
            vl = alphaBetaSearch(-beta, -alpha, depth - 1);
            nowBoard.undoWholeMove(nowMove, true);

            // 5. ����Alpha-Beta��С�жϺͽض�
            if(vl > vlBest)       // �ҵ����ֵ(������ȷ����Alpha��PV����Beta�߷�)
            {
                vlBest = vl;        // "vlBest"����ĿǰҪ���ص����ֵ�����ܳ���Alpha-Beta�߽�
                nowBestMove.forceCopyFrom(runningMoveStack[i]);

                if(ChessGameConfig::PLAYER_NUM == 2)
                {
                    if(vl >= beta)    // �ҵ�һ��Beta�߷�
                    {
                        break;            // Beta�ض�
                    }
                    else if(vl > alpha)    // �ҵ�һ��PV�߷�
                    {
                        alpha = vl;     // ��СAlpha-Beta�߽�
                    }
                }
            }
        }

        // 5. �����߷����������ˣ�������߷�(������Alpha�߷�)���浽��ʷ���������ֵ
        if(vlBest <= -Chessboard::WIN_VALUE)
        {
            // �����ɱ�壬�͸���ɱ�岽����������
            return nowBoard.getEvaluation((ChessGameConfig::PLAYER_NAMES)(nowBoard.nowTurn - 1 + ((-!(long long)nowBoard.nowTurn)&ChessGameConfig::PLAYER_NUM))) - nowBoard.nowRound;
        }

        if(nowBestMove.size != 0)
        {
            //// �������Alpha�߷����ͽ�����߷����浽��ʷ��
            //Search.nHistoryTable[mvBest] += nDepth * nDepth;
            if(depth == rootDepth)
            {
                // �������ڵ�ʱ��������һ������߷�(��Ϊȫ�����������ᳬ���߽�)��������߷���������
                GraphSearchEngine::bestMove.forceCopyFrom(nowBestMove);
            }
        }

        nowBoard.onMoveIntent(nowBestMove, true);
        int preBest = nowBoard.getEvaluation((ChessGameConfig::PLAYER_NAMES)(nowBoard.nowTurn - 1 + ((-!(long long)nowBoard.nowTurn)&ChessGameConfig::PLAYER_NUM)));
        nowBoard.undoMove(nowBestMove, true);
        return preBest;
    }

    void GraphSearchEngine::makeBestMove(Chessboard *chessboard, void *move)
    {
        beginTime = clock();
        bestMove.clear();
        GraphSearchEngine::pChessboard = chessboard;
        rootDepth = limitDepth;
        int vl = alphaBetaSearch(-Chessboard::MATE_VALUE, Chessboard::MATE_VALUE, limitDepth);
        (*((Move *)move)).forceCopyFrom(bestMove);
    }

    void GraphSearchEngine::setTimeOut(unsigned long t)
    {
        if(t <= 0)
        {
            timeout = -1;
        }
        else
        {
            timeout = t;
        }
    }

    void GraphSearchEngine::setLimitDepth(int d)
    {
        if(d <= 0)
        {
            d = 2;
        }

        limitDepth = d;
    }

    int GraphSearchEngine::rootDepth;
    int GraphSearchEngine::limitDepth;
    unsigned long GraphSearchEngine::beginTime;
    unsigned long GraphSearchEngine::timeout;
    Chessboard *GraphSearchEngine::pChessboard = NULL;
    CIG::Move GraphSearchEngine::bestMove;
}