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

            static const int MATE_VALUE = 100000000;  // 将死的分值
            static const int WIN_VALUE = MATE_VALUE >> 1; // 搜索出胜负的分值界限，超出此值就说明已经搜索出杀棋了

            //************************************
            // Method:    onXXIntent
            // FullName:  CIG::ChessmanBoard::onXXIntent
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
            virtual bool onPickIntent(PointOrVector p, bool refreshEvaluations = false) = 0;
            virtual bool onPickIntent(Chessman *c, bool refreshEvaluations = false) = 0;
            //************************************
            // Method:    onAddIntent
            // FullName:  CIG::Chessboard::onAddIntent
            // Access:    virtual public
            // Returns:   Chessman*
            // Qualifier:
            // Parameter: PointOrVector p
            // 注意用法: 预告在某处增加一枚棋子, 返回棋子的指针, 但是还没有真正在游戏中放下这个子.
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
            // 注意, 为了运行效率, 并且尽量减少外界接口, 所以不做任何判断, 编程者必须严格保证是按照走棋的顺序撤销. 一定是类内部调用.
            // 特别注意undoCaptureIntent的参数是被吃棋子, onCapture的参数是吃子的棋子
            // 还要特别注意undoPut的默认实现并没有进行棋子坐标的恢复. 也就是说在执行put和unput之后, 得到的结果是其余不变, 但是棋子的坐标从pick的发生地变为put的目的地.
            // 如果要实现棋子坐标恢复的话需要增加很多结构, 并不是直接保存一个值就行的. 因为棋子可能经历类似put, put, unput, unput的过程.
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
            virtual void refreshEvaluations() = 0;    //如果需要对每个局面重新计算评估值, 请实现此函数, 并在适当的地方调用. 如果采用增量计算的形式, 请忽略此函数.
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
