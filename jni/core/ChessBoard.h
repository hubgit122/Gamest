
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
            bool loose[PLAYER_NUM];                  //������ʱ�����ж��Ƿ��ʤ, �ڷ�ֹ�Ⱥ��߳���ʤ�߷�ʱ������
            bool win[PLAYER_NUM];                        //������ʱ�����ж��Ƿ��ʤ, �ڷ�ֹ�Ⱥ��߳���ʤ�߷�ʱ������

            //static const int GRADES[3][6];

            //************************************
            // Method:    onXXIntent
            // FullName:  ChessmanBoard::onXXIntent
            // Access:    virtual public
            // Returns:   bool
            // Qualifier:
            // Parameter: PointOrVector p, Chessman& c, CIGConfig::CHESSMAN_TYPES t
            // ���Բ���, �������Ƿ�����ɹ�, ������ɹ�, �򱾴ε��ò�������̲���Ӱ��, ��������ɹ�, ��ᱣ������Ľ��.
            // Ĭ������Ϊ:
            // ��������"�������˵�����, �����Լ�������"�����ĳ���, ��������״̬, ��������ֵ, ����true;
            // ����޸Ĺ���, Ӧ�ü̳и���, ��дonXXXIntent����, �������������Լ�����������.
            // ��ȻҲ�������Լ��ĺ�������ñ���ĺ���, �ڲ������¼���Ĺ���.
            // ע��: ��Ϊʹ���˶�̬����, ���е�����ָ�������ʹ��ʱ���¼���. ԭ����: ���ҽ����õ�ָ����й��������ӵĲ���(�����Ƿ���ɾ��������)
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
            // ע���÷�: Ԥ����ĳ������һö����, �������ӵ�ָ��, ���ǻ�û����������Ϸ�з��������.
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
            // ע��, Ϊ������Ч��, ���Ҿ����������ӿ�, ���Բ����κ��ж�, ����߱����ϸ�֤�ǰ��������˳����. һ�������ڲ�����.
            // �ر�ע��undoCaptureIntent�Ĳ����Ǳ�������, onCapture�Ĳ����ǳ��ӵ�����
            // ��Ҫ�ر�ע��undoPut��Ĭ��ʵ�ֲ�û�н�����������Ļָ�. Ҳ����˵��ִ��put��unput֮��, �õ��Ľ�������಻��, �������ӵ������pick�ķ����ر�Ϊput��Ŀ�ĵ�.
            // ���Ҫʵ����������ָ��Ļ���Ҫ���Ӻܶ�ṹ, ������ֱ�ӱ���һ��ֵ���е�. ��Ϊ���ӿ��ܾ�������put, put, unput, unput�Ĺ���.
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
            virtual void refreshEvaluations();      //�����Ҫ��ÿ���������¼�������ֵ, ��ʵ�ִ˺���, �����ʵ��ĵط�����. ������������������ʽ, ����Դ˺���.
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
    Chessman *Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::operator [](PointOrVector p) const           // TO-DO �����߼������Ż�һ��, ������ô���ȽϺ�
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
    bool Chessboard<INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, PLAYER_NUM>::beyondBoardRange(PointOrVector &p)const           // ���Ա���д�Ӷ��������
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

    //����ԭ����, ����������ô��
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
        if((*this)[p] != NULL)           //beyondBoardʱ����-1(ffff), ����Ҳ�᷵��false
        {
            return false;
        }
        else /*if ((pickedChessman.size > 0) && (pickedChessman[0] == c))*/
        {
            chessmanBoard[p] = c;

            assert(c->onPutIntent(p));    //�������������, ˵���߷����������.

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


