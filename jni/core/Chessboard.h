
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
#include "PointOrVectorS.h"

namespace CIG
{
    class ChessGame;
    class Chessboard : public Object
    {
        public:
            Chessboard(const ChessGame &g);
            Chessboard(const Chessboard &cb);
            Chessboard(const MyJSONNode &json, const ChessGame &g);
            virtual ~Chessboard() {};
            void operator=(const Chessboard &cb);

            const ChessGame &game;
            const Array<Player, INI_PLAYER_ARRAY_SIZE, 0> &players;
            Array<Motion, INT_BANNED_MOTION_SIZE, 0> currentBannedMotions;
            Array<Chessman *, INI_CHESSMAN_GROUP_SIZE, 0> pickedChessman;
            Board<Chessman *> chessmanBoard;

            unsigned short INI_BOARD_WIDTH_LOG2, INI_BOARD_HEIGHT_LOG2, MAX_PLAYER_NUM;
            unsigned short nowRound;
            unsigned short nowTurn;
            VectorJSON<int> evaluations;
            VectorJSON<bool> loose;                  //������ʱ�����ж��Ƿ��ʤ, �ڷ�ֹ�Ⱥ��߳���ʤ�߷�ʱ������
            VectorJSON<bool> win;                        //������ʱ�����ж��Ƿ��ʤ, �ڷ�ֹ�Ⱥ��߳���ʤ�߷�ʱ������
            unsigned long MATE_VALUE = 10000000;
            //static const int GRADES[3][6];

            //************************************
            // Method:    onXXIntent
            // FullName:  ChessmanBoard::onXXIntent
            // Access:    virtual public
            // Returns:   bool
            // Qualifier:
            // Parameter: PointOrVector p, Chessman& c, CIGConfig::short t
            // ���Բ���, �������Ƿ�����ɹ�, ������ɹ�, �򱾴ε��ò�������̲���Ӱ��, ��������ɹ�, ��ᱣ������Ľ��.
            // Ĭ������Ϊ:
            // ��������"�������˵�����, �����Լ�������"�����ĳ���, ��������״̬, ��������ֵ, ����true;
            // ����޸Ĺ���, Ӧ�ü̳и���, ��дonXXXIntent����, �������������Լ�����������.
            // ��ȻҲ�������Լ��ĺ�������ñ���ĺ���, �ڲ������¼���Ĺ���.
            // ע��: ��Ϊʹ���˶�̬����, ���е�����ָ�������ʹ��ʱ���¼���. ԭ����: ���ҽ����õ�ָ����й��������ӵĲ���(�����Ƿ���ɾ��������)
            //************************************
            virtual bool onPickIntent(PointOrVectorS p, bool refreshEvaluations = false);
            virtual bool onPickIntent(Chessman *c, bool refreshEvaluations = false);
            //************************************
            // Method:    onAddIntent
            // FullName:  Chessboard::onAddIntent
            // Access:    virtual public
            // Returns:   Chessman*
            // Qualifier:
            // Parameter: PointOrVector p
            // ע���÷�: Ԥ����ĳ������һö����, �������ӵ�ָ��, ���ǻ�û����������Ϸ�з��������.
            //************************************
            virtual bool onAddIntent(PointOrVectorS p = PointOrVectorS(-1, -1), bool refreshEvaluations = false);
            virtual bool onPutIntent(Chessman *c, PointOrVectorS p = PointOrVectorS(-1, -1), bool refreshEvaluations = false);
            virtual bool onCaptureIntent(Chessman *c, PointOrVectorS p, bool refreshEvaluations = false);
            virtual bool onPromotionIntent(Chessman *c, short t, bool refreshEvaluations = false);
            virtual bool onPromotionIntent(PointOrVectorS p, short t, bool refreshEvaluations = false);
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
            virtual void undoAdd(PointOrVectorS p, bool refreshEvaluations = false);
            virtual void undoPick(Chessman *c, PointOrVectorS p, bool refreshEvaluations = false);
            virtual void undoPut(Chessman *c, PointOrVectorS previousP, bool refreshEvaluations = false);
            virtual void undoCaptured(Chessman *c, bool refreshEvaluations = false);
            virtual void undoPromotion(Chessman *c, short t, bool refreshEvaluations = false);
            virtual void undoPromotion(PointOrVectorS p, short t, bool refreshEvaluations = false);
            virtual void undoMove(const Move &move, bool refreshEvaluations = false);
            virtual void undoWholeMove(const Move &move, bool refreshEvaluations = false);
            virtual void undoMotion(const Motion &operation, bool refreshEvaluations = false);
            virtual void undoChangeTurn();
            virtual void refreshEvaluations();      //�����Ҫ��ÿ���������¼�������ֵ, ��ʵ�ִ˺���, �����ʵ��ĵط�����. ������������������ʽ, ����Դ˺���.
            virtual bool gameOver();

        public:
            virtual int getEvaluation(unsigned short p)const;
            virtual int getEvaluation()const;

            virtual Chessman *operator[](PointOrVectorS p)const;
            virtual bool beyondBoardRange(PointOrVectorS &p)const;

            inline virtual string toJSON()const;
    };
}
#endif /*__TOTALCHESSBOARD_H_*/


