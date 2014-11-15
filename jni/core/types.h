#ifndef __TYPES_H__
#define __TYPES_H__

namespace CIG
{
    typedef float degree;

    const long double PI = acos((long double) - 1.0);

    enum GAME_TYPE
    {
        ERRROR,
        DRAUGHTS,//跳棋
        CHINESE_CHESS,//中国象棋
        GOBANG,//五子棋
        WESTEN_CHESS,//国际象棋
        GO,//围棋
        FLIGHT_CHESS,//飞行棋
        MILITARY_CHESS,//军棋

        GAME_TYPE_NUM
    };
    enum BASIC_OPERATION_ID             //包含了大多数棋的走法, 需要时可以从0开始扩充. 定义这个的目的是添加比较通用的走棋代码.
    {
        NOMORE,                 //作为走法生成器返回的提示语: 无更多操作, 请回退搜索.
        BEGIN,
        ADD,                        //增加一个棋子
        PICK,                       //拿起
        PUT,                            //走棋
        CAPTURE,                    //吃子
        PROMOTION,          //升变
        DECOVER,                //掀开
        END,                            //作为走法生成器返回的提示语: 一条搜索路径结束, 请保存结果并回退搜索.
        SURRENDER,           //认输
        USER_OPERATION_BASE,
    };

    enum BASIC_CHESS_TYPE
    {
        MONO_CHESS,
        KING
    };

    enum CHESSMAN_STATUS
    {
        ON_BOARD,
        OFF_BOARD,
        CAPTURED,
    };

    enum VISIBILITIES
    {
        ALL,
        NONE,
        SELF,
        ALLY,
    };
}
#endif // !__TYPES_H__