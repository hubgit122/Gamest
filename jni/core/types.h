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
    enum BASIC_OPERATION_ID             //�����˴��������߷�, ��Ҫʱ���Դ�0��ʼ����. ���������Ŀ������ӱȽ�ͨ�õ��������.
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
        SURRENDER,           //����
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