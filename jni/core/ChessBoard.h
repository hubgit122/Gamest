
#ifndef __TOTALCHESSBOARD_H__
#define __TOTALCHESSBOARD_H__

#include "Motion.h"
#include "Array.h"
#include "Stack.h"
#include "ChessGameConfig.h"
#include "Chessman.h"
#include "utilities.h"
#include "Player.h"
#include "Board.h"
#include "ChessboardInterface.h"

namespace CIG
{
    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    class Chessboard : public ChessboardInterface
    {
            class Game;
        private:
            Chessboard() {};
        public:
            Chessboard(const Game &g);
            Chessboard(const Chessboard &cb);
            virtual ~Chessboard() {};
            void operator=(const Chessboard &cb);

            Game *game;
            Array<Player, INI_PLAYER_ARRAY_SIZE, 0> &players;
            Array<Motion, INT_BANNED_MOTION_SIZE, 0> currentBannedMotions;
            Array<Chessman *, INI_CHESSMAN_GROUP_SIZE, 0> pickedChessman;
            Board<Chessman *, INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2> chessmanBoard;

            unsigned nowRound;
            unsigned short nowTurn;
            int evaluations[PLAYER_NUM];
            bool loose[PLAYER_NUM];                  //在搜索时辅助判断是否获胜, 在防止先后走出获胜走法时起作用
            bool win[PLAYER_NUM];                        //在搜索时辅助判断是否获胜, 在防止先后走出获胜走法时起作用

            //static const int GRADES[3][6];

            //************************************
            // Method:    onXXIntent
            // FullName:  ChessmanBoard::onXXIntent
            // Access:    virtual public
            // Returns:   bool
            // Qualifier:
            // Parameter: PointOrVector p, Chessman& c, CIGConfig::CHESSMAN_TYPES t
            // 尝试操作, 并返回是否操作成功, 如果不成功, 则本次调用不会对棋盘产生影响, 如果操作成功, 则会保存操作的结果.
            // 默认配置为:
            // 对于满足"不动别人的棋子, 不吃自己的棋子"条件的尝试, 调整棋盘状态, 更新评估值, 返回true;
            // 如果修改规则, 应该继承该类, 重写onXXXIntent函数, 并在其中配置自己的评估规则.
            // 当然也可以在自己的函数里调用本类的函数, 在并配置新加入的规则.
            // 注意: 因为使用了动态容器, 所有的棋子指针必须在使用时重新计算. 原则是: 当且仅当得到指针后有过增加棋子的操作(无论是否又删除了棋子)
            //************************************
            virtual bool onPickIntent(PointOrVector p, bool refreshEvaluations = false);
            virtual bool onPickIntent(Chessman *c , bool refreshEvaluations = false);
            //************************************
            // Method:    onAddIntent
            // FullName:  Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::onAddIntent
            // Access:    virtual public
            // Returns:   Chessman*
            // Qualifier:
            // Parameter: PointOrVector p
            // 注意用法: 预告在某处增加一枚棋子, 返回棋子的指针, 但是还没有真正在游戏中放下这个子.
            //************************************
            virtual bool onAddIntent(PointOrVector p = PointOrVector(-1, -1), bool refreshEvaluations = false);
            virtual bool onPutIntent(Chessman *c, PointOrVector p = PointOrVector(-1, -1), bool refreshEvaluations = false);
            virtual bool onCaptureIntent(Chessman *c, PointOrVector p, bool refreshEvaluations = false);
            virtual bool onPromotionIntent(Chessman *c, CHESSMAN_TYPES t, bool refreshEvaluations = false);
            virtual bool onPromotionIntent(PointOrVector p, CHESSMAN_TYPES t, bool refreshEvaluations = false);
            virtual bool onMoveIntent(const Move &move, bool refreshEvaluations = false);
            virtual bool onWholeMoveIntent(const Move &move, bool refreshEvaluations = false);
            virtual bool onMotionIntent(const Motion &operation, bool refreshEvaluations = false);
            virtual bool canMakeWholeMove(const Move &move, bool refreshEvaluations = false);
            virtual bool onChangeTurn();

            //************************************
            // Method:    undoXX
            // FullName:  Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::undoXX
            // Access:    virtual private
            // Returns:   void
            // Qualifier:
            // Parameter: PointOrVector p
            // 注意, 为了运行效率, 并且尽量减少外界接口, 所以不做任何判断, 编程者必须严格保证是按照走棋的顺序撤销. 一定是类内部调用.
            // 特别注意undoCaptureIntent的参数是被吃棋子, onCapture的参数是吃子的棋子
            // 还要特别注意undoPut的默认实现并没有进行棋子坐标的恢复. 也就是说在执行put和unput之后, 得到的结果是其余不变, 但是棋子的坐标从pick的发生地变为put的目的地.
            // 如果要实现棋子坐标恢复的话需要增加很多结构, 并不是直接保存一个值就行的. 因为棋子可能经历类似put, put, unput, unput的过程.
            //************************************
            virtual void undoAdd(PointOrVector p, bool refreshEvaluations = false);
            virtual void undoPick(Chessman *c , PointOrVector p, bool refreshEvaluations = false);
            virtual void undoPut(Chessman *c, PointOrVector previousP, bool refreshEvaluations = false);
            virtual void undoCaptured(Chessman *c, bool refreshEvaluations = false);
            virtual void undoPromotion(Chessman *c, CHESSMAN_TYPES t, bool refreshEvaluations = false);
            virtual void undoPromotion(PointOrVector p, CHESSMAN_TYPES t, bool refreshEvaluations = false);
            virtual void undoMove(const Move &move, bool refreshEvaluations = false);
            virtual void undoWholeMove(const Move &move, bool refreshEvaluations = false);
            virtual void undoMotion(const Motion &operation, bool refreshEvaluations = false);
            virtual void undoChangeTurn();
            virtual void refreshEvaluations();      //如果需要对每个局面重新计算评估值, 请实现此函数, 并在适当的地方调用. 如果采用增量计算的形式, 请忽略此函数.
            virtual bool gameOver();

        public:
            virtual int getEvaluation(unsigned short p)const;
            virtual int getEvaluation()const;

            virtual Chessman *operator[](PointOrVector p)const;
            virtual bool beyondBoardRange(PointOrVector &p)const;

            inline virtual string toJSON()const;

            Chessboard(const JSONNode &json, const Game &g);

    };

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::Chessboard(const Game &g) : nowTurn(0), nowRound(0), game(&g), players(g.players), pickedChessman(), currentBannedMotions(), chessmanBoard()
    {
        memset(loose, 0, sizeof(loose));
        memset(win, 0, sizeof(win));
        memset(evaluations, 0, sizeof(evaluations));
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::Chessboard(const JSONNode &json, const Game &g) : nowTurn(json.at("nowTurn").as_int()), nowRound(json.at("nowRound").as_int()), game(&g), players(g.players), pickedChessman(json.at("pickedChessman")), currentBannedMotions(json.at("currentBannedMotions")), chessmanBoard(json.at("chessmanBoard"))
    {
        parseBoolArray(json, "loose", loose);
        parseBoolArray(json, "win", win);
        parseIntArray(json, "loose", evaluations);
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::Chessboard(const Chessboard &cb)
        : nowTurn(cb.nowTurn), nowRound(cb.nowRound), game(cb.game), players(cb.players), chessmanBoard(cb.chessmanBoard),
          pickedChessman(), currentBannedMotions()
    {
        currentBannedMotions.forceCopyFrom(cb.currentBannedMotions);

        for(int i = 0; i < cb.pickedChessman.size; ++i)
        {
            Chessman *c = cb.pickedChessman[i];
            pickedChessman.add(&game->players[c->chessmanIndex.player].ownedChessmans[c->chessmanIndex.index]);
        }

        for(short i = 0; i < (1 << INI_BOARD_HEIGHT_LOG2); ++i)
        {
            for(short j = 0; j < (1 << INI_BOARD_WIDTH_LOG2); ++j)
            {
                Chessman *c = cb.chessmanBoard[PointOrVector(j, i)];
                chessmanBoard[PointOrVector(j, i)] = c ? &game->players[c->chessmanIndex.player].ownedChessmans[c->chessmanIndex.index] : 0;
            }
        }

        memcpy(loose, cb.loose, sizeof(loose));
        memcpy(win, cb.win, sizeof(win));
        memcpy(evaluations, cb.evaluations, sizeof(evaluations));
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    void Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::operator=(const Chessboard &cb)
    {
        assert(game == cb.game, "board copy between different games");

        nowTurn = cb.nowTurn;
        nowRound = cb.nowRound;
        currentBannedMotions.forceCopyFrom(cb.currentBannedMotions);
        pickedChessman.forceCopyFrom(cb.pickedChessman);
        chessmanBoard = cb.chessmanBoard;
        memcpy(win, cb.win, sizeof(win));
        memcpy(loose, cb.loose, sizeof(loose));
        memcpy(evaluations, cb.evaluations, sizeof(evaluations));
    }

    //************************************
    // Method:    operator[]
    // FullName:  Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::operator[]
    // Access:    public
    // Returns:   Chessman*
    // Qualifier: const
    // Parameter: PointOrVector p
    //************************************
    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    Chessman *Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::operator [](PointOrVector p) const           // TO-DO 这里逻辑可以优化一下, 看看怎么检测比较好
    {
        if(beyondBoardRange(p))
        {
            return (Chessman *)(void *) - 1;
        }

        return chessmanBoard[(p[1] << INI_BOARD_WIDTH_LOG2) + p[0]];
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    int Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::getEvaluation(unsigned short p) const
    {
        int result = 0;

        for(int i = 0; i < PLAYER_NUM; ++i)
        {
            if(i != p)
            {
                result -= evaluations[i];
            }
        }

        result = evaluations[p] + (result) / (PLAYER_NUM - 1);

        return result;
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    int Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::getEvaluation() const
    {
        return getEvaluation(nowTurn);
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    bool Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::beyondBoardRange(PointOrVector &p)const           // 可以被改写从而提高性能
    {
        static const unsigned mask = (~(((unsigned short)1 << INI_BOARD_WIDTH_LOG2) - 1) << sizeof(unsigned short) * 8) | (unsigned short) - 1 & (~(((unsigned short)1 << INI_BOARD_HEIGHT_LOG2) - 1));

        if(mask&*((unsigned *)p.x))
        {
            return true;
        }
        else if(!boardRange[p])
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    bool Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::onAddIntent(PointOrVector p /*= PointOrVector(-1,-1)*/, bool refreshEvaluations /*= false*/)
    {
        Chessman *c = players[nowTurn].ownedChessmans.add(Chessman(CHESS, p, nowTurn, players[nowTurn].ownedChessmans.size, OFF_BOARD, ALL));
        return onPutIntent(c, p, refreshEvaluations);
    }

    //穿脱原理下, 操作就是这么简单
    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    void Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::undoAdd(PointOrVector p, bool refreshEvaluations)
    {
        undoPut(&chessmanBoard[p], PointOrVector(), refreshEvaluations);
        //pickedChessman.deleteAtNoReturn(pickedChessman.size - 1);
        players[nowTurn].ownedChessmans.popNoReturn();
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    bool Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::onPutIntent(Chessman *c, PointOrVector p, bool refreshEvaluations)
    {
        if((*this)[p] != NULL)           //beyondBoard时返回-1(ffff), 所以也会返回false
        {
            return false;
        }
        else /*if ((pickedChessman.size > 0) && (pickedChessman[0] == c))*/
        {
            chessmanBoard[p] = c;

            assert(c->onPutIntent(p));    //如果不满足条件, 说明走法设计有问题.

            //pickedChessman.deleteAtNoReturn(0);
            return true;
        }

        return false;
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    void Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::undoPut(Chessman *c, PointOrVector previousP, bool refreshEvaluations /*= false*/)
    {
        chessmanBoard[c->coordinate] = NULL;
        c->undoPut();
        //pickedChessman.add(c);

        c->coordinate = previousP;
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    bool Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::onChangeTurn()
    {
        game->nowTurn = (unsigned short)((game->nowTurn + 1) % (PLAYER_NUM));
        game->nowRound++;
        return true;
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    void Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::undoChangeTurn()
    {
        game->nowTurn = (unsigned short)((game->nowTurn - 1 + PLAYER_NUM) % (PLAYER_NUM));
        game->nowRound--;
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    bool Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::onMoveIntent(const Move &move, bool refreshEvaluations)
    {
        bool result = true;

        for(int i = 0; i < move.size; i++)
        {
            result &= onMotionIntent(move[i], refreshEvaluations);
        }

        result &= (this->pickedChessman.size == 0);
        return result;
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    bool Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::onMotionIntent(const Motion &op, bool refreshEvaluations)
    {
        switch(op.operation)
        {
            case BEGIN:
                return true;

            case ADD:
                return onAddIntent(op.distination, refreshEvaluations);

            case PICK:
                return onPickIntent(&(this->players[nowTurn].ownedChessmans[op.chessmanIndex.index]), refreshEvaluations);

            case PUT:
                return onPutIntent(&(this->players[nowTurn].ownedChessmans[op.chessmanIndex.index]), op.distination, refreshEvaluations);

            case CAPTURE:
                return onCaptureIntent(pickedChessman[0], op.distination, refreshEvaluations);

            case PROMOTION:
                return false;

            default:
                return false;
        }
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    bool Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::canMakeWholeMove(const Move &move, bool refreshEvaluations)
    {
        Chessboard cb(*this);
        bool result = cb.onWholeMoveIntent(move, refreshEvaluations);
        return result;
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    void Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::undoMove(const Move &move, bool refreshEvaluations)
    {
        for(int i = move.size - 1; i >= 0; --i)
        {
            undoMotion(move[i], refreshEvaluations);
        }
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    void Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::undoMotion(const Motion &operation, bool refreshEvaluations)
    {
        switch(operation.operation)
        {
            case ADD:
                undoAdd(operation.distination, refreshEvaluations);
                break;

            case PICK:
                undoPick(&(this->players[operation.chessmanIndex.player].ownedChessmans[operation.chessmanIndex.index]), operation.distination, refreshEvaluations);
                break;

            case PUT:
                undoPut(&(this->players[operation.chessmanIndex.player].ownedChessmans[operation.chessmanIndex.index]), operation.savedCoodinate, refreshEvaluations);
                break;

            case CAPTURE:
                undoCaptured(&(this->players[operation.chessmanIndex.player].ownedChessmans[operation.chessmanIndex.index]), refreshEvaluations);
                break;

            default:
                break;
        }
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    bool Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::onWholeMoveIntent(const Move &move, bool refreshEvaluations)
    {
        return onMoveIntent(move, refreshEvaluations) && onChangeTurn();
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    void Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::undoWholeMove(const Move &move, bool refreshEvaluations)
    {
        undoChangeTurn();
        undoMove(move, refreshEvaluations);
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    bool Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::onPickIntent(PointOrVector p, bool refreshEvaluations)
    {
        return onPickIntent((*this)[p], refreshEvaluations);
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    void Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::undoPick(Chessman *c, PointOrVector p, bool refreshEvaluations)
    {
        if(refreshEvaluations)
        {
            // TO-DO

        }

        pickedChessman.deleteAtNoReturn(pickedChessman.size - 1);
        chessmanBoard[p] = c;
        c->coordinate = p;
        c->undoPick();
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    void Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::undoPromotion(Chessman *c, CHESSMAN_TYPES t, bool refreshEvaluations)
    {
        //TODO
    }
    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    void Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::undoPromotion(PointOrVector p, CHESSMAN_TYPES t, bool refreshEvaluations)
    {
        //TODO
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    bool Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::onCaptureIntent(Chessman *c, PointOrVector p, bool refreshEvaluations)
    {
        if(beyondBoardRange(p))
        {
            return false;
        }
        else
        {
            Chessman *testC = (*this)[p];

            if((testC == NULL) || (testC->chessmanIndex.player == nowTurn))
            {
                return false;
            }
            else if(pickedChessman[0] == c)
            {
                if(testC->onCapturedIntent())
                {
                    c->onCaptureIntent(testC);
                    chessmanBoard[p] = 0;
                    //loose[testC->chessmanIndex.player] = (testC->chessmanType == CIGRuleConfig::KING);

                    if(refreshEvaluations)
                    {
                        //evaluations[testC->chessmanIndex.player] -= CIGRuleConfig::EVALUATIONS[testC->chessmanIndex.player][testC->chessmanType][p.x[1]][p.x[0]];
                    }

                    return true;
                }
                else
                {
                    return false;
                }
            }
        }

        return false;
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    bool Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::onPromotionIntent(Chessman *c, CHESSMAN_TYPES t, bool refreshEvaluations)
    {
        return false;
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    bool Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::onPickIntent(Chessman *c, bool refreshEvaluations)
    {
        if((c->chessmanIndex.player == nowTurn) && (pickedChessman.size == 0) && (c->onPickIntent()))
        {
            PointOrVector &p = c->coordinate;
            pickedChessman.add(c);
            chessmanBoard[c->coordinate] = NULL;

            if(refreshEvaluations)
            {
                //evaluations[nowTurn] -= CIGRuleConfig::EVALUATIONS[nowTurn][c->chessmanType][p.x[1]][p.x[0]];
            }

            return true;
        }

        return false;
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    bool Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::onPromotionIntent(PointOrVector p, CHESSMAN_TYPES t, bool refreshEvaluations)
    {
        return onPromotionIntent((*this)[p], t, refreshEvaluations);
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    void Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::undoCaptured(Chessman *c, bool refreshEvaluations)
    {
        c->undoCaptured();
        PointOrVector p(c->coordinate);
        chessmanBoard[p] = c;

        //if (c->chessmanType == CIGRuleConfig::KING)
        //{
        //  loose[c->chessmanIndex.player] = false;
        //}

        if(refreshEvaluations)
        {
            // TO-DO
        }
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    void Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::refreshEvaluations()
    {
        // TO-DO
    }

    template <unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2, unsigned short PLAYER_NUM>
    bool Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::gameOver()
    {
        // TO-DO
        for(int i = 0; i < PLAYER_NUM; ++i)
        {
            if(loose[i])
            {
                return true;
            }
        }

        return false;
    }

}

#endif /*__TOTALCHESSBOARD_H_*/


