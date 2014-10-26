#include "Chessboard.h"
#include "chessgame.h"

namespace CIG
{
    Chessboard::Chessboard(const ChessGame &g)
        : nowTurn(0), nowRound(0), game(g), players(g.players), pickedChessman(), currentBannedMotions(), chessmanBoard(INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2)
    {
        for(int i = 0; i < players.size; ++i)
        {
            loose.push_back(0);
            win.push_back(0);
            evaluations.push_back(0);
        }
    }

    Chessboard::Chessboard(const MyJSONNode &json, const ChessGame &g)
        : JSON_INI(nowTurn), JSON_INI(nowRound),
          game(g), players(g.players), JSON_INI(pickedChessman),
          JSON_INI(currentBannedMotions), JSON_INI(chessmanBoard),
          JSON_INI(loose), JSON_INI(win), JSON_INI(evaluations)
    {
    }

    Chessboard::Chessboard(const Chessboard &cb)
        : nowTurn(cb.nowTurn), nowRound(cb.nowRound), game(cb.game), players(cb.players), chessmanBoard(cb.chessmanBoard),
          pickedChessman(), currentBannedMotions(), loose(cb.loose), win(cb.win), evaluations(cb.evaluations)
    {
        currentBannedMotions.forceCopyFrom(cb.currentBannedMotions);

        for(int i = 0; i < cb.pickedChessman.size; ++i)
        {
            Chessman *c = cb.pickedChessman[i];
            pickedChessman.add(&game.players[c->chessmanIndex.player].ownedChessmans[c->chessmanIndex.index]);
        }

        for(short i = 0; i < (1 << INI_BOARD_HEIGHT_LOG2); ++i)
        {
            for(short j = 0; j < (1 << INI_BOARD_WIDTH_LOG2); ++j)
            {
                Chessman *c = cb.chessmanBoard[PointOrVectorS(j, i)];
                chessmanBoard.at(j, i) = c ? &game.players[c->chessmanIndex.player].ownedChessmans[c->chessmanIndex.index] : 0;
            }
        }
    }

    void Chessboard::operator=(const Chessboard &cb)
    {
        assert(&game == &cb.game, "board copy between different games");

        nowTurn = cb.nowTurn;
        nowRound = cb.nowRound;
        currentBannedMotions.forceCopyFrom(cb.currentBannedMotions);
        pickedChessman.forceCopyFrom(cb.pickedChessman);
        chessmanBoard = cb.chessmanBoard;

        for(int i = 0; i < players.size; ++i)
        {
            loose.push_back(cb.loose[i]);
            win.push_back(cb.win[i]);
            evaluations.push_back(cb.evaluations[i]);
        }
    }

    //************************************
    // Method:    operator[]
    // FullName:  Chessboard::operator[]
    // Access:    public
    // Returns:   Chessman*
    // Qualifier: const
    // Parameter: PointOrVectorS p
    //************************************
    Chessman *Chessboard::operator [](PointOrVectorS p) const           // TO-DO 这里逻辑可以优化一下, 看看怎么检测比较好
    {
        if(beyondBoardRange(p))
        {
            return (Chessman *)(void *) - 1;
        }

        return chessmanBoard[(p[1] << INI_BOARD_WIDTH_LOG2) + p[0]];
    }

    int Chessboard::getEvaluation(unsigned short p) const
    {
        int result = 0;

        for(int i = 0; i < MAX_PLAYER_NUM; ++i)
        {
            if(i != p)
            {
                result -= evaluations[i];
            }
        }

        result = evaluations[p] + (result) / (MAX_PLAYER_NUM - 1);

        return result;
    }

    int Chessboard::getEvaluation() const
    {
        return getEvaluation(nowTurn);
    }

    bool Chessboard::beyondBoardRange(PointOrVectorS &p)const           // 可以被改写从而提高性能
    {
        static const unsigned mask = (~(((unsigned short)1 << INI_BOARD_WIDTH_LOG2) - 1) << sizeof(unsigned short) * 8) | (unsigned short) - 1 & (~(((unsigned short)1 << INI_BOARD_HEIGHT_LOG2) - 1));

        if(mask&*((unsigned *)p.x))
        {
            return true;
        }
        else if(!game.config.boardRange[p])
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool Chessboard::onAddIntent(PointOrVectorS p /*= PointOrVectorS(-1,-1)*/, bool refreshEvaluations /*= false*/)
    {
        Chessman *c = players[nowTurn].ownedChessmans.add(Chessman(0, p, nowTurn, players[nowTurn].ownedChessmans.size, OFF_BOARD));
        return onPutIntent(c, p, refreshEvaluations);
    }

    //穿脱原理下, 操作就是这么简单
    void Chessboard::undoAdd(PointOrVectorS p, bool refreshEvaluations)
    {
        undoPut(chessmanBoard[p], PointOrVectorS(), refreshEvaluations);
        pickedChessman.deleteAtNoReturn(pickedChessman.size - 1);
        players[nowTurn].ownedChessmans.popNoReturn();
    }

    bool Chessboard::onPutIntent(Chessman *c, PointOrVectorS p, bool refreshEvaluations)
    {
        if((*this)[p] != NULL)           //beyondBoard时返回-1(ffff), 所以也会返回false
        {
            return false;
        }
        else if((pickedChessman.size > 0) && (pickedChessman[0] == c))
        {
            chessmanBoard[p] = c;

            assert(c->onPutIntent(p));    //如果不满足条件, 说明走法设计有问题.

            pickedChessman.deleteAtNoReturn(0);
            return true;
        }

        return false;
    }

    void Chessboard::undoPut(Chessman *c, PointOrVectorS previousP, bool refreshEvaluations /*= false*/)
    {
        chessmanBoard[c->coordinate] = NULL;
        c->undoPut();
        pickedChessman.add(c);

        c->coordinate = previousP;
    }

    bool Chessboard::onChangeTurn()
    {
        nowTurn = (unsigned short)((nowTurn + 1) % (MAX_PLAYER_NUM));
        nowRound++;
        return true;
    }

    void Chessboard::undoChangeTurn()
    {
        nowTurn = (unsigned short)((nowTurn - 1 + MAX_PLAYER_NUM) % (MAX_PLAYER_NUM));
        nowRound--;
    }

    bool Chessboard::onMoveIntent(const Move &move, bool refreshEvaluations)
    {
        bool result = true;

        for(int i = 0; i < move.size; i++)
        {
            result &= onMotionIntent(move[i], refreshEvaluations);
        }

        result &= (this->pickedChessman.size == 0);
        return result;
    }

    bool Chessboard::onMotionIntent(const Motion &op, bool refreshEvaluations)
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

    bool Chessboard::canMakeWholeMove(const Move &move, bool refreshEvaluations)
    {
        Chessboard cb(*this);
        bool result = cb.onWholeMoveIntent(move, refreshEvaluations);
        return result;
    }

    void Chessboard::undoMove(const Move &move, bool refreshEvaluations)
    {
        for(int i = move.size - 1; i >= 0; --i)
        {
            undoMotion(move[i], refreshEvaluations);
        }
    }

    void Chessboard::undoMotion(const Motion &operation, bool refreshEvaluations)
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

    bool Chessboard::onWholeMoveIntent(const Move &move, bool refreshEvaluations)
    {
        return onMoveIntent(move, refreshEvaluations) && onChangeTurn();
    }

    void Chessboard::undoWholeMove(const Move &move, bool refreshEvaluations)
    {
        undoChangeTurn();
        undoMove(move, refreshEvaluations);
    }

    bool Chessboard::onPickIntent(PointOrVectorS p, bool refreshEvaluations)
    {
        return onPickIntent((*this)[p], refreshEvaluations);
    }

    void Chessboard::undoPick(Chessman *c, PointOrVectorS p, bool refreshEvaluations)
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

    void Chessboard::undoPromotion(Chessman *c, short t, bool refreshEvaluations)
    {
        //TODO
    }
    void Chessboard::undoPromotion(PointOrVectorS p, short t, bool refreshEvaluations)
    {
        //TODO
    }

    bool Chessboard::onCaptureIntent(Chessman *c, PointOrVectorS p, bool refreshEvaluations)
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

    bool Chessboard::onPromotionIntent(Chessman *c, short t, bool refreshEvaluations)
    {
        return false;
    }

    bool Chessboard::onPickIntent(Chessman *c, bool refreshEvaluations)
    {
        if((c->chessmanIndex.player == nowTurn) && (pickedChessman.size == 0) && (c->onPickIntent()))
        {
            PointOrVectorS &p = c->coordinate;
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

    bool Chessboard::onPromotionIntent(PointOrVectorS p, short t, bool refreshEvaluations)
    {
        return onPromotionIntent((*this)[p], t, refreshEvaluations);
    }

    void Chessboard::undoCaptured(Chessman *c, bool refreshEvaluations)
    {
        c->undoCaptured();
        PointOrVectorS p(c->coordinate);
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

    void Chessboard::refreshEvaluations()
    {
        // TO-DO
    }

    bool Chessboard::gameOver()
    {
        // TO-DO
        for(int i = 0; i < MAX_PLAYER_NUM; ++i)
        {
            if(loose[i])
            {
                return true;
            }
        }

        return false;
    }
}
