#ifndef __CHESSBOARDINTERFACE_H__
#define __CHESSBOARDINTERFACE_H__

#include "Motion.h"
#include "Array.h"
#include "Stack.h"
#include "ChessGameConfig.h"
#include "Chessman.h"
#include "utilities.h"
#include "ChessmanIndex.h"
#include "Player.h"
#include "Board.h"

namespace CIG
{
    class ChessboardInterface: public Object
    {
        public:
            virtual ~ChessboardInterface() {};
            inline virtual string toJSON()const = 0;

            static const int MATE_VALUE = 100000000;  // �����ķ�ֵ
            static const int WIN_VALUE = MATE_VALUE >> 1; // ������ʤ���ķ�ֵ���ޣ�������ֵ��˵���Ѿ�������ɱ����

            //************************************
            // Method:    onXXIntent
            // FullName:  CIG::ChessmanBoard::onXXIntent
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
            virtual bool onPickIntent(PointOrVector p, bool refreshEvaluations = false) = 0;
            virtual bool onPickIntent(Chessman *c, bool refreshEvaluations = false) = 0;
            //************************************
            // Method:    onAddIntent
            // FullName:  CIG::Chessboard::onAddIntent
            // Access:    virtual public
            // Returns:   Chessman*
            // Qualifier:
            // Parameter: PointOrVector p
            // ע���÷�: Ԥ����ĳ������һö����, �������ӵ�ָ��, ���ǻ�û����������Ϸ�з��������.
            //************************************
            virtual bool onAddIntent(PointOrVector p = PointOrVector(-1, -1), bool refreshEvaluations = false) = 0;
            virtual bool onPutIntent(const Chessman *const c, PointOrVector p = PointOrVector(-1, -1), bool refreshEvaluations = false) = 0;
            virtual bool onCaptureIntent(Chessman *c, PointOrVector p, bool refreshEvaluations = false) = 0;
            virtual bool onPromotionIntent(Chessman *c, CHESSMAN_TYPES t, bool refreshEvaluations = false) = 0;
            virtual bool onPromotionIntent(PointOrVector p, CHESSMAN_TYPES t, bool refreshEvaluations = false) = 0;
            virtual bool onMoveIntent(Move &move, bool refreshEvaluations = false) = 0;
            virtual bool onWholeMoveIntent(Move &move, bool refreshEvaluations = false) = 0;
            virtual bool onMotionIntent(const Motion &operation, bool refreshEvaluations = false) = 0;
            virtual bool canMakeWholeMove(Move &move, bool refreshEvaluations = false) = 0;
            virtual bool onChangeTurn() = 0;

            //************************************
            // Method:    undoXX
            // FullName:  CIG::Chessboard::undoXX
            // Access:    virtual private
            // Returns:   void
            // Qualifier:
            // Parameter: PointOrVector p
            // ע��, Ϊ������Ч��, ���Ҿ����������ӿ�, ���Բ����κ��ж�, ����߱����ϸ�֤�ǰ��������˳����. һ�������ڲ�����.
            // �ر�ע��undoCaptureIntent�Ĳ����Ǳ�������, onCapture�Ĳ����ǳ��ӵ�����
            // ��Ҫ�ر�ע��undoPut��Ĭ��ʵ�ֲ�û�н�����������Ļָ�. Ҳ����˵��ִ��put��unput֮��, �õ��Ľ�������಻��, �������ӵ������pick�ķ����ر�Ϊput��Ŀ�ĵ�.
            // ���Ҫʵ����������ָ��Ļ���Ҫ���Ӻܶ�ṹ, ������ֱ�ӱ���һ��ֵ���е�. ��Ϊ���ӿ��ܾ�������put, put, unput, unput�Ĺ���.
            //************************************
            virtual void undoAdd(PointOrVector p, bool refreshEvaluations = false) = 0;
            virtual void undoPick(Chessman *c, PointOrVector p, bool refreshEvaluations = false) = 0;
            virtual void undoPut(Chessman *c, PointOrVector previousP, bool refreshEvaluations = false) = 0;
            virtual void undoCaptured(Chessman *c, bool refreshEvaluations = false) = 0;
            virtual void undoPromotion(Chessman *c, CHESSMAN_TYPES t, bool refreshEvaluations = false) = 0;
            virtual void undoPromotion(PointOrVector p, CHESSMAN_TYPES t, bool refreshEvaluations = false) = 0;
            virtual void undoMove(Move &move, bool refreshEvaluations = false) = 0;
            virtual void undoWholeMove(Move &move, bool refreshEvaluations = false) = 0;
            virtual void undoMotion(Motion &operation, bool refreshEvaluations = false) = 0;
            virtual void undoChangeTurn() = 0;
            virtual void refreshEvaluations() = 0;    //�����Ҫ��ÿ���������¼�������ֵ, ��ʵ�ִ˺���, �����ʵ��ĵط�����. ������������������ʽ, ����Դ˺���.
            virtual bool gameOver() = 0;

            virtual int getEvaluation(unsigned short p)const = 0;
            virtual int getEvaluation()const = 0;

            virtual Chessman *operator[](PointOrVector p)const = 0;
            virtual bool beyondBoardRange(PointOrVector &p)const = 0;

        private:
            ChessboardInterface() {};
    };
}
#endif // !__CHESSBOARDINTERFACE_H__
