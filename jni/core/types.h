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

    unsigned PLAYER_NUMS[GAME_TYPE_NUM] =
    {
        6,
        2,
        2,
        2,
        2,
        4,
        2,
    };

    enum CHESSMAN_TYPES
    {
        NOCHESSMAN = -1,
        CHESS,                                      //跳棋只有一种棋子
        CHESSMAN_TYPE_NUM,          //总数
    };

    enum OPERATIONS
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
    };

    char *OPERATION_NAME[END] =
    {
        "NOMORE",
        "BEGIN",
        "ADD",
        "PICK",
        "PUT",
        "CAPTURE",
        "PROMOTION",
        "DECOVER",
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