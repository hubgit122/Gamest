
#ifndef __GRAPHSEARCHENGINE_H__
#define __GRAPHSEARCHENGINE_H__

#include "Motion.h"
#include "Stack.h"
#include <ctime>
namespace CIG
{
    template <unsigned short PLAYER_NUM>
    class GraphSearchEngine
    {
        public:
            static void makeBestMove(ChessboardInterface *cb, void *op);
            static void setTimeOut(unsigned long t);
            static void setLimitDepth(int d);

        private:
            static int alphaBetaSearch(int alpha, int beta, int depth);
            //HashTable<Motion> historyList;
            static int limitDepth;
            static int rootDepth;
            static unsigned long beginTime;
            static unsigned long timeout;
            static ChessboardInterface *chessboard;
            static Move bestMove;
    };

    //************************************
    // Method:    alphaBetaSearch
    // FullName:  CIG::GraphSearchEngine<PLAYER_NUM>::alphaBetaSearch
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
    template <unsigned short PLAYER_NUM>
    int GraphSearchEngine<PLAYER_NUM>::alphaBetaSearch(int alpha, int beta, int depth)
    {
        int vl, vlBest;
        Move nowBestMove;
        ChessboardInterface &nowBoard = *chessboard;
        // һ��Alpha-Beta��ȫ������Ϊ���¼����׶�
        // 1. ����ˮƽ�ߣ��򷵻ؾ�������ֵ
        unsigned tmp = clock();

        if(depth == 0 || beginTime + timeout <= tmp)
        {
            return nowBoard.getEvaluation((unsigned short)(nowBoard.nowTurn - 1 + ((-!(long long)nowBoard.nowTurn)&PLAYER_NUM)));
        }

        // 2. ��ʼ�����ֵ������߷�
        vlBest = -ChessboardInterface::MATE_VALUE; // ��������֪�����Ƿ�һ���߷���û�߹�(ɱ��)
        //bestMove.clear();           // ��������֪�����Ƿ���������Beta�߷���PV�߷����Ա㱣�浽��ʷ��
        // 3. ����ȫ���߷�����������ʷ������         ���������, û���������.
        MotionGenerator mg(nowBoard);
        mg.generateMoves();
        MoveStack &runningMoveStack = mg.moveStack;

        //qsort(mvs, nGenMoves, sizeof(int), CompareHistory);       //����CompareHistory�Ķ���, �����ɴ�С����.

        // 4. ��һ����Щ�߷��������еݹ�
        for(int i = runningMoveStack.size - 1; i >= 0; --i)
        {
            Move &nowMove = runningMoveStack[i];
            nowBoard.onWholeMoveIntent(nowMove, true);
            vl = alphaBetaSearch(-beta, -alpha, depth - 1);
            nowBoard.undoWholeMove(nowMove, true);

            // 5. ����Alpha-Beta��С�жϺͽض�
            if(vl > vlBest)        // �ҵ����ֵ(������ȷ����Alpha��PV����Beta�߷�)
            {
                vlBest = vl;        // "vlBest"����ĿǰҪ���ص����ֵ�����ܳ���Alpha-Beta�߽�
                nowBestMove.forceCopyFrom(runningMoveStack[i]);

                if(PLAYER_NUM == 2)
                {
                    if(vl >= beta)     // �ҵ�һ��Beta�߷�
                    {
                        break;            // Beta�ض�
                    }
                    else if(vl > alpha)     // �ҵ�һ��PV�߷�
                    {
                        alpha = vl;     // ��СAlpha-Beta�߽�
                    }
                }
            }
        }

        // 5. �����߷����������ˣ�������߷�(������Alpha�߷�)���浽��ʷ���������ֵ
        if(vlBest <= -ChessboardInterface::WIN_VALUE)
        {
            // �����ɱ�壬�͸���ɱ�岽����������
            return nowBoard.getEvaluation((unsigned short)(nowBoard.nowTurn - 1 + ((-!(long long)nowBoard.nowTurn)&PLAYER_NUM))) - nowBoard.nowRound;
        }

        if(nowBestMove.size != 0)
        {
            //// �������Alpha�߷����ͽ�����߷����浽��ʷ��
            //Search.nHistoryTable[mvBest] += nDepth * nDepth;
            if(depth == rootDepth)
            {
                // �������ڵ�ʱ��������һ������߷�(��Ϊȫ�����������ᳬ���߽�)��������߷���������
                GraphSearchEngine<PLAYER_NUM>::bestMove.forceCopyFrom(nowBestMove);
            }
        }

        nowBoard.onMoveIntent(nowBestMove, true);
        int preBest = nowBoard.getEvaluation((unsigned short)(nowBoard.nowTurn - 1 + ((-!(long long)nowBoard.nowTurn)&PLAYER_NUM)));
        nowBoard.undoMove(nowBestMove, true);
        return preBest;
    }

    template <unsigned short PLAYER_NUM>
    void GraphSearchEngine<PLAYER_NUM>::makeBestMove(ChessboardInterface *chessboard, void *move)
    {
        beginTime = clock();
        bestMove.clear();
        GraphSearchEngine<PLAYER_NUM>::chessboard = chessboard;
        rootDepth = limitDepth;
        int vl = alphaBetaSearch(-ChessboardInterface::MATE_VALUE, ChessboardInterface::MATE_VALUE, limitDepth);
        (*((Move *)move)).forceCopyFrom(bestMove);
    }

    template <unsigned short PLAYER_NUM>
    void GraphSearchEngine<PLAYER_NUM>::setTimeOut(unsigned long t)
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

    template <unsigned short PLAYER_NUM>
    void GraphSearchEngine<PLAYER_NUM>::setLimitDepth(int d)
    {
        if(d <= 0)
        {
            d = 2;
        }

        limitDepth = d;
    }

    template <unsigned short PLAYER_NUM>
    int GraphSearchEngine<PLAYER_NUM>::rootDepth;
    template <unsigned short PLAYER_NUM>
    int GraphSearchEngine<PLAYER_NUM>::limitDepth;
    template <unsigned short PLAYER_NUM>
    unsigned long GraphSearchEngine<PLAYER_NUM>::beginTime;
    template <unsigned short PLAYER_NUM>
    unsigned long GraphSearchEngine<PLAYER_NUM>::timeout;
    template <unsigned short PLAYER_NUM>
    ChessboardInterface *GraphSearchEngine<PLAYER_NUM>::chessboard = NULL;
    template <unsigned short PLAYER_NUM>
    CIG::Move GraphSearchEngine<PLAYER_NUM>::bestMove;
}

#endif /*__GRAPHSEARCHENGINE_H_*/

