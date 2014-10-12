#ifndef __TYPES_H__
#define __TYPES_H__

namespace CIG
{
    typedef float degree;

    const long double PI = acos((long double) - 1.0);

    enum GAME_TYPE
    {
        ERRROR,
        DRAUGHTS,//����
        CHINESE_CHESS,//�й�����
        GOBANG,//������
        WESTEN_CHESS,//��������
        GO,//Χ��
        FLIGHT_CHESS,//������
        MILITARY_CHESS,//����

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
        CHESS,                                      //����ֻ��һ������
        CHESSMAN_TYPE_NUM,          //����
    };

    enum OPERATIONS
    {
        NOMORE,                 //��Ϊ�߷����������ص���ʾ��: �޸������, ���������.
        BEGIN,
        ADD,                        //����һ������
        PICK,                       //����
        PUT,                            //����
        CAPTURE,                    //����
        PROMOTION,          //����
        DECOVER,                //�ƿ�
        END,                            //��Ϊ�߷����������ص���ʾ��: һ������·������, �뱣��������������.
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