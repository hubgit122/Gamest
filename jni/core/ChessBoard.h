
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

            ChessGame*game;
            Array<Player, INI_PLAYER_ARRAY_SIZE, 0> &players;
            Array<Motion, INT_BANNED_MOTION_SIZE, 0> currentBannedMotions;
            Array<Chessman *, INI_CHESSMAN_GROUP_SIZE, 0> pickedChessman;
            Board<Chessman *> chessmanBoard;
            
            unsigned short INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, MAX_PLAYER_NUM;
            unsigned nowRound;
            unsigned short nowTurn;
            vector<int> evaluations;
            vector<bool> loose;                  //������ʱ�����ж��Ƿ��ʤ, �ڷ�ֹ�Ⱥ��߳���ʤ�߷�ʱ������
            vector<bool> win;                        //������ʱ�����ж��Ƿ��ʤ, �ڷ�ֹ�Ⱥ��߳���ʤ�߷�ʱ������

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
            // FullName:  Chessboard::onAddIntent
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
            // FullName:  Chessboard::undoXX
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

#endif /*__TOTALCHESSBOARD_H_*/


