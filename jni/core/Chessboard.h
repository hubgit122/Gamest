
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
            VectorJSON<bool> loose;                  //在搜索时辅助判断是否获胜, 在防止先后走出获胜走法时起作用
            VectorJSON<bool> win;                        //在搜索时辅助判断是否获胜, 在防止先后走出获胜走法时起作用
            unsigned long MATE_VALUE = 10000000;
            //static const int GRADES[3][6];

            //************************************
            // Method:    onXXIntent
            // FullName:  ChessmanBoard::onXXIntent
            // Access:    virtual public
            // Returns:   bool
            // Qualifier:
            // Parameter: PointOrVector p, Chessman& c, CIGConfig::short t
            // 尝试操作, 并返回是否操作成功, 如果不成功, 则本次调用不会对棋盘产生影响, 如果操作成功, 则会保存操作的结果.
            // 默认配置为:
            // 对于满足"不动别人的棋子, 不吃自己的棋子"条件的尝试, 调整棋盘状态, 更新评估值, 返回true;
            // 如果修改规则, 应该继承该类, 重写onXXXIntent函数, 并在其中配置自己的评估规则.
            // 当然也可以在自己的函数里调用本类的函数, 在并配置新加入的规则.
            // 注意: 因为使用了动态容器, 所有的棋子指针必须在使用时重新计算. 原则是: 当且仅当得到指针后有过增加棋子的操作(无论是否又删除了棋子)
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
            // 注意用法: 预告在某处增加一枚棋子, 返回棋子的指针, 但是还没有真正在游戏中放下这个子.
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
            // 注意, 为了运行效率, 并且尽量减少外界接口, 所以不做任何判断, 编程者必须严格保证是按照走棋的顺序撤销. 一定是类内部调用.
            // 特别注意undoCaptureIntent的参数是被吃棋子, onCapture的参数是吃子的棋子
            // 还要特别注意undoPut的默认实现并没有进行棋子坐标的恢复. 也就是说在执行put和unput之后, 得到的结果是其余不变, 但是棋子的坐标从pick的发生地变为put的目的地.
            // 如果要实现棋子坐标恢复的话需要增加很多结构, 并不是直接保存一个值就行的. 因为棋子可能经历类似put, put, unput, unput的过程.
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
            virtual void refreshEvaluations();      //如果需要对每个局面重新计算评估值, 请实现此函数, 并在适当的地方调用. 如果采用增量计算的形式, 请忽略此函数.
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


