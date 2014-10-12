
#ifndef __TOTALCHESSBOARD_H__
#define __TOTALCHESSBOARD_H__

#include "Motion.h"
#include "Array.h"
#include "Stack.h"
#include "ChessGameConfig.h"
#include "Chessman.h"
#include "utilities.h"
#include "ChessmanIndex.h"
#include "Player.h"
#include "ChessmanIndexBoard.h"

namespace CIG
{
    class Chessboard
    {
            class Game;
        public:
            Chessboard();
            Chessboard(const Chessboard &cb);
            virtual ~Chessboard() {};
            void operator=(const Chessboard &cb);

            Game *game;
            int evaluations[PLAYER_NUM];
            Array<Motion, ChessGameConfig::INT_BANNED_MOTION_SIZE, 0> currentBannedMotions;
            Array<ChessmanIndex, ChessGameConfig::INI_CHESSMAN_GROUP_SIZE, 0> pickedChessmanByIndex;
            ChessmanIndexBoard chessmanIndexBoard;

            bool loose[PLAYER_NUM];                  //������ʱ�����ж��Ƿ��ʤ, �ڷ�ֹ�Ⱥ��߳���ʤ�߷�ʱ������
            bool win[PLAYER_NUM];                        //������ʱ�����ж��Ƿ��ʤ, �ڷ�ֹ�Ⱥ��߳���ʤ�߷�ʱ������

            static const int MATE_VALUE = 100000000;  // �����ķ�ֵ
            static const int WIN_VALUE = MATE_VALUE >> 1; // ������ʤ���ķ�ֵ���ޣ�������ֵ��˵���Ѿ�������ɱ����
            static const int ADVANCED_VALUE = 3;  // ����Ȩ��ֵ

            static const int GRADES[3][6];

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
            virtual bool onPickIntent(PointOrVector p, bool refreshEvaluations = false);
            virtual bool onPickIntent(Chessman *c , bool refreshEvaluations = false);
            //************************************
            // Method:    onAddIntent
            // FullName:  CIG::Chessboard::onAddIntent
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
            virtual bool onMoveIntent(Move &move, bool refreshEvaluations = false);
            virtual bool onWholeMoveIntent(Move &move, bool refreshEvaluations = false);
            virtual bool onMotionIntent(Motion &operation, bool refreshEvaluations = false);
            virtual bool canMakeWholeMove(Move &move, bool refreshEvaluations = false);
            virtual bool onChangeTurn();

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
            virtual void undoAdd(PointOrVector p, bool refreshEvaluations = false);
            virtual void undoPick(Chessman *c , PointOrVector p, bool refreshEvaluations = false);
            virtual void undoPut(Chessman *c, PointOrVector previousP, bool refreshEvaluations = false);
            virtual void undoCaptured(Chessman *c, bool refreshEvaluations = false);
            virtual void undoPromotion(Chessman *c, CHESSMAN_TYPES t, bool refreshEvaluations = false);
            virtual void undoPromotion(PointOrVector p, CHESSMAN_TYPES t, bool refreshEvaluations = false);
            virtual void undoMove(Move &move, bool refreshEvaluations = false);
            virtual void undoWholeMove(Move &move, bool refreshEvaluations = false);
            virtual void undoMotion(Motion &operation, bool refreshEvaluations = false);
            virtual void undoChangeTurn();
            bool CIG::Chessboard::onSelfHalfOfBoard(PointOrVector &p);
            virtual void refreshEvaluations();      //�����Ҫ��ÿ���������¼�������ֵ, ��ʵ�ִ˺���, �����ʵ��ĵط�����. ������������������ʽ, ����Դ˺���.
            virtual bool gameOver();

        public:
            virtual int getEvaluation(PLAYER_NAMES p)const;
            virtual int getEvaluation()const;

            Chessman *operator[](PointOrVector p)const;
            bool beyondBoardRange(PointOrVector &p)const;

            friend ostringstream &operator<<(ostringstream &oss, const Chessboard &cb)                      ///�������÷���, �ͻ���ÿ������캯��, id��������߰���.
            {
                for(int i = 0; i < (1 << cb.game->config.INI_BOARD_WIDTH_LOG2); ++i)
                {
                    for(int j = 0; j < (1 << cb.game->config.INI_BOARD_HEIGHT_LOG2); ++j)
                    {
                        oss << "[ " << i << " , " << j << " ]";
                        //oss<< cb.mChessmanBoard[j][i];            // TO-DO
                    }
                }

                oss << '}\n';
                return oss;
            }

            Chessboard(JSONNode json)
            {

            }
    };
}

#endif /*__TOTALCHESSBOARD_H_*/

